#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define TWOD_COPY_SYSCALL 451

int main()
{

    float original[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    float new[3][3];

    long sys_call_status;

   
    printf("original matrix is - \n");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%f ", original[i][j]);
        }
        printf("\n");
    }

    if (syscall(TWOD_COPY_SYSCALL, original, new) != EFAULT)
    {
        printf("new generated array is - \n");

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                printf("%f ", new[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}
