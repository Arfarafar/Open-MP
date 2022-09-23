#include "omp.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{

    if (argc != 2){
        printf("Invalid argc\n");
    }

    char* extstr;
    long N = strtol(argv[1], &extstr, 0);



    long long int sum = 0; 

     #pragma omp paralllel for private(sum) reduction(+:sum) schedule(auto)
        for(int i = 1; i <= N; i++)
            sum += i;
    

    printf("%lld\n", sum);

}
