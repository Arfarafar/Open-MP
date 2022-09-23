#include "omp.h"
#include <stdio.h>
#include <stdlib.h>


const int arraysize = 100000;

int main(int argc, char** argv)
{

    long long int a[arraysize];
    for(int i = 0; i < arraysize; i++)
        a[i] = i;


    #pragma omp parallel
    {
        #pragma omp for schedule(auto)
            for(int i = 1; i < arraysize-1; i++)
                a[i] = (a[i-1]*a[i]*a[i+1])/3;
    }
        
    

    printf("%lld\n", sum);

}




