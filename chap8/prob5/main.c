
#include <stdio.h>
#include <unistd.h>

/* Print process ID and parent process ID */
int main(void)
{
    printf("my process number: [%d]\n", (int)getpid());
    printf("my parent process number: [%d]\n", (int)getppid());

    return 0;
}

