
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid1, pid2, child;
    int status;

    printf("[%d] parental process start\n", (int)getpid());

    pid1 = fork();

    if (pid1 < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid1 == 0) {
        printf("[%d] child process[1] start\n", (int)getpid());
        sleep(1);
        printf("[%d] child process[1] end\n", (int)getpid());
        exit(1);
    }

    pid2 = fork();

    if (pid2 < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid2 == 0) {
        printf("[%d] child process[2] start\n", (int)getpid());
        sleep(2);
        printf("[%d] child process[2] end\n", (int)getpid());
        exit(2);
    }

    child = waitpid(pid1, &status, 0);

    if (child == -1) {
        perror("waitpid failed");
        return 1;
    }

    printf("[%d] child process[1] %d end\n",
           (int)getpid(), (int)child);

    if (WIFEXITED(status))
        printf("end code %d\n", WEXITSTATUS(status));

    return 0;
}

