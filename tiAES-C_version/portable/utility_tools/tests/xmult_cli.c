//xmult.c
//Fips 197 xMult
#include <stdio.h>

typedef unsigned int uint;

uint xtimes(uint n) {
    uint m;
	m=0;
	
	if (n == 0) {
        return n;
	}

	if ((n & 128) > 0) m=1;
	n = (n << 1);
	n %= 256;
	if (m == 1) n^=27;
	return n;
}

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
            t=b;
            for (e=0; e<=i; e++) {
                t=xtimes(t);
            }
            d^=t;
        }
        a = (a >> 1);
    }
	printf("%u\n",d);
	return 0;
}
