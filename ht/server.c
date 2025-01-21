#include <stdio.h>  // console input/output, perror
#include <stdlib.h> // exit
#include <string.h> // string manipulation
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/socket.h> // socket APIs
#include <netinet/in.h> // sockaddr_in
#include <unistd.h>     // open, close

#include <signal.h> // signal handling
#include <time.h>   // time


#define PORT 8888
#define BUFFER_SIZE 1024
#define BACKLOG 10 // number of pending connections queue will hold

int server_socket;
int client_socket;
/* char *request; */


void handle_signal(int signal) {
  if (signal == SIGINT)
  {
    printf("\nShutting down server...\n");

    close(client_socket);
    close(server_socket);

    /* if (request != NULL) */
    /*   free(request); */

    exit(0);
  }
}



void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0'; // end of string
        /* printf("Received request:\n%s\n", buffer); */

        // check method
        if (strstr(buffer, "GET / HTTP/") != NULL) {
            const char *content = "{\"status\": \"OK\"}";
            const char *content_type = "application/json";
            const char *etag = "W/\"123456789\"";

            size_t content_length = strlen(content);

            // Формируем ответ
            char response[BUFFER_SIZE];
            int response_length = snprintf(response, sizeof(response),
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: %s\r\n"
                "Content-Length: %zu\r\n"
                "ETag: %s\r\n"
                "Server: backend_benchmarks.htserver\r\n"
                "\r\n"
                "%s", 
                content_type, content_length, etag, content);

            // Отправляем полный ответ
            write(client_socket, response, response_length);
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
    signal(SIGINT, handle_signal);

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // socket bind
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Error: The server is not bound to the address.\n");
        return 1;
    }

    if (listen(server_socket, BACKLOG) < 0) {
        printf("Error: The server is not listening.\n");
        return 1;
    }

    printf("Started server: http://%s:%d\n\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));

    while (1) {
        // handle incoming connections
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        handle_client(client_socket);
    }

    close(server_socket);
    printf("\nServer stopped.\n");
    return 0;
}
