#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define RECV_BUFFER 8192

int connect_to_server(const char *ip, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket failed");
        return -1;
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        perror("inet_pton failed");
        close(sockfd);
        return -1;
    }

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

char *http_get(int sockfd, const char *path) {
    char request[1024];
    snprintf(request, sizeof(request),
             "GET %s HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n",
             path);

    if (send(sockfd, request, strlen(request), 0) < 0) {
        perror("send failed");
        return NULL;
    }

    size_t buffer_size = RECV_BUFFER;
    char *response = malloc(buffer_size);
    if (!response) return NULL;

    size_t total = 0;
    ssize_t n;
    while ((n = recv(sockfd, response + total, buffer_size - total - 1, 0)) > 0) {
        total += n;
        if (total >= buffer_size - 1) {
            buffer_size *= 2;
            char *tmp = realloc(response, buffer_size);
            if (!tmp) {
                free(response);
                return NULL;
            }
            response = tmp;
        }
    }
    response[total] = '\0';
    return response;
}

json_object *parse_json_body(const char *http_response) {
    char *json_start = strstr(http_response, "\r\n\r\n");
    if (!json_start) return NULL;
    json_start += 4; // skip past double CRLF
    return json_tokener_parse(json_start);
}

