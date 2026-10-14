
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int newmode;

    if (argc != 3) {
        fprintf(stderr, "How to use: %s mode file\n", argv[0]);
        exit(1);
    }

    newmode = (int)strtol(argv[1], NULL, 8);

    if (chmod(argv[2], newmode) == -1) {
        perror(argv[2]);
        exit(1);
    }

    exit(0);
}

