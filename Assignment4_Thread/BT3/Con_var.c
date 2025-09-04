#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // sleep()

// Biến chia sẻ
int data = 0;
int data_ready = 0;

// Mutex và condition variable
pthread_mutex_t mutex;
pthread_cond_t cond;

// Producer
void *producer(void *arg)
{
    for (int i = 0; i < 10; i++)
    {
        int value = rand() % 100; // Tạo số ngẫu nhiên

        pthread_mutex_lock(&mutex);

        // Đặt dữ liệu mới
        data = value;
        data_ready = 1;

        printf("[Producer] Sinh ra dữ liệu: %d\n", value);

        // Báo hiệu cho Consumer biết
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);

        sleep(1); // giả lập thời gian sinh dữ liệu
    }
    return NULL;
}

// Consumer
void *consumer(void *arg)
{
    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mutex);

        // Chờ cho đến khi có dữ liệu
        while (!data_ready)
        {
            pthread_cond_wait(&cond, &mutex);
        }

        // Đọc dữ liệu
        printf("    [Consumer] Nhận dữ liệu: %d\n", data);

        // Đánh dấu đã xử lý xong
        data_ready = 0;

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t prod_thread, cons_thread;

    // Khởi tạo mutex và condition
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // Tạo luồng producer và consumer
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Chờ các luồng kết thúc
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Hủy mutex và condition
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("Chương trình kết thúc.\n");
    return 0;
}
