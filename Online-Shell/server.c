#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>

void handle_client(int newSocket) {
    char buffer[1024];
    int read_size;

    // Loop to handle multiple commands from the same client
    while ((read_size = recv(newSocket, buffer, 1024, 0)) > 0) {
        buffer[read_size] = '\0';

        // Tokenize command
        char *args[20];
        int i = 0;
        char *token = strtok(buffer, " ");
        while (token != NULL && i < 19) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Redirect stdout and stderr to the socket
        dup2(newSocket, STDOUT_FILENO);
        dup2(newSocket, STDERR_FILENO);

        // Fork a new process to execute command
        pid_t pid = fork();
        if (pid == 0) {
            // Child process executes command
            if (execvp(args[0], args) == -1) {
                printf("execvp failed");
            }
            exit(0);
        } else if (pid > 0) {
            // Parent process waits for child to complete
            waitpid(pid, NULL, 0);
        } else {
            printf("fork failed");
        }

        // Reset client socket
        fflush(stdout);
        fflush(stderr);
    }
    close(newSocket);
}

int main() {
    int welcomeSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(6674);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    /*---- Bind the address struct to the socket ----*/
    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    /*---- Listen on the socket, with 5 max connection requests queued ----*/
    if (listen(welcomeSocket, 5) == 0) {
        printf("Listening on port %d\n", 6674);
    } else {
        printf("Error\n");
    }

    // Server loop to accept multiple clients
    while (1) {
        addr_size = sizeof serverStorage;
        newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

        // Fork a child process to handle the client
        if (fork() == 0) { // Child process
            close(welcomeSocket);
            handle_client(newSocket);
            exit(0);
        } else {  // Parent process
            close(newSocket);
            // Clean up zombie processes
            waitpid(-1, NULL, WNOHANG);
        }
    }

    close(welcomeSocket);

    return 0;
}