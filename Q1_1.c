#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sched.h>

void countA()
{
    unsigned long long i = 0;
    while (i != 4294967295)
    {
        i++;
    }
}
void countB()
{
    unsigned long long int i = 0;
    while (i != 4294967295)
    {
        i++;
    }
}
void countC()
{
    unsigned long long int i = 0;
    while (i != 4294967295)
    {
        i++;
    }
}
void *thr_A()
{
    struct timespec start;
    struct timespec end;
    struct sched_param *A = (struct sched_param *)malloc(sizeof(struct sched_param));
    if (A != NULL)
    {
        A->sched_priority = 0;
    }
    nice(0);
    pthread_setschedparam(pthread_self(), SCHED_OTHER, A);
    clock_gettime(CLOCK_REALTIME, &start);
    countA();
    clock_gettime(CLOCK_REALTIME, &end);
    double totalrt = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("The runtime is %f seconds\n", totalrt);

    return 0;
}
void *thr_B()
{
    struct timespec start;
    struct timespec end;
    struct sched_param *B = (struct sched_param *)malloc(sizeof(struct sched_param));
    if (B != NULL)
    {
        B->sched_priority = 0;
    }
    pthread_setschedparam(pthread_self(), SCHED_RR, B);
    clock_gettime(CLOCK_REALTIME, &start);
    countB();
    clock_gettime(CLOCK_REALTIME, &end);
    double totalrt = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("The runtime is %f seconds\n", totalrt);

    return 0;
}
void *thr_C()
{
    struct timespec start;
    struct timespec end;
    struct sched_param *C = (struct sched_param *)malloc(sizeof(struct sched_param));
    if (C != NULL)
    {
        C->sched_priority = 0;
    }

    pthread_setschedparam(pthread_self(), SCHED_FIFO, C);
    clock_gettime(CLOCK_REALTIME, &start);
    countC();
    clock_gettime(CLOCK_REALTIME, &end);
    double totalrt = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("The runtime is %f seconds\n", totalrt);

    return 0;
}
int main()
{
    pthread_t p1;
    pthread_t p2;
    pthread_t p3;
    if (pthread_create(&p1, NULL, &thr_A, NULL) != 0)
    {
        perror("FAILED TO CREATE THREAD");
        return 1;
    }

    if (pthread_create(&p2, NULL, &thr_B, NULL) != 0)
    {
        perror("FAILED TO CREATE THREAD");
        return 1;
    }
    if (pthread_create(&p3, NULL, &thr_C, NULL) != 0)
    {
        perror("FAILED TO CREATE THREAD");
        return 1;
    }
    if (pthread_join(p1, NULL) != 0)
    {
        return 1;
    }
    if (pthread_join(p2, NULL) != 0)
    {
        return 1;
    }
    if (pthread_join(p3, NULL) != 0)
    {
        return 1;
    }
    return 0;
}