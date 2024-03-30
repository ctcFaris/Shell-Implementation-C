#define _GNU_SOURCE // clone() function requirement
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>

void child_thread(void *arg) {
    printf("Child thread executing...\n");
    printf("Child thread ID: %ld\n", (long)getpid());
    
    char *envp[] = {"PATH=/bin", "USER=child", NULL};
    execle("/bin/echo", "echo", "Hello from the child thread!", NULL, envp);

    perror("Execle failed");
    exit(EXIT_FAILURE);
}

int main() {
    const int STACK_SIZE = 65536;
    char *stack = malloc(STACK_SIZE);
    if (stack == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Cast the function pointer to the appropriate type
    pid_t pid = clone((int (*)(void *))child_thread, stack + STACK_SIZE, CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD, NULL);
    if (pid == -1) {
        perror("Clone failed");
        exit(EXIT_FAILURE);
    }

    printf("Parent process waiting for child thread to finish...\n");

    waitpid(pid, NULL, 0);
    printf("Parent process exiting...\n");

    free(stack);

    return 0;
}
