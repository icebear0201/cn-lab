#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);
    char buffer[BUF_SIZE];
    int n;

    // Create UDP socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        printf("Socket creation failed\n");
        return 1;
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Enter message
    printf("Enter message: ");
    if (fgets(buffer, BUF_SIZE, stdin) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
    }

    // Send message to server
    if (sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, server_len) < 0) {
        printf("Send failed\n");
        close(client_socket);
        return 1;
    }

    // Receive response
    n = recvfrom(client_socket, buffer, BUF_SIZE - 1, 0, (struct sockaddr *)&server_addr, &server_len);
    if (n < 0) {
        printf("Receive failed\n");
    } else {
        buffer[n] = '\0';
        printf("Server Response: %s\n", buffer);
    }

    close(client_socket);
    return 0;
}