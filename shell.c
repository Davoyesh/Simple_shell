#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

// Function to parse the command and arguments from user input
void parse_command(char* input, char* command, char** arguments) {
    char* token = strtok(input, " ");
    strcpy(command, token);
    int i = 0;
    while (token != NULL && i < MAX_ARGUMENTS) {
        arguments[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    arguments[i] = NULL;
}

// Function to execute the command
void execute_command(char* command, char** arguments) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execvp(command, arguments);
        // If execvp returns, there was an error
        perror("Error executing command");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    } else {
        // Fork failed
        perror("Error forking process");
        exit(1);
    }
}

int main(void) {
    char input[MAX_COMMAND_LENGTH];
    char command[MAX_COMMAND_LENGTH];
    char* arguments[MAX_ARGUMENTS];

    while (1) {
        printf("shell$ ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }
        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';
        parse_command(input, command, arguments);
        execute_command(command, arguments);
    }

    return 0;
}
