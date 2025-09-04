#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

volatile sig_atomic_t received_count = 0; // biến đếm số tín hiệu con nhận được

// Hàm xử lý tín hiệu ở process con
void handle_sigusr1(int sig)
{
    received_count++;
    printf("Child: Received signal from parent (%d)\n", received_count);
}

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // === Process con ===
        signal(SIGUSR1, handle_sigusr1); // Đăng ký handler cho SIGUSR1
        printf("Child: PID = %d, waiting for signals...\n", getpid());

        // Vòng lặp chờ tín hiệu từ cha
        while (1)
        {
            pause(); // Dừng tiến trình cho đến khi nhận tín hiệu
        }
    }
    else
    {
        // === Process cha ===
        printf("Parent: PID = %d, sending signals to child PID = %d\n", getpid(), pid);

        for (int i = 0; i < 5; i++)
        {
            sleep(2);           // chờ 2 giây
            kill(pid, SIGUSR1); // gửi tín hiệu cho con
            printf("Parent: Sent SIGUSR1 to child (%d/5)\n", i + 1);
        }

        printf("Parent: Finished sending 5 signals. Exiting.\n");
        exit(0);
    }

    return 0;
}
