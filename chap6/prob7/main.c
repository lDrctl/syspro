#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "How to use: %s file\n", argv[0]);
        exit(1);
    }

    if (unlink(argv[1]) == -1) {
        perror(argv[1]);
        exit(1);
    }

    exit(0);
}

