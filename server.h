#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>

#define PORT 9101
#define BUFFER_SIZE 4096
#define MAX_RESPONSE_LENGTH 8182

int create_server_socket();
void configure_server_address(struct sockaddr_in *address);
int bind_and_listen(int server_fd, struct sockaddr_in *address);
void handle_client(int client_fd);
void serve_json_file(int client_fd, const char *filepath);
void log_msg(int count, ...);

#endif
