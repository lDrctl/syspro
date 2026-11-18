
#include <stdio.h>
#include <unistd.h>

/* Create a child process */
int main(void)
{
    int pid;

    printf("[%d] Process start\n", (int)getpid());

    pid = fork();

    printf("[%d] Process : return value %d\n",
           (int)getpid(), pid);

    return 0;
}

