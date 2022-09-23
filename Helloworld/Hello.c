#include "omp.h"
#include <stdio.h>


int main(int argc, char** argv)
{

    int a = 0; 

    #pragma omp parallel
    {
        int maxid = omp_get_num_threads();
        int myid = omp_get_thread_num();

        while (myid != (maxid - a - 1));
        
        
        printf("myid = %d \n", myid);
        fflush(0);
        a++;
        
    }

}
