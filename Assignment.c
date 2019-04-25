#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
sem_t mutualExclusion;
pthread_t thread1, thread2;

void f2() {
    printf("\nF2 called");
}

void f1() {
    printf("\nF1 called");
    pthread_create(&thread2, NULL, f2, NULL);
}

void fa() {
    sem_wait(&mutualExclusion);
    printf("\nThread for fa Entered");
    sleep(4);
    printf("\nThread For fa Done");
    sem_post(&mutualExclusion);
}

void fb() {
    sem_wait(&mutualExclusion);
    printf("\nThread For fb Entered");
    sleep(4);
    printf("\nFunction fb Thread Done");
    sem_post(&mutualExclusion);
}

void fc() {
    sem_wait(&mutualExclusion);
    printf("\nThread for fc Entered ");
    sleep(4);
    printf("\nThread Function fc Done ");
    sem_post(&mutualExclusion);
}

int main() {
    sem_init(&mutualExclusion, 5, 1);

    pthread_create(&thread1, NULL, f1, NULL);
    sleep(6);

    pthread_create(&thread2, NULL, fa, NULL);
    sleep(6);

    pthread_create(&thread1, NULL, fb, NULL);
    sleep(5);

    pthread_create(&thread2, NULL, fc, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\nThreads Executed Successfully");
}
