#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/select.h>

volatile sig_atomic_t sigint_received = 0;
volatile sig_atomic_t sigterm_received = 0;

// Hàm xử lý tín hiệu
void handle_sigint(int sig)
{
    sigint_received = 1;
}

void handle_sigterm(int sig)
{
    sigterm_received = 1;
}

int main()
{
    // Đăng ký signal handler
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigterm);

    printf("Chương trình bắt đầu. (Ctrl+C để gửi SIGINT, 'kill -TERM <pid>' để thoát)\n");

    while (1)
    {
        // Nếu nhận SIGINT
        if (sigint_received)
        {
            printf("SIGINT received.\n");
            sigint_received = 0; // reset cờ
        }

        // Nếu nhận SIGTERM
        if (sigterm_received)
        {
            printf("SIGTERM received. Thoát chương trình.\n");
            exit(0);
        }

        // Dùng select để chờ dữ liệu nhập từ stdin
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        struct timeval tv;
        tv.tv_sec = 1; // timeout 1 giây
        tv.tv_usec = 0;

        int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

        if (ret > 0 && FD_ISSET(STDIN_FILENO, &readfds))
        {
            char buffer[256];
            if (fgets(buffer, sizeof(buffer), stdin) != NULL)
            {
                buffer[strcspn(buffer, "\n")] = '\0'; // bỏ newline
                printf("Bạn nhập: %s\n", buffer);
            }
        }
        // Nếu ret = 0: timeout, không làm gì (chỉ quay vòng để check tín hiệu)
    }

    return 0;
}
