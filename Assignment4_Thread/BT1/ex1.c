#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Hàm mà luồng sẽ thực thi
void *thread_function(void *arg)
{
    pthread_t tid = pthread_self(); // Lấy ID của luồng hiện tại
    printf("Thread với ID %lu đang chạy!\n", (unsigned long)tid);
    pthread_exit(NULL); // Kết thúc luồng
}

int main()
{
    pthread_t thread1, thread2; // Khai báo hai biến luồng
    int ret;

    // Tạo luồng 1
    ret = pthread_create(&thread1, NULL, thread_function, NULL);
    if (ret != 0)
    {
        printf("Không thể tạo luồng 1\n");
        exit(EXIT_FAILURE);
    }

    // Tạo luồng 2
    ret = pthread_create(&thread2, NULL, thread_function, NULL);
    if (ret != 0)
    {
        printf("Không thể tạo luồng 2\n");
        exit(EXIT_FAILURE);
    }

    // Chờ luồng 1 kết thúc
    pthread_join(thread1, NULL);
    // Chờ luồng 2 kết thúc
    pthread_join(thread2, NULL);

    printf("Cả hai luồng đã kết thúc. Kết thúc chương trình chính.\n");

    return 0;
}
