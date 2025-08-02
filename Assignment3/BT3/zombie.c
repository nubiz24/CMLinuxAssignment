// zombie.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

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
        printf("Tiến trình con (PID=%d) thoát ngay.\n", getpid());
        exit(0); // kết thúc ngay
    }
    else
    {
        // Tiến trình cha
        printf("Tiến trình cha (PID=%d) tạo tiến trình con PID=%d.\n", getpid(), pid);
        printf("Tiến trình cha sleep 20 giây, KHÔNG gọi wait().\n");
        sleep(20); // Không gọi wait() → con thành zombie
    }
    return 0;
}
