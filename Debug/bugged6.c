#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define VECLEN 100

float a[VECLEN], b[VECLEN];

float dotprod()
{
    int i, tid;
    float sum = 0.0;

    tid = omp_get_thread_num();

    #pragma omp for //здесь редакшн ошибочен так как sum, объявленная внутри секции, приватная. и каждый поток и так будет складывать пройденные итерации в свою копию
    for (i = 0; i < VECLEN; i++)
    {
        sum = sum + (a[i] * b[i]);
        printf("  tid= %d i=%d\n", tid, i);
    }

    return sum;
}


int main (int argc, char *argv[])
{
    int i;
    float sum;

    for (i = 0; i < VECLEN; i++)
        a[i] = b[i] = 1.0 * i;
    sum = 0.0;

    #pragma omp parallel reduction(+:sum) //каждый поток получит свое значение возвращаемое из функции которое надо будет сложить
    {
        sum += dotprod();
    }

    printf("Sum = %f\n",sum);
}


/******************************************************************************
* ЗАДАНИЕ: bugged6.c
* ОПИСАНИЕ:
*   Множественные ошибки компиляции
*   Программа должнна была показывать, как можно выполнять параллельный код,
*   используя функции, но что-то пошло не так.
******************************************************************************

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define VECLEN 100

float a[VECLEN], b[VECLEN];

float dotprod()
{
    int i, tid;
    float sum;

    tid = omp_get_thread_num();
    #pragma omp for reduction(+:sum)
    for (i = 0; i < VECLEN; i++)
    {
        sum = sum + (a[i] * b[i]);
        printf("  tid= %d i=%d\n", tid, i);
    }
}


int main (int argc, char *argv[])
{
    int i;
    float sum;

    for (i = 0; i < VECLEN; i++)
        a[i] = b[i] = 1.0 * i;
    sum = 0.0;

    #pragma omp parallel shared(sum)
    dotprod();

    printf("Sum = %f\n",sum);
}
*/

