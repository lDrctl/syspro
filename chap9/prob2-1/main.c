
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Wait for a child process */
int main(void)
{
    pid_t pid, child;
    int status;

    printf("[%d] parental process start\n", (int)getpid());

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("[%d] child process start\n", (int)getpid());
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

