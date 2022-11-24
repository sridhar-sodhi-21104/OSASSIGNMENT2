#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>

void callfork(int a)
{
    if (a == 1)
    {
        pid_t p1;
        struct timespec start;
        struct timespec end;
        clock_gettime(CLOCK_REALTIME, &start);
        p1 = fork();
        struct sched_param *A = (struct sched_param)malloc(sizeof(struct sched_param));
        if (A != NULL)
        {
            A->sched_priority = 0;
        }
        sched_setscheduler(p1, SCHED_OTHER, A);
        if (p1 < 0)
        {
            printf("Fork failed\n");
            exit(1);
        }
        else if (p1 == 0)
        {
            execlp("/bin/bash", "sh", "bash1.sh", NULL);
        }
        else
        {
            int check = waitpid(p1, 0, 0);
            clock_gettime(CLOCK_REALTIME, &end);
            double totalrt = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
            FILE *outputfile = fopen("result.txt", "a");
            printf("The runtime is %lf seconds\n", totalrt);
            fprintf(result, "FIRST: %lf\n", totalrt);
            fclose(result);
        }
    }
    else if (a == 2)
    {
        pid_t p2;
        struct timespec start;
        struct timespec end;
        clock_gettime(CLOCK_REALTIME, &start);
        p2 = fork();
        struct sched_param *B = (struct sched_param *)malloc(sizeof(struct sched_param));
        if (B != NULL)
        {
            B->sched_priority = 1;
        }
        sched_setscheduler(p2, SCHED_FIFO, B);
        if (p2 < 0)
        {
            printf("Fork failed\n");
            exit(1);
        }
        else if (p2 == 0)
        {
            execlp("/bin/bash", "sh", "bash2.sh", NULL);
        }
        else
        {
            int check = waitpid(p2, 0, 0);
            clock_gettime(CLOCK_REALTIME, &end);
            double totalrt = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
            FILE *outputfile = fopen("result.txt", "a");
            printf("The runtime is %lf seconds\n", totalrt);
            fprintf(result, "SECOND: %lf\n", totalrt);
            fclose(result);
        }
    }
    else if (a == 3)
    {
        pid_t p3;
        struct timespec start;
        struct timespec end;
        clock_gettime(CLOCK_REALTIME, &start);
        p3 = fork();
        struct sched_param *C = (struct sched_param *)malloc(sizeof(struct sched_param));
        if (C != NULL)
        {
            C->sched_priority = 1;
        }
        sched_setscheduler(p3, SCHED_RR, C);
        if (p3 < 0)
        {
            printf("Fork failed\n");
            exit(1);
        }
        else if (p3 == 0)
        {
            execlp("/bin/bash", "sh", "bash3.sh", NULL);
        }
        else
        {
            int check = waitpid(p3, 0, 0);
            clock_gettime(CLOCK_REALTIME, &end);
            double totalrt = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
            FILE *outputfile = fopen("result.txt", "a");
            printf("The runtime is %lf seconds\n", totalrt);
            fprintf(result, "THIRD: %lf\n", totalrt);
            fclose(result);
        }
    }
}
int main()
{

    pid_t pid1 = fork();
    if (pid1 < 0)
    {
        printf("Fork failed\n");
        exit(1);
    }
    if (pid1 == 0)
    {
        callfork(1);
        pid_t pid2 = fork();
        if (pid2 == 0)
        {
            callfork(2);
            pid_t pid3 = fork();
            if (pid3 == 0)
            {
                callfork(3);
            }
            else
            {
                wait(NULL);
            }
        }
        else
        {
            wait(NULL);
        }
    }
    else
    {
        wait(NULL);
    }
}
