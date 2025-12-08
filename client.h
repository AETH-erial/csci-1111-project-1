#ifndef CLIENT_H
#define CLIENT_H

#include <json-c/json.h>

// Connects to a TCP server. Returns socket fd or -1 on error
int connect_to_server(const char *ip, int port);

// Sends a GET request and reads full response into dynamically allocated buffer
// Caller must free the buffer
char *http_get(int sockfd, const char *path);

// Parses JSON body from HTTP response buffer
// Returns a json_object* (caller must call json_object_put)
json_object *parse_json_body(const char *http_response);

#endif

