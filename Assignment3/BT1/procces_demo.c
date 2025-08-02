#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        // lỗi khi tạo tiến trình con
        perror("fork thất bại");
        return 1;
    }

    if (child_pid == 0)
    {
        // Đây là tiến trình con
        printf("Tiến trình con: PID = %d, PPID = %d\n", getpid(), getppid());
        // Thực hiện một số việc nếu cần, sau đó thoát với mã 10
        exit(10);
        // hoặc _exit(10); // nếu muốn bỏ qua flush của stdio
    }
    else
    {
        // Đây là tiến trình cha
        printf("Tiến trình cha: PID = %d, PID của con = %d\n", getpid(), child_pid);

        int status;
        pid_t w = wait(&status); // chờ tiến trình con kết thúc

        if (w == -1)
        {
            perror("wait thất bại");
            return 1;
        }

        if (WIFEXITED(status))
        {
            int exit_code = WEXITSTATUS(status);
            printf("Tiến trình con (PID = %d) kết thúc bình thường với mã thoát = %d\n", w, exit_code);
        }
        else if (WIFSIGNALED(status))
        {
            int sig = WTERMSIG(status);
            printf("Tiến trình con (PID = %d) bị kết thúc bởi tín hiệu %d\n", w, sig);
        }
        else
        {
            printf("Tiến trình con (PID = %d) kết thúc theo cách khác (không phải exit bình thường)\n", w);
        }
    }

    return 0;
}
