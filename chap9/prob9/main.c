
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAXLINE 1024
#define MAXARG 64

/* Remove leading and trailing spaces */
static char *trim(char *s)
{
    char *end;

    while (isspace((unsigned char)*s))
        s++;

    end = s + strlen(s);

    while (end > s && isspace((unsigned char)end[-1]))
        end--;

    *end = '\0';
    return s;
}

/* Execute a single command */
static void run_command(char *command)
{
    char *args[MAXARG];
    char *tok, *saveptr = NULL;
    char *input = NULL, *output = NULL;
    int argc = 0, background = 0, fd;
    pid_t pid;
    size_t n;

    command = trim(command);
    n = strlen(command);

    if (n == 0)
        return;

    if (command[n - 1] == '&') {
        background = 1;
        command[n - 1] = '\0';
    }

    for (tok = strtok_r(command, " \t\r\n", &saveptr);
         tok != NULL;
         tok = strtok_r(NULL, " \t\r\n", &saveptr)) {

        if (strcmp(tok, "<") == 0 ||
            strcmp(tok, ">") == 0) {

            int is_input = (tok[0] == '<');

            tok = strtok_r(NULL, " \t\r\n", &saveptr);

            if (tok == NULL) {
                fprintf(stderr, "Missing filename\n");
                return;
            }

            if (is_input)
                input = tok;
            else
                output = tok;
        }
        else {
            if (argc >= MAXARG - 1) {
                fprintf(stderr, "Too many arguments\n");
                return;
            }

            args[argc++] = tok;
        }
    }

    if (argc == 0)
        return;

    args[argc] = NULL;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        if (input != NULL) {
            fd = open(input, O_RDONLY);

            if (fd < 0) {
                perror("open input");
                _exit(1);
            }

            if (dup2(fd, STDIN_FILENO) < 0) {
                perror("dup2 input");
                _exit(1);
            }

            close(fd);
        }

        if (output != NULL) {
            fd = open(output,
                      O_CREAT | O_WRONLY | O_TRUNC,
                      0644);

            if (fd < 0) {
                perror("open output");
                _exit(1);
            }

            if (dup2(fd, STDOUT_FILENO) < 0) {
                perror("dup2 output");
                _exit(1);
            }

            close(fd);
        }

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

int main(void)
{
    char line[MAXLINE];
    char *cmd, *saveptr;

    while (1) {
        while (waitpid(-1, NULL, WNOHANG) > 0) {}

        printf("[shell] ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        saveptr = NULL;

        for (cmd = strtok_r(line, ";", &saveptr);
             cmd != NULL;
             cmd = strtok_r(NULL, ";", &saveptr)) {

            cmd = trim(cmd);

            if (strcmp(cmd, "exit") == 0)
                return 0;

            run_command(cmd);
        }
    }

    return 0;
}

