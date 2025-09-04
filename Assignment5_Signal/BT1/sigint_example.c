#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t sigint_count = 0; // Biến đếm toàn cục, an toàn cho signal handler

// Hàm xử lý tín hiệu
void handle_sigint(int sig)
{
    sigint_count++;
    printf("\nSIGINT received (%d)\n", sigint_count);

    if (sigint_count >= 3)
    {
        printf("Đã nhận SIGINT 3 lần. Kết thúc chương trình.\n");
        exit(0);
    }
}

int main()
{
    // Đăng ký hàm xử lý cho tín hiệu SIGINT
    signal(SIGINT, handle_sigint);

    printf("Chương trình đang chạy. Nhấn Ctrl+C để gửi SIGINT.\n");

    // Vòng lặp vô hạn để chương trình còn sống
    while (1)
    {
        printf("Đang chạy...\n");
        sleep(2);
    }

    return 0;
}
