#include "omp.h"
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char** argv){

        if (argc != 2){
                printf("Invalid argc\n");
            }

        char* extstr;
        long N = strtol(argv[1], &extstr, 0); //обработка аргумента командной строки обозначающего кол-во слагаемых в рядах

        omp_set_num_threads(10);

        
        long double pi = 0;

        #pragma omp parallel for reduction(+:pi) schedule(auto) // вычисляем сумму ряда для числа пи
        for (int i = 0; i < N; i++) {
                if (i % 2 == 0){
                        pi +=  4.0 / (2.0 * (long double)(i) + 1);
                }
                else {
                        pi -=  4.0 / (2.0 * (long double)(i) + 1);
                }
        }


        printf("first %ld of pi series: %Lf\n", N, pi);

        long double exponent2 = 0;
        long double x = 2.0;
        #pragma omp parallel for reduction(+:exponent2) schedule(auto) // вычисляем сумму ряда для e^2
        for (int i = 0; i < N; i++) {
                long double tmp = 1;
                for (int j = 0; j < i; j++){
                    tmp *= x/(i-j);
                }
                exponent2 += tmp;
        }
        
        printf("first %ld of exp^%d series: %Lf\n", N, (int)x, exponent2);       


}


