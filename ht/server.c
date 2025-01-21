#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0'; // Завершаем строку
        /* printf("Received request:\n%s\n", buffer); */

        // Проверяем, является ли запрос GET к /
        if (strstr(buffer, "GET / HTTP/") != NULL) {
            const char *response = "HTTP/1.1 200 OK\r\n"
                                   "Content-Type: application/json\r\n"
                                   "Content-Length: 17\r\n"
                                   "\r\n"
                                   "{\"status\": \"OK\"}";
            write(client_socket, response, strlen(response));
        } else {
            const char *response = "HTTP/1.1 404 Not Found\r\n"
                                   "Content-Length: 0\r\n"
                                   "\r\n";
            write(client_socket, response, strlen(response));
        }
    }

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Создаем сокет
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Настраиваем адрес и порт
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Привязываем сокет к адресу
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        return 1;
    }

    // Слушаем входящие соединения
    if (listen(server_socket, 3) < 0) {
        perror("Listen failed");
        close(server_socket);
        return 1;
    }

    printf("Server running on port %d\n", PORT);

    while (1) {
        // Принимаем входящее соединение
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}
