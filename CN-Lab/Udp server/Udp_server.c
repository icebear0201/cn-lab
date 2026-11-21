#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUF_SIZE];
    int n;
    int opt = 1;

    // Create UDP socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        printf("Socket creation failed\n");
        return 1;
    }

    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Bind failed\n");
        close(server_socket);
        return 1;
    }

    printf("UDP Server is running on port %d...\n", PORT);

    // Receive message from client
    n = recvfrom(server_socket, buffer, BUF_SIZE - 1, 0, (struct sockaddr *)&client_addr, &client_len);
    if (n < 0) {
        printf("Receive failed\n");
        close(server_socket);
        return 1;
    }

    buffer[n] = '\0';
    printf("Message from Client: %s\n", buffer);

    // Send response to client
    const char *response = "Hello from UDP Server";
    if (sendto(server_socket, response, strlen(response), 0, (struct sockaddr *)&client_addr, client_len) < 0) {
        printf("Send failed\n");
    } else {
        printf("Response sent to Client\n");
    }

    close(server_socket);
    return 0;
}