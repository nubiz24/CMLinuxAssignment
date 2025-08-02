// orphan.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid > 0)
    {
        // Tiến trình cha thoát ngay
        printf("Parent process (PID=%d) exiting...\n", getpid());
        exit(0);
    }
    else
    {
        // Tiến trình con
        for (int i = 0; i < 5; i++)
        {
            printf("Child PID=%d, PPID=%d\n", getpid(), getppid());
            sleep(2);
        }
    }

    return 0;
}
