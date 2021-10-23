#include <stdio.h>
#define POL_GRADE 6     //Grade of irreducible polynomial m

unsigned int multPolinom(unsigned int f, unsigned int g, unsigned int m);
unsigned int mult_by_x(unsigned int f, unsigned int m);

int main(){
    //int m=283;  //AES polynomial
    int m = 67;   //x6 + x + 1
    //printf("%d\n", multPolinom(141,2,m));

    for (size_t i = 0; i < (1<<POL_GRADE); i++){
        if( !(i%16) )
            printf("\n---------------------------------------------------------------------------------\n");
        for (size_t j = 0; j < (1<<POL_GRADE); j++){
            if(!(i||j))
                printf("0:0\t");
            if( multPolinom(i,j,m) == 1 )
                printf("%x:%x\t",i,j);
        }
        
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
    if( f >= (1<<(POL_GRADE-1)) )   //Check if the most significative bit of f is 1
        a=1;
    f = f<<1 & ((1<<POL_GRADE)-1);
    if(a)
        f = f ^ ( m & ((1<<POL_GRADE)-1) );
    return f;
}