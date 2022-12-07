#include "omp.h"
#include <stdio.h>
#include <stdlib.h>


#define MAXSIZE 10000


size_t init_with_file(int32_t* a, char* filename){
    FILE* f = fopen(filename, "r");
    if (f == NULL) 
     return 0;
 
    int tmp;
    size_t i = 0;
    for(; i < MAXSIZE; i++){
        if (fscanf(f, " %d ", &tmp) == EOF) //в файле числa через пробел
            break;
        a[i] = tmp;
    }

    return i;
}

size_t init_with_console(int32_t* a){
    int tmp;
    size_t i = 0;
    for(; i < MAXSIZE; i++){
        int res = scanf(" %d \n", &tmp);
        if (res == EOF || res == 0)
            break;
        a[i] = tmp;
    }

    return i;
}

void print(int32_t* a, size_t size){

    for(size_t i = 0; i < size; i++){
        printf("%d ", a[i]);
    }

}

void quickSortR(int32_t* a, long N) {

  long i = 0, j = N-1;      // поставить указатели на исходные места
  int32_t temp, p;

  p = a[ N>>1 ];        // центральный элемент

  // процедура разделения
  do {
    while ( a[i] < p ) 
        i++;
    while ( a[j] > p ) 
        j--;

    if (i <= j) {
      temp = a[i]; 
      a[i] = a[j];
      a[j] = temp;
      i++; 
      j--;
    }
  } while ( i <= j );

  // рекурсивные вызовы, если есть, что сортировать 
  if ( j > 0 ) 
    #pragma omp task
        quickSortR(a, j+1);
  if ( N > i )
    #pragma omp task
        quickSortR(a+i, N-i);
}


int main(int argc, char* argv[]){

        int32_t a[MAXSIZE] = {};
      
        size_t realsize = 0;
        if (argc == 2)
            realsize = init_with_file(a, argv[1]);
        else
            realsize = init_with_console(a);

        omp_set_num_threads(10);
        long i = 0, j = realsize-1;

        while ( i < j && a[i] < a[i+1] ) //проверка на то что массив сортирован и на единичную длину
            i++;
        if (i == realsize-1){
            printf("Массив уже сортирован\n");
            print(a, realsize);
            return 0;
        }  

        #pragma omp parallel
            #pragma omp single nowait
            {
                quickSortR(a, realsize);
            }

        print(a, realsize);
        return 0;
}
