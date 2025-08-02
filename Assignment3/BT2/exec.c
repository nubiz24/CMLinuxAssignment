#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    // Thiết lập biến môi trường MY_COMMAND
    if (setenv("MY_COMMAND", "ls", 1) != 0)
    {
        perror("setenv thất bại");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork thất bại");
        return 1;
    }

    if (pid == 0)
    {
        // Tiến trình con
        char *cmd = getenv("MY_COMMAND"); // Đọc biến môi trường
        if (cmd == NULL)
        {
            fprintf(stderr, "Không tìm thấy biến môi trường MY_COMMAND\n");
            exit(1);
        }

        printf("Tiến trình con: PID=%d, thực thi lệnh '%s'\n", getpid(), cmd);

        // Thay thế mã thực thi bằng lệnh trong cmd
        execlp(cmd, cmd, (char *)NULL);

        // Nếu exec() thất bại:
        perror("exec thất bại");
        exit(1);
    }
    else
    {
        // Tiến trình cha
        int status;
        wait(&status);
        printf("Tiến trình cha: PID=%d, tiến trình con PID=%d đã kết thúc\n", getpid(), pid);
    }

    return 0;
}
