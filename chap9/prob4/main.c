
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int system(const char *cmdstring)
{
    pid_t pid;
    int status;

    if (cmdstring == NULL)
        return 1;

    pid = fork();

    if (pid < 0)
        return -1;

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c",
              cmdstring, (char *)NULL);
        _exit(127);
    }

    while (waitpid(pid, &status, 0) == -1) {
        if (errno != EINTR)
            return -1;
    }

    return status;
}

int main(void)
{
    int status;

    status = system("date");

    if (status < 0)
        perror("system failed");
    else if (WIFEXITED(status))
        printf("end code %d\n", WEXITSTATUS(status));

    status = system("hello");

    if (status < 0)
        perror("system failed");
    else if (WIFEXITED(status))
        printf("end code %d\n", WEXITSTATUS(status));

    status = system("who; exit 44");

    if (status < 0)
        perror("system failed");
    else if (WIFEXITED(status))
        printf("end code %d\n", WEXITSTATUS(status));

    return 0;
}

