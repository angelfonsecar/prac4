#include <stdio.h>
#define POL_GRADE 8     // Grado del polinomio irreducible m

unsigned int multPolinom(unsigned int f, unsigned int g, unsigned int m);
unsigned int mult_by_x(unsigned int f, unsigned int m);


int main(){
    int m=283;  //polinomio de AES
    int a = 67;
    //printf("%d\n", multPolinom(141,2,m));

    for (size_t i = 0; i < 256; i++){
        for (size_t j = 0; j < 256; j++){
            //printf("%x\t", multPolinom(i,j,m));
            if( multPolinom(i,j,m) == 1 )
                printf("i: %x\tj: %x\n",i,j);
        }
        //printf("\n");
    }
    

    return 0;
}

unsigned int multPolinom(unsigned int f, unsigned int g, unsigned int m){
    unsigned int res=0;
    for (size_t i = 0; i < POL_GRADE; i++){
        if ( g & (1<<i) ){
            int prod = f;
            for (size_t j = 1; j < i+1; j++){
                prod=mult_by_x(prod, m);
            }
            res = res ^ prod;
        }
    }
    return res;
}

unsigned int mult_by_x(unsigned int f, unsigned int m){     //Function that multiplies by x, the polynomial f
    int a = 0;
    if( f >= (1<<(POL_GRADE-1)) )   //vemos si el bit más significativo de f está encendido
        a=1;
    f = f<<1 & ((1<<POL_GRADE)-1);
    if(a)
        f = f ^ ( m & ((1<<POL_GRADE)-1) );
    return f;
}