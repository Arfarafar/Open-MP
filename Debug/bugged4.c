/******************************************************************************
 * ЗАДАНИЕ: bugged4.c
 * ОПИСАНИЕ:
 *   Очень простая программа параллельных манипуляций с двумерным массивом
 *   зависимо от количества исполнителей... но с segmentation fault.
 ******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1048

int main (int argc, char *argv[]) 
{
    int nthreads, tid, i, j;
    //double a[N][N]; // выделение на стеке больше 8мб данных 
    


    //#pragma omp parallel shared(nthreads) private(i, j, tid, a)
    #pragma omp parallel shared(nthreads) private(i, j, tid)
    {
        double* a = (double*)calloc(N*N, sizeof(double)); //выделение памяти для каждого потока, (все равно производилось бы копирование)
        tid = omp_get_thread_num();
        if (tid == 0) 
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
        printf("Thread %d starting...\n", tid);

        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                a[i*N + j] = tid + i + j; //немного подправим обращение к элементам раскрыв одни скобки 

        printf("Thread %d done. Last element= %f\n", tid, a[(N-1)*N + N-1]);
        free(a);
    } 
}
