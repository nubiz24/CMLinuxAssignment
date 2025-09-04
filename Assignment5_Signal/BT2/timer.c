#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t counter = 0; // Biến đếm an toàn cho signal handler

// Hàm xử lý tín hiệu SIGALRM
void handle_sigalrm(int sig)
{
    counter++;
    printf("Timer: %d seconds\n", counter);

    if (counter >= 10)
    {
        printf("Đã đếm đủ 10 giây. Kết thúc chương trình.\n");
        exit(0);
    }

    alarm(1); // Đặt lại báo động sau 1 giây để tiếp tục đếm
}

int main()
{
    // Đăng ký hàm xử lý cho tín hiệu SIGALRM
    signal(SIGALRM, handle_sigalrm);

    printf("Bắt đầu bộ đếm thời gian...\n");

    alarm(1); // Bắt đầu đếm giây đầu tiên

    // Vòng lặp vô hạn để chương trình còn sống chờ tín hiệu
    while (1)
    {
        pause(); // Tạm dừng tiến trình cho đến khi có tín hiệu
    }

    return 0;
}
