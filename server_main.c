#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int server_fd = create_server_socket();

    struct sockaddr_in address;
    configure_server_address(&address);

    bind_and_listen(server_fd, &address);

    printf("JSON server running at http://localhost:%d\n", PORT);

    while (1) {
        int addrlen = sizeof(address);
        int client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }

        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}

