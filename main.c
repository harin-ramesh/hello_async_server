#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

#include "common.h"

int setup_server_socket() {
    int listen_fd;
    struct sockaddr_in server_addr;

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_n_die("Socket error");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    if (bind(listen_fd, (SA *) &server_addr, sizeof(server_addr)) < 0)
        err_n_die("Bind error");

    if (listen(listen_fd, 10) < 0)
        err_n_die("Listen error");

    return listen_fd;
}

void handle_client(int client_fd, fd_set *current_sockets) {
    uint8_t receive_line[MAX_LINE + 1];
    uint8_t response[MAX_LINE + 1];
    int n;

    memset(receive_line, 0, sizeof(receive_line));

    while ((n = read(client_fd, receive_line, MAX_LINE - 1)) > 0) {
        printf("\nHex: %s\nText: %s\n", (char *)bin2hex(receive_line, n), receive_line);
        if (receive_line[n - 1] == '\n') {
            break;
        }
        memset(receive_line, 0, sizeof(receive_line));
    }

    if (n < 0) {
        err_n_die("Read error");
    }

    snprintf((char *) response, sizeof(response), "HTTP/1.0 200 OK\r\n\r\nHello world!\n");
    write(client_fd, response, strlen((char *) response));
    close(client_fd);
    FD_CLR(client_fd, current_sockets);
}

int main() {
    int listen_fd = setup_server_socket();
    fd_set current_sockets, ready_sockets;

    FD_ZERO(&current_sockets);
    FD_SET(listen_fd, &current_sockets);

    printf("Waiting for connections on port %d\n", SERVER_PORT);

    while (1) {
        ready_sockets = current_sockets;

        if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0)
            err_n_die("Select error");

        for (int fd = 0; fd < FD_SETSIZE; fd++) {
            if (FD_ISSET(fd, &ready_sockets)) {
                if (fd == listen_fd) {
                    int client_fd = accept(listen_fd, NULL, NULL);
                    if (client_fd < 0) {
                        perror("Accept failed");
                        continue;
                    }
                    FD_SET(client_fd, &current_sockets);
                } else {
                    handle_client(fd, &current_sockets);
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
