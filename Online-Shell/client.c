#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char const *argv[]) {
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(6674);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    /*---- Connect the socket to the server using the address struct ----*/
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

    printf("Connected to the server.\n");

    while (1) {
        // Get command input from the user
        printf("Enter command (or 'quit' to exit): ");
        fgets(buffer, 1024, stdin);

        // Remove newline character from the command
        buffer[strcspn(buffer, "\n")] = '\0';

        // Check for exit command
        if (strcmp(buffer, "quit") == 0) {
            break;
        }

        // Send command to the server
        if (send(clientSocket, buffer, strlen(buffer), 0) < 0) {
            printf("Failed to send command");
            continue;
        }

        // Receive and print output from the server
        printf("Output from server:\n");
        int read_size;
        while ((read_size = recv(clientSocket, buffer, 1024 - 1, 0)) > 0) {
            buffer[read_size] = '\0';
            printf("%s", buffer);

            // Break if we receive less than BUFFER_SIZE, which might mean end of data
            if (read_size < 1024 - 1) {
                break;
            }
        }

        printf("\n");
    }
    close(clientSocket);

    return 0;
}