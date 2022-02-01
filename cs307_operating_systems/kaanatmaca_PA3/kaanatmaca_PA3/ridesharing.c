#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

// Kaan Atmaca 28239

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int totalInCar = 0;
int totalAInCar = 0;
int totalBInCar = 0;
int count = 0;
sem_t sema;
sem_t semb;
int A, B;

void *findCarA(void *pid)
{
    pthread_mutex_lock(&mut);
    unsigned long tid;
    tid = *((unsigned long *)pid);
    printf("Thread ID: %ld, Team: A, I am looking for a car\n", tid);
    totalInCar++;
    totalAInCar++;

    if (totalInCar >= 4 && totalAInCar >= 4)
    {
        totalInCar -= 4;
        totalAInCar -= 4;
        for (int i = 0; i < 3; i++)
            sem_post(&sema);
    }
    else if (totalInCar >= 4 && totalAInCar >= 2 && totalBInCar >= 2)
    {
        totalInCar -= 4;
        totalAInCar -= 2;
        totalBInCar -= 2;
        sem_post(&sema);
        for (int i = 0; i < 2; i++)
            sem_post(&semb);
    }
    else
    {
        pthread_mutex_unlock(&mut);
        sem_wait(&sema);
        pthread_mutex_lock(&mut);
    }
    count++;
    printf("Thread ID: %ld, Team: A, I have found a spot in a car\n", tid);
    if (count % 4 == 0)
    {
        printf("Thread ID: %ld, Team: A, I am the captain and driving the car\n", tid);
    }
    pthread_mutex_unlock(&mut);
}

void *findCarB(void *pid)
{
    pthread_mutex_lock(&mut);
    unsigned long tid;
    tid = *((unsigned long *)pid);
    printf("Thread ID: %ld, Team: B, I am looking for a car\n", tid);

    totalInCar++;
    totalBInCar++;

    if (totalInCar >= 4 && totalBInCar >= 4)
    {
        totalInCar -= 4;
        totalBInCar -= 4;
        for (int i = 0; i < 3; i++)
            sem_post(&semb);
    }
    else if (totalInCar >= 4 && totalAInCar >= 2 && totalBInCar >= 2)
    {
        totalInCar -= 4;
        totalAInCar -= 2;
        totalBInCar -= 2;
        sem_post(&semb);
        for (int i = 0; i < 2; i++)
            sem_post(&sema);
    }

    else
    {
        pthread_mutex_unlock(&mut);
        sem_wait(&semb);
        pthread_mutex_lock(&mut);
    }
    count++;
    printf("Thread ID: %ld, Team: B, I have found a spot in a car\n", tid);
    if (count % 4 == 0)
    {
        printf("Thread ID: %ld, Team: B, I am the captain and driving the car\n", tid);
    }
    pthread_mutex_unlock(&mut);
}

int main(int argc, char *argv[])
{
    sem_init(&sema, 0, 0);
    sem_init(&semb, 0, 0);
    int a, b;
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    A = a;
    B = b;
    int totalThreads = a + b;
    if (totalThreads % 4 == 0 && a % 2 == 0 && b % 2 == 0)
    {
        int totalCars = totalThreads / 4;
        pthread_t teamA[a];
        pthread_t teamB[b];
        int totalInCar = 0;
        for (int i = 0; i < a; i++) // creating threads
        {
            pthread_create(&teamA[i], NULL, findCarA, &teamA[i]);
        }

        for (int i = 0; i < b; i++) // creating threads
        {
            pthread_create(&teamB[i], NULL, findCarB, &teamB[i]);
        }
        for (int i = 0; i < a; i++) // joining threads
        {
            pthread_join(teamA[i], NULL);
        }
        for (int i = 0; i < b; i++) // joining threads
        {
            pthread_join(teamB[i], NULL);
        }
    }
    sem_destroy(&sema);
    sem_destroy(&semb);
    printf("The main terminates\n");
    return 0;
}