#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_THREADS 3
#define N_INCREMENTS 1000000

long long counter = 0;         // Biến toàn cục chia sẻ
pthread_mutex_t counter_mutex; // Khai báo mutex

void *increment_counter(void *arg)
{
    for (int i = 0; i < N_INCREMENTS; i++)
    {
        pthread_mutex_lock(&counter_mutex);   // Khóa mutex trước khi truy cập
        counter++;                            // Tăng biến toàn cục
        pthread_mutex_unlock(&counter_mutex); // Mở khóa sau khi dùng xong
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[N_THREADS];

    // Khởi tạo mutex
    if (pthread_mutex_init(&counter_mutex, NULL) != 0)
    {
        printf("Không thể khởi tạo mutex!\n");
        return 1;
    }

    // Tạo 3 luồng
    for (int i = 0; i < N_THREADS; i++)
    {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0)
        {
            printf("Không thể tạo luồng %d\n", i);
            return 1;
        }
    }

    // Chờ tất cả luồng kết thúc
    for (int i = 0; i < N_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // In kết quả cuối cùng
    printf("Giá trị cuối cùng của counter: %lld\n", counter);

    // Hủy mutex
    pthread_mutex_destroy(&counter_mutex);

    return 0;
}
