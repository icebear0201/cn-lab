#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 1221
#define BUF_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUF_SIZE];
    int bytes;
    int opt = 1;

    // Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        printf("Socket creation failed\n");
        return 1;
    }

    // Allow port reuse immediately if you restart the server
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Prepare server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        printf("Bind failed\n");
        close(server_fd);
        return 1;
    }

    // Listen
    listen(server_fd, 3);
    printf("TCP Server listening on port %d...\n", PORT);

    // Accept connection
    client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (client_fd < 0) {
        printf("Accept failed\n");
        close(server_fd);
        return 1;
    }

    printf("Client connected!\n");

    // Receive and echo messages
    while ((bytes = recv(client_fd, buffer, BUF_SIZE - 1, 0)) > 0) {
        buffer[bytes] = '\0';
        printf("Received: %s\n", buffer);
        send(client_fd, buffer, bytes, 0);
    }

    close(client_fd);
    close(server_fd);
    return 0;
}