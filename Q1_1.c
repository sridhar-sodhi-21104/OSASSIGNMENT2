#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sched.h>

void *countA()
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
    unsigned long long i = 0;
    while (i != 4294967295)
    {
        i++;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double totalrt = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("The runtime of A is %f seconds\n", totalrt);

    return 0;
}
void *countB()
{
    struct timespec start;
    struct timespec end;
    struct sched_param *B = (struct sched_param *)malloc(sizeof(struct sched_param));
    if (B != NULL)
    {
        B->sched_priority = 1;
    }
    pthread_setschedparam(pthread_self(), SCHED_RR, B);
    clock_gettime(CLOCK_REALTIME, &start);
    unsigned long long i = 0;
    while (i != 4294967295)
    {
        i++;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double totalrt = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("The runtime  of B is %f seconds\n", totalrt);

    return 0;
}
void *countC()
{
    struct timespec start;
    struct timespec end;
    struct sched_param *C = (struct sched_param *)malloc(sizeof(struct sched_param));
    if (C != NULL)
    {
        C->sched_priority = 1;
    }

    pthread_setschedparam(pthread_self(), SCHED_FIFO, C);
    clock_gettime(CLOCK_REALTIME, &start);
    unsigned long long i = 0;
    while (i != 4294967295)
    {
        i++;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double totalrt = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("The runtime of C is %f seconds\n", totalrt);

    return 0;
}
int main()
{
    pthread_t p1;
    pthread_t p2;
    pthread_t p3;
    if (pthread_create(&p1, NULL, &countA, NULL) != 0)
    {
        perror("FAILED TO CREATE THREAD");
        return 1;
    }

    if (pthread_create(&p2, NULL, &countB, NULL) != 0)
    {
        perror("FAILED TO CREATE THREAD");
        return 1;
    }
    if (pthread_create(&p3, NULL, &countC, NULL) != 0)
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
