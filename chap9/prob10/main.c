
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAXLINE 1024
#define MAXARG 64

int main(void)
{
    char line[MAXLINE];
    char *args[MAXARG];
    char *tok, *saveptr;
    int argc, background;
    pid_t pid;

    while (1) {
        while (waitpid(-1, NULL, WNOHANG) > 0) {}

        printf("[shell] ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        argc = 0;
        saveptr = NULL;

        tok = strtok_r(line, " \t\r\n", &saveptr);

        while (tok != NULL && argc < MAXARG - 1) {
            args[argc++] = tok;
            tok = strtok_r(NULL, " \t\r\n", &saveptr);
        }

        if (argc == 0)
            continue;

        args[argc] = NULL;

        if (strcmp(args[0], "exit") == 0)
            break;

        background = 0;

        if (strcmp(args[argc - 1], "&") == 0) {
            background = 1;
            args[--argc] = NULL;

            if (argc == 0)
                continue;
        }

        pid = fork();

        if (pid < 0) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            _exit(127);
        }

        if (background) {
            printf("[background] %ld\n", (long)pid);
        }
        else {
            while (waitpid(pid, NULL, 0) < 0) {
                if (errno != EINTR) {
                    perror("waitpid");
                    break;
                }
            }
        }
    }

    return 0;
}

