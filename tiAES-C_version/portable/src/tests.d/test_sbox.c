//test_sbox.c
//testing sbox output

#include "testcore.h"

void main() {
	uchar n,s;
    printf("Enter an integer < 256:\n");
    scanf("%d",&n);
    s=sbox[sboxi[n]];
    printf("%d\n",s);
    return;	
}
