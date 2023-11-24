#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const int PORT = 8080;
const int BACKLOG = 5;

void handle_request(int client_socket) {
    const char* response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Error: Failed to create socket." << std::endl;
        return 1;
    }

    // Bind the socket to a specific port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error: Binding failed." << std::endl;
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, BACKLOG) < 0) {
        std::cerr << "Error: Listening failed." << std::endl;
        return 1;
    }

    std::cout << "HTTP server started on port " << PORT << ". Press Ctrl+C to exit." << std::endl;

    // Accept and handle incoming connections
    while (true) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
        if (client_socket < 0) {
            std::cerr << "Error: Accepting connection failed." << std::endl;
            continue;
        }

        handle_request(client_socket);
    }

    close(server_socket);
    return 0;
}
