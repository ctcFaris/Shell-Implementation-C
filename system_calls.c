#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // Fork a child process called pid
    pid = fork();

    if (pid < 0) {
	//Child process failure...
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process success...
        printf("Child process executing...\n");

        // Execute another program using exec
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);

        // If execvp returns, that means it surely failed
        perror("Execvp failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        printf("Parent process waiting for child to finish...\n");

        // Wait for child process  to terminate
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Exited child process with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Terminated child process \n");
        }
    }

    return 0;
}

