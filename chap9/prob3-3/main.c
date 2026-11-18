
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid, child;
    int status;

    if (argc < 2) {
        printf("Usage: %s command [arguments]\n", argv[0]);
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        execvp(argv[1], &argv[1]);
        fprintf(stderr, "%s: execution failed\n", argv[1]);
        exit(1);
    }

    child = wait(&status);

    if (child == -1) {
        perror("wait failed");
        return 1;
    }

    printf("[%d] child process %d end\n",
           (int)getpid(), (int)child);

    if (WIFEXITED(status))
        printf("end code %d\n", WEXITSTATUS(status));

    return 0;
}

