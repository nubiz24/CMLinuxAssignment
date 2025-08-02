// orphan.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork thất bại");
        return 1;
    }

    if (pid == 0)
    {
        // Tiến trình con
        for (int i = 0; i < 5; i++)
        {
            printf("Tiến trình con (PID=%d) có PPID=%d\n", getpid(), getppid());
            sleep(2);
        }
    }
    else
    {
        // Tiến trình cha
        printf("Tiến trình cha (PID=%d) thoát ngay.\n", getpid());
        exit(0); // kết thúc ngay lập tức
    }

    return 0;
}
