#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

#define SYS_kern_2D_memcpy 449

int main()
{
    float m1[3][3] = {{1.0, 2.0, 3.0}, {3.0, 4.0, 5.0}, {5.0, 6.0, 7.0}};
    float m2[3][3] = {{5.0, 5.0, 5.0}, {5.0, 5.0, 5.0}, {5.0, 5.0, 5.0}};

    printf("This is the initial matrix1 is:\n");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%lf ", m1[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("This is the initial matrix2 is:\n");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%lf ", m2[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int res = syscall(SYS_kern_2D_memcpy, m1, m2, 3, 3);

    if (res < 0)
    {
        printf("ERROR! Could not perform system call.");
        exit(1);
    }

    printf("This is the final matrix1 is:\n");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%lf ", m1[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("This is the final matrix2 is:\n");

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%lf ", m2[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}