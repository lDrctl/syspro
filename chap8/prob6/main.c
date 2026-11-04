
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

/* Print user ID and group ID */
int main(void)
{
    printf("Real User ID: %d(%s)\n",
           (int)getuid(), getpwuid(getuid())->pw_name);

    printf("Effective User ID: %d(%s)\n",
           (int)geteuid(), getpwuid(geteuid())->pw_name);

    printf("Real Group ID: %d(%s)\n",
           (int)getgid(), getgrgid(getgid())->gr_name);

    printf("Effective Group ID: %d(%s)\n",
           (int)getegid(), getgrgid(getegid())->gr_name);

    return 0;
}

