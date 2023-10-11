#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

const int PORT = 8080;

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    struct hostent* server;

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        std::cerr << "Error: Failed to create socket." << std::endl;
        return 1;
    }

    // Get server information
    server = gethostbyname("localhost");
    if (server == nullptr) {
        std::cerr << "Error: Failed to get server information." << std::endl;
        return 1;
    }

    // Connect to the server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error: Connection failed." << std::endl;
        return 1;
    }

    // Send an HTTP GET request
    const char* request = "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
    send(client_socket, request, strlen(request), 0);

    // Receive and display the server's response
    char buffer[1024];
    int bytes_received;
    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        std::cout << buffer;
    }

    close(client_socket);
    return 0;
}
