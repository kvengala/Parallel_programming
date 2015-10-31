/* 
 * File:   DSP.c
 * Author: kashyap
 *
 * Created on October 30, 2015, 5:57 PM
 */

#include <stdio.h>
#include <math.h>

#define M 1 /* e.g. M=1*/
#define N 2 /* e.g. N=2 */
#define n 20 /* defining the size of the arra */
#define loop_iter(i,iter_limit) for( i=0;i<iter_limit;i++) /* loop iterator */
int i =0;
double a[N]; /* array that contains coefficients a1,a2,…aN */
double b[M+1]; /* array that contains coefficients b0,b1,b2,…,bM*/ 
double y[n] = {0};
double x[n] = {0};
double param_x = 0.5;
void gen_acoeff(){
    loop_iter(i,N)
        a[i] = i*2 +1;
}
void gen_bcoeff(){
    loop_iter(i,M+1)
        b[i] = i*3 +1;
}
double iirDF1(int x_n){
    double sum=0;
    double y_inter=0;
    double x_inter=0;
    loop_iter(i,N+1){
    
    y_inter += (-1)*a[i+1]*y[x_n - i+1 +10];    
    }
    loop_iter(i,M+1){
   
    double val = x_n - 1 < 0 ? 0 : x[x_n -i];   
 
    x_inter += b[i]*val;    
    }
    y[x_n +10] = y_inter +x_inter;
    return y[x_n +10];
}
void gen_xn(){
    loop_iter(i,n){
        x[i] = pow(param_x,(double)i);
 
    }
}

int main(int argc, char** argv) {
    int iter =-1;
    gen_acoeff();
    gen_bcoeff();
    gen_xn();
    loop_iter(iter,10){
        printf("n-value = %d  function output y(n) = %f\n", iter, iirDF1(iter) );
    }
    return 0;
}

