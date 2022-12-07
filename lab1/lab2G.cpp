#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define ISIZE 10000
#define JSIZE 10000
#define ISHIFT 4
#define JSHIFT 5

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    
    int start = ISIZE / size * rank - ISHIFT; 
    start = start < 0 ? 0 : start;
    int end = ISIZE / size * (rank + 1); 
    end = end > ISIZE ? ISIZE : end;
    

    double *a = (double*)malloc(sizeof(double) * JSIZE * (end - start));
    double T_st = MPI_Wtime();
    for (int i = 0; i < end - start; i++)
        for (int j = 0; j < JSIZE; j++)
            a[i*JSIZE + j] = 10 * (start + i) + j;

    for (int i = 0; i < end - start - ISHIFT; i++)
        for (int j = JSHIFT; j < JSIZE; j++)
            a[i*JSIZE + j] = sin(0.00001 * a[(i+ISHIFT)*JSIZE + j - JSHIFT]);

    double T_work = MPI_Wtime() - T_st;
    printf("Time %f\n", T_work);

    int send;
    FILE *ff = fopen("MPI_result.txt", "a+");
    if (ff == NULL)
        return -1;

    if (rank != 0)
        MPI_Recv(&send, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int i = 0;
    for (; i < end - start - ISHIFT; i++)
        for (int j = 0; j < JSIZE; j++)
            fprintf(ff, "%f", a[i*JSIZE + j]);
    
    if (rank < size - 1)
        MPI_Send(&send, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    else
        for (; i < end - start; i++)
        for (int j = 0; j < JSIZE; j++)
            fprintf(ff, "%f", a[i*JSIZE + j]);
    fclose(ff);
    free(a);
    MPI_Finalize();
    return 0;
}
