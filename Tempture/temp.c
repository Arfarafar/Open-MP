#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void printPlane(long double* plane, long sizeX, long sizeY){
        for (int i = 0; i < sizeY; ++i)
        {
                for (int j = 0; j < sizeX; ++j)
                {
                        printf("%8.4Lf|", plane[i*sizeX+j]);
                }
                putchar('\n');
        }
        putchar('\n');
        putchar('\n');
}

char checkdiff(long double* plane, long sizeX, long sizeY, long double e, struct timespec *t0 ){

        clock_gettime (CLOCK_REALTIME, t0);
        
        for (int j = 0; j < sizeX/2 + 1; ++j)
                if (plane[j] - plane[(sizeY-1)*sizeX + j] > e)
                    return 1;              
        
        return 0;
}



int main(int argc, char** argv){

        struct timespec  t0;
        struct timespec  t1;

        if (argc != 4){
                printf("Invalid argc\n");
            }

        char* extstr;
        long N = strtol(argv[1], &extstr, 0); 
        long M = strtol(argv[2], &extstr, 0);
        long double e = strtold(argv[3], &extstr);


        long double* oldplane = (long double*) calloc (N*M, sizeof(long double)); //площадки шириной М 
        long double* newplane = (long double*) calloc (N*M, sizeof(long double));

        for (int i = 0; i < M; i++){
                oldplane[i] = 100.0;
        }
        for (int i = 0; i< N; i++){
                oldplane[i*M] = 100;
                oldplane[i*M + M - 1] = 100;
        }


        printPlane(oldplane, M, N);
       

        omp_set_num_threads(10);

        
        long double time = 0.0;

        while (checkdiff(oldplane, M, N, e, &t0)){ //вернет 0 если разность между клетками меньше е, засекает начало времени

                #pragma omp parallel for schedule(auto) // считает температуру как среднее арифметическое из соседних клеток и своей клетки
                for (int i = 0; i < N; i++) {
                        for (int j = 0; j < M; j++){

                                if (i == 0){
                                        if (0 < j && j < M-1){
                                                newplane[i*M + j] = (oldplane[i*M + j-1] + oldplane[i*M + j+1] + oldplane[(i+1)*M+j] + oldplane[i*M +j])/4; 
                                        }
                                        else if (j == 0){
                                                newplane[0] = (oldplane[1] + oldplane[M]+ oldplane[0])/3.0; 
                                        }
                                        else 
                                                newplane[i*M + j] = (oldplane[i*M + j-1] + oldplane[(i+1)*M+j]+ oldplane[i*M +j])/3; 

                                }
                                else if(i == N-1){
                                        if (0 < j && j < M-1){
                                                newplane[i*M + j] = (oldplane[i*M + j-1] + oldplane[i*M + j+1] + oldplane[(i-1)*M+j]+ oldplane[i*M +j])/4;
                                        }
                                        else if (j == 0){
                                                newplane[i*M + j] = (oldplane[i*M + j+1] + oldplane[(i-1)*M+j]+ oldplane[i*M +j])/3;
                                        }
                                        else 
                                                newplane[i*M + j] = (oldplane[i*M + j-1] + oldplane[(i-1)*M+j]+ oldplane[i*M +j])/3;
                                }
                                else if (j == 0){
                                        newplane[i*M + j] = (oldplane[i*M + j+1] + oldplane[(i-1)*M+j] + oldplane[(i+1)*M+j]+ oldplane[i*M +j])/4;
                                }
                                else if (j == M-1){
                                        newplane[i*M + j] = (oldplane[i*M + j-1] + oldplane[(i-1)*M+j] + oldplane[(i+1)*M+j]+ oldplane[i*M +j])/4;
                                }
                                else {
                                        newplane[i*M + j] = (oldplane[i*M + j-1] + oldplane[i*M + j+1] + oldplane[(i-1)*M+j] + oldplane[(i+1)*M+j]+ oldplane[i*M +j])/5;
                                }

                        }
                
                }

                long double* tmp = oldplane;    //поочередно заполняем 2 таблицы температур
                oldplane = newplane;
                newplane = tmp;

                clock_gettime (CLOCK_REALTIME, &t1); // чтобы не считать время на отрисовку как рабочее заканчиваем тут на каждом цикле

                time += t1.tv_sec-t0.tv_sec + ((t1.tv_nsec-t0.tv_nsec) / 1000) * 0.000001;
                printPlane(oldplane, M, N);
        }

        printf("%Lf\n", time);
        free(oldplane);
        free(newplane);


        return 0;
}


