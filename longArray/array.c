#include "omp.h"
#include <stdio.h>
#include <stdlib.h>


const long long int arraysize = 100000;
const int blocksize = 1000;

int main(int argc, char** argv)
{

    long long int a[arraysize];
    for(int i = 0; i < arraysize; i++)  
        a[i] = i;

    /*
    #pragma omp parallel for schedule(auto)     //массив по условию задачи заполнен определенным образом, 
                                                //а именно имеет зависимость данных от индекса
        for(long long int i = 1; i < arraysize; i++)
            a[i] = i*(i-1)*(i+1) / 3;           //значит никто нам не запрящает совсем избавиться от зависимости по данным

    a[arraysize - 1] = (arraysize - 2) * (arraysize - 1) / 3 ; //в каждом умножении присутсвует множитель делящийся на 3
    

    for(int i = 0; i < 1000; i++)  
       printf("%lld\n", a[i]);

   */

    long long int lastvar = 0;
    int zone_index = 0;

    #pragma omp parallel for schedule(dynamic, blocksize) shared(zone_index, lastvar)  
        for(int i = 0; i < ((arraysize-1)/blocksize + 1); ++i){

            
            int end_block_index = (i+1) * (blocksize) > arraysize ? arraysize : (i+1)*blocksize;
            int second = a[i*blocksize+1];
            int prev = a[i*blocksize];
            int cur = 0;

            int j;
            for(j = i*blocksize+1; j < end_block_index-1; ++j){
                cur = a[j];
                a[j] = cur*a[j+1]*prev/ 3;
                prev = cur;
            }

            while (zone_index != i);

            if(i == 0){
                a[0] = a[0]*second/3;
                lastvar = a[j];
                a[j] = (j+1 == arraysize) ? a[j] * prev / 3 : prev*a[j]*a[j+1]/3 ;
            }
            else if (j+1 == arraysize){
                a[i*blocksize] = lastvar*second*a[i*blocksize]/3;
                a[j] = prev * a[j]/3;
            }
            else{
                a[i*blocksize] = lastvar*second*a[i*blocksize]/3;
                lastvar = a[j];
                a[j] = prev*a[j+1]*a[j]/3 ;
            }

            zone_index++;


        }

    long long int b[arraysize];
    long long int diff = 0;
    
    #pragma omp parallel for schedule(auto) shared(b, a) reduction(+:diff)

        for(long long int i = 1; i < arraysize - 1; i++)
        {
            b[i] = (i-1)*i*(i+1)/3;
            diff += b[i] - a [i]; 
        }


    b[0] = 0;
    b[arraysize - 1] = (arraysize-1)*(arraysize - 2)/3; 
    printf("%lld\n", diff);
    
/*
    for(int i = 99500; i < 100000; i++)  
       printf("%d: %lld %lld %lld \n", i, a[i], b[i], a[i]-b[i]);
  */  

} 




