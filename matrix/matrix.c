#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>





void init(int raw, int col, int* A){

	#pragma omp parallel for schedule(auto)
			for(int i = 0; i < raw; i++){
				for (int j = 0; j < col; j++){
					A[i*col + j] = rand()%1000;
				}
			} 
}


int main(int argc, char** argv)
{



	for (int num = 1; num < 17; num *= 2){

		omp_set_num_threads(num);

		for (int matr = 10; matr < 2000; matr *= 2){

			int A_raw = matr;
			int A_col = matr;

			int B_raw = A_col;
			int B_col = 2*matr;



			int* A = (int*) malloc( A_raw * A_col * sizeof(int) );
			int* B = (int*) malloc( B_col * B_raw * sizeof(int) );

			init(A_raw, A_col, A);
			init(B_raw, B_col, B);


			int* SUM = (int*) malloc(A_raw*B_col*sizeof(int)) ;

			


			struct timespec  t0;
			struct timespec  t1;

			clock_gettime (CLOCK_REALTIME, &t0);


			#pragma omp parallel for schedule(auto)
				for(int i = 0; i < A_raw; i++){
					
					for (int k = 0; k < B_col; k++){
						int sum = 0;
						for (int j = 0; j < A_col; j++)
							sum += A[i*A_col + j]*B[j*B_col + k];
						SUM[i* B_col + k] = sum;

					}
				} 

			

			clock_gettime (CLOCK_REALTIME, &t1);

			free(A);
			free(B);
			free(SUM);

			printf("потоков %d,  размер матрицы %d, время умножения %lf\n", num, matr, t1.tv_sec-t0.tv_sec + ((t1.tv_nsec-t0.tv_nsec) / 1000) * 0.000001);
		}
		printf("\n");
	}

}
