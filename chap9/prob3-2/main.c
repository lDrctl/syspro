
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    printf("parental process start\n");
    fflush(stdout);

    if (fork() == 0) {
        execl("/bin/echo", "echo", "hello", (char *)NULL);
        fprintf(stderr, "first exec failed\n");
        exit(1);
    }

    if (fork() == 0) {
        execl("/bin/date", "date", (char *)NULL);
        fprintf(stderr, "second exec failed\n");
        exit(2);
    }

    if (fork() == 0) {
        execl("/bin/ls", "ls", "-l", (char *)NULL);
        fprintf(stderr, "third exec failed\n");
        exit(3);
    }

    printf("parental process end\n");

    return 0;
}

