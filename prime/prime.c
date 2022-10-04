#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define wheelsize  48
#define wheelbasissize  4




char checkPrimeBasis(int number, int* basis){
        for (int i = 0; i < wheelbasissize; i++){
                if (number % basis[i] == 0){
                        if (number != basis[i])         // если число простое из базиса то вернем 0 (как будто оно не делится на базис),
                                                        // так как потом при сравнении с max программа будет вести себя верно
                                return 1;               // если число делится на простое из базиса то возвращаем 1
                        else
                                return 0;
                }
        }
        return 0;
}



int main(int argc, char** argv){

        if (argc != 2){
                printf("Invalid argc\n");
            }

        char* extstr;
        long N = strtol(argv[1], &extstr, 0); //обработка аргумента командной строки

        omp_set_num_threads(10);


/* Брать готовый алгоритм блочного решета Эратосфена показалось слишком скучным, поэтому я написал свой алгоритм факторизации колеса.

   Его смысл в том, что мы составляем набор из всех чисел взаимно простых с 2*3*5*7 = 210 и проверяем заданное число M на делимость 
   относительно чисел набора + t*210, t = 0, 1, 2...  пока число не превысит корень из M. Если делителей не нашлось, то число простое.
   подробнее: http://mech.math.msu.su/~shvetz/54/inf/perl-examples/PerlExamples_Primes_Ideas.xhtml (Колесный метод)  */



        
        int wheel4[wheelsize] = {1,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,
                          73,79,83,89,97,101,103,107,109,113,121,127,131,137,139,143,  //используем факторизацию колеса из первых 4х простых чисел
                          149,151,157,163,167,169,173,179,181,187,191,193,197,199,209}; // т.е все взаимно простые с 210 числа


        int wheelbasis[wheelbasissize] = {2,3,5,7};
        int Pk = 2*3*5*7;

        int num = 0; 

        #pragma omp parallel for reduction(+:num) schedule(auto) 
        for (int i = 2; i < N+1; i++) {
                int max = (int) sqrt(i + .0);
                if (checkPrimeBasis(i, wheelbasis)){

                }

                else {
                        int index = 1;
                        int circle = wheel4[index];

                        while (circle <= max){
                                if (i % circle != 0){
                                        index++;
                                        circle = wheel4[index % 48] + index / wheelsize *Pk;
                                } 
                                else 
                                        break;
                        }

                        if (circle > max)
                                num++;

                }
        }


        printf("%d\n", num);
}


