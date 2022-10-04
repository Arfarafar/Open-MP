#include "omp.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{

    if (argc != 2){
        printf("Invalid argc\n");
    }

    char* extstr;
    long N = strtol(argv[1], &extstr, 0); // До какого слагаемого надо считать



    long long int sum = 0; 

     #pragma omp paralllel for private(sum) reduction(+:sum) schedule(auto)
        for(int i = 1; i <= N; i++)
            sum += i; //суммируем
    

    printf("%lld\n", sum);

}
