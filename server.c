#include "server.h"
#include "json_io.h"
#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>


/*
 * Log a message to the terminal
 * Usage:
 *   log_message(3, "Error: ", "file ", "not found");
 * The first argument is the number of strings to log.
 */
void log_msg(int count, ...) {
    va_list args;
    va_start(args, count);
    printf("LOGGER: ");
    // creating a timestamp
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char buffer[26];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("[%s] ", buffer);
    for (int i = 0; i < count; i++) {
        const char *s = va_arg(args, const char*);
        printf("%s", s);
    }

    printf("\n");

    va_end(args);
}


/*
 * Create the server socket
 */
int create_server_socket() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return server_fd;
}

/*
 * Set up the 'address' struct to be used for TCP
 * :param server_fd: the file descriptor of the network socket
 * :param sockaddr_in: pointer to a sockaddr_in struct
 * */
void configure_server_address(struct sockaddr_in *address) {
    (*address).sin_family = AF_INET;
    (*address).sin_addr.s_addr = INADDR_ANY;
    (*address).sin_port = htons(PORT);
}

/*
 *bind the socket to the open file descriptor and listen on it
 :param server_fd: the file descriptor of the network socket
 :param sockaddr_in: pointer to an 'address' struct
 * */
int bind_and_listen(int server_fd, struct sockaddr_in *address) {
    if (bind(server_fd, (struct sockaddr *)address, sizeof(*address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    return 0;
}

/*
 Serve out test questions as JSON
    :param client_fd: the file descriptor to write the response to
    :param filepath: the filepath on the host operating system to open for reading
 */
void serve_json_file(int client_fd, const char *filepath) {
    int file_fd = open(filepath, O_RDONLY);
    log_msg(2, "attempting to open file: ", filepath);
    if (file_fd < 0) {
        const char *not_found =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: application/json\r\n\r\n"
            "{\"error\": \"File not found\"}";
        send(client_fd, not_found, strlen(not_found), 0);
        return;
    }


    /*getting information about the file so that we can appropriately 
    write our HTTP response, along with properly allocating a memory buffer
    */
    struct stat st;
    fstat(file_fd, &st);

    char *json_data = malloc(st.st_size);
    read(file_fd, json_data, st.st_size);
    close(file_fd);

    char header[256];
    // using snprintf() here to prevent buffer overflows, so that no matter
    // the size of our JSON file, we are accounting for it while writing
    snprintf(header, sizeof(header),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: application/json\r\n"
             "Content-Length: %ld\r\n\r\n",
             st.st_size);

    send(client_fd, header, strlen(header), 0);
    send(client_fd, json_data, st.st_size, 0);

    free(json_data);
}

/*
 Handle a client request
    :param client_fd: the file descriptor that was opened during the initiation of a request
 */
void handle_client(int client_fd) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_fd, buffer, sizeof(buffer) - 1);

    // Parse the HTTP method
    char method[8], path[256];
    sscanf(buffer, "%s %s", method, path);
    log_msg(4, "got ", method, " request on path: ", path);

    if (strncmp(method, "GET", 3) == 0) {
        char filepath[MAX_PATH_LENGTH];
        snprintf(filepath, sizeof(filepath), "data%s", path);
        /*
         * This is preventing against any sort of directory traversal,
         * i.e. requesting 'http://server.com/../../../etc/shadow' will cause the server to
         * respond with 400 status code. prevents unintendedly leaking sensitive files on the host.
         * */
        struct stat s;
        /* if filepath is a directory, we return the filenames in a list so the client can 
         *iteratively get them all. If its a file, we can assume that it should read it as a json file
         */
        if ( stat(filepath, &s) == 0 ) {
            if ( s.st_mode & S_IFDIR) {
                json_object *files = json_from_file_list(filepath);
                if (!files) {
                    const char *bad =
                    "HTTP/1.1 400 Bad Request\r\n\r\n";
                    send(client_fd, bad, strlen(bad), 0);
                }
                

                const char *json_str = json_object_to_json_string_ext(files, JSON_C_TO_STRING_PRETTY);
                char header[1024];
                snprintf(header, sizeof(header),
                     "HTTP/1.1 200 OK\r\n"
                     "Content-Type: application/json\r\n"
                     "Content-Length: %zu\r\n\r\n",
                     strlen(json_str));
                send(client_fd, header, strlen(header), 0);
                send(client_fd, json_str, strlen(json_str), 0);
                json_object_put(files);
            } else {
                serve_json_file(client_fd, filepath);
            }
        }
        /*
         * this is here to protect against an path traversals, so the caller cant requests 'http://localhost:8080/../../etc/shadow
         * or something.
         * */
        if (strstr(path, "..")) {
            const char *bad =
                "HTTP/1.1 400 Bad Request\r\n\r\n";
            send(client_fd, bad, strlen(bad), 0);
        }
    }

    close(client_fd);
}
