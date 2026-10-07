#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    close(fd);

    int totalLine = row;
    printf("File read success\n");
    printf("Total Line : %d\n", totalLine);
    printf("You can choose 1 ~ %d Line\n", totalLine);
    printf("Pls 'Enter' the line to select : ");

    char input[100];
    scanf("%s", input);

    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < totalLine; i++) {
            printf("%s\n", savedText[i]);
        }
    } 
    else if (strchr(input, '-')) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        for (int i = start - 1; i <= end - 1; i++) {
            if (i >= 0 && i < totalLine) {
                printf("%s\n", savedText[i]);
            }
        }
    } 
    else if (strchr(input, ',')) {
        char *token = strtok(input, ",");
        while (token != NULL) {
            int lineNum = atoi(token);
            if (lineNum > 0 && lineNum <= totalLine) {
                printf("%s\n", savedText[lineNum - 1]);
            }
            token = strtok(NULL, ",");
        }
    } 
    else {
        int lineNum = atoi(input);
        if (lineNum > 0 && lineNum <= totalLine) {
            printf("%s\n", savedText[lineNum - 1]);
        }
    }

    return 0;
}
