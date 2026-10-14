#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "How to use: %s file1 file2\n", argv[0]);
        exit(1);
    }

    if (access(argv[1], F_OK) == -1) {
        perror(argv[1]);
        exit(1);
    }

    if (symlink(argv[1], argv[2]) == -1) {
        perror(argv[2]);
        exit(1);
    }

    exit(0);
}

