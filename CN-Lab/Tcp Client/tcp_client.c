#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 1221
#define BUF_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server;
    char buffer[BUF_SIZE];
    int bytes;

    // Create TCP socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        printf("Socket creation failed\n");
        return 1;
    }

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(client_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection failed\n");
        close(client_fd);
        return 1;
    }

    printf("Connected to TCP Server!\n");

    while (1) {
        printf("Enter message: ");
        if (fgets(buffer, BUF_SIZE, stdin) == NULL)
            break;

        buffer[strcspn(buffer, "\r\n")] = '\0';

        if (strcmp(buffer, "exit") == 0)
            break;

        if (strlen(buffer) == 0)
            continue;

        // Send message
        if (send(client_fd, buffer, strlen(buffer), 0) < 0) {
            printf("Send failed\n");
            break;
        }

        // Receive echo
        bytes = recv(client_fd, buffer, BUF_SIZE - 1, 0);
        if (bytes <= 0) {
            printf("Connection closed or receive failed\n");
            break;
        }

        buffer[bytes] = '\0';
        printf("Server echoed: %s\n", buffer);
    }

    close(client_fd);
    return 0;
}