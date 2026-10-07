#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd;
    char buf;
    char savedText[10][100] = {0};
    int row = 0, col = 0;

    if (argc < 2) {
        fprintf(stderr, "How to use : %s file\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror("File open error");
        exit(1);
    }
    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[row][col] = '\0';
            row++;
            col = 0;
        } else {
            savedText[row][col] = buf;
            col++;
        }
    }
    
    if (col > 0) {
        savedText[row][col] = '\0';
        row++;
    }
    close(fd);

    int totalLine = row;

    for (int i = totalLine - 1; i >= 0; i--) {
        printf("%s\n", savedText[i]);
    }

    return 0;
}
