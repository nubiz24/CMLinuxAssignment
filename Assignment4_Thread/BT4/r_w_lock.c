#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

int shared_data = 0;     // Tài nguyên chia sẻ
pthread_rwlock_t rwlock; // Read-Write Lock

void *reader(void *arg)
{
    int id = *((int *)arg);
    for (int i = 0; i < 5; i++)
    {
        pthread_rwlock_rdlock(&rwlock); // Khóa đọc
        printf("📖 Reader %d đọc giá trị: %d\n", id, shared_data);
        pthread_rwlock_unlock(&rwlock); // Mở khóa
        usleep(200000);                 // 0.2s để mô phỏng thời gian đọc
    }
    return NULL;
}

void *writer(void *arg)
{
    int id = *((int *)arg);
    for (int i = 0; i < 5; i++)
    {
        pthread_rwlock_wrlock(&rwlock); // Khóa ghi (độc quyền)
        shared_data++;
        printf("✍️  Writer %d ghi, giá trị mới: %d\n", id, shared_data);
        pthread_rwlock_unlock(&rwlock); // Mở khóa
        usleep(500000);                 // 0.5s để mô phỏng thời gian ghi
    }
    return NULL;
}

int main()
{
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    pthread_rwlock_init(&rwlock, NULL);

    // Tạo các Reader
    for (int i = 0; i < NUM_READERS; i++)
    {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Tạo các Writer
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Chờ Reader kết thúc
    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    // Chờ Writer kết thúc
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        pthread_join(writers[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    printf("✅ Chương trình kết thúc, giá trị cuối cùng: %d\n", shared_data);
    return 0;
}
