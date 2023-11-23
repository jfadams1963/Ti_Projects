//test_xmult.c
//testing xmult tables output

#include "testcore.h"

void main() {
	uchar n,m;
	printf("times 9\n");
    printf("Enter an integer < 256:\n");
    scanf("%d",&n);
    m=m9[n];
    printf("%d\n",m);
    return;	
}
