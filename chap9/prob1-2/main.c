
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Create a child process */
int main(void)
{
    int pid;

    pid = fork();

    if (pid == 0) {
        printf("[Child] Hello, world! Pid=%d\n",
               (int)getpid());
    }
    else {
        printf("[Parent] Hello, world! Pid=%d\n",
               (int)getpid());
    }

    return 0;
}

