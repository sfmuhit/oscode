#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t mutex;

void* phil(void* num) {
    int i = *(int*)num;
    int left = i;
    int right = (i + 1) % N;
    
    while(1) {
        printf("%d thinking\n", i);
        sleep(1);
        
        sem_wait(&mutex);
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);
        sem_post(&mutex);
        
        printf("%d eating\n", i);
        sleep(1);
        
        sem_post(&forks[left]);
        sem_post(&forks[right]);
    }
}

int main() {
    pthread_t t[N];
    int id[N];
    
    sem_init(&mutex, 0, 1);
    for(int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);
    
    for(int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&t[i], NULL, phil, &id[i]);
    }
    
    for(int i = 0; i < N; i++)
        pthread_join(t[i], NULL);
    
    return 0;
}