//xmult_cli.c
//Fips 197 xmult
#include <stdio.h>
#include "gfmath.h"

typedef unsigned int uint;


int main() {
    uint a,b,d,e,i,t;
    
    //get input
    printf("Enter first integer: ");
    scanf("%u",&a);
    printf("Enter second integer: ");
    scanf("%u",&b);

    if (a*b == 0) {
        printf("%u\n",0);
        return 0;
    } else  if (a == 1) {
        printf("%u\n",b);
        return 0;
    } else if (b == 1) {
        printf("%u\n",a);
        return 0;
    }
    
    if ((a & 1) > 0) d=b;
    a = (a >> 1); //binary division by 2

    t=0;
    for (i=0; i<7; i++) {
        if ((a & 1) > 0) {
            t = b;
            for (e=0; e<=i; e++) {
                t = xtime(t);
            }
            d ^= t;
        }
        a = (a >> 1);
    }
	printf("%u\n",d);
	return 0;
}
