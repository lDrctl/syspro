
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

int main(int argc, char *argv[])
{
    char **ptr;
    char *value;

    if (argc < 2) {
        printf("Usage: %s -e [NAME] | -u | -g | -i | -p\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-e") == 0) {
        if (argc == 2) {
            for (ptr = environ; *ptr != NULL; ptr++)
                printf("%s\n", *ptr);
        }
        else if (argc == 3) {
            value = getenv(argv[2]);

            if (value != NULL)
                printf("%s = %s\n", argv[2], value);
            else
                printf("Environment variable not found\n");
        }
        else {
            printf("Invalid arguments\n");
            return 1;
        }
    }
    else if (strcmp(argv[1], "-u") == 0 && argc == 2) {
        printf("Real User ID: %d(%s)\n",
               (int)getuid(), getpwuid(getuid())->pw_name);

        printf("Effective User ID: %d(%s)\n",
               (int)geteuid(), getpwuid(geteuid())->pw_name);
    }
    else if (strcmp(argv[1], "-g") == 0 && argc == 2) {
        printf("Real Group ID: %d(%s)\n",
               (int)getgid(), getgrgid(getgid())->gr_name);

        printf("Effective Group ID: %d(%s)\n",
               (int)getegid(), getgrgid(getegid())->gr_name);
    }
    else if (strcmp(argv[1], "-i") == 0 && argc == 2) {
        printf("My Process ID: [%d]\n", (int)getpid());
    }
    else if (strcmp(argv[1], "-p") == 0 && argc == 2) {
        printf("My Parent Process ID: [%d]\n", (int)getppid());
    }
    else {
        printf("Invalid option\n");
        return 1;
    }

    return 0;
}

