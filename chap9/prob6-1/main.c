
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    printf("PARENT: PID = %d GID = %d\n",
           (int)getpid(), (int)getpgrp());
    fflush(stdout);

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("CHILD: PID = %d GID = %d\n",
               (int)getpid(), (int)getpgrp());
    }

    return 0;
}

