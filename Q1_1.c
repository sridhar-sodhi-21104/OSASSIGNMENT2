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

    printf("The runtime of thread A is %f seconds\n", totalrt);
    pthread_exit(NULL);

    return 0;
}
void *thr_B()
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
    countB();
    clock_gettime(CLOCK_REALTIME, &end);
    double totalrt = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("The runtime of thread B is %f seconds\n", totalrt);
    pthread_exit(NULL);

    return 0;
}
void *thr_C()
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
    countC();
    clock_gettime(CLOCK_REALTIME, &end);
    double totalrt = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("The runtime of Thread C is %f seconds\n", totalrt);
    pthread_exit(NULL);

    return 0;
}
int main()
{
    pthread_t p1;
    pthread_t p2;
    pthread_t p3;
    pthread_attr_t attr1, attr2, attr3;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);
    printf("1\n");
    int check1 = pthread_create(&p1, &attr1, thr_A, NULL);
    if (check1 != 0)
    {
        perror("FAILED TO CREATE THREAD");
        return 1;
    }
    printf("2\n");
    int check2 = pthread_create(&p2, &attr2, thr_B, NULL);
    if (check2 != 0)
    {
        perror("FAILED TO CREATE THREAD");
        return 1;
    }
    printf("3\n");
    int check3 = pthread_create(&p3, &attr3, thr_C, NULL);
    if (check3 != 0)
    {
        perror("FAILED TO CREATE THREAD");
        return 1;
    }
        printf("4\n");
    return 0;
}
