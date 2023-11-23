//Fips 197 xTimes3
//xtimes3_cli.c

#include <stdio.h>
#include "gfmath.h"


int main() {
    uint a,b;
//    b=0;
    printf("Enter: ");
    scanf("%d",&a);

/*    if (a == 0) {
		printf("%d\n",0);
		exit(0);
	}

    b=xtimes(a);
    b^=a; 
*/
	a=xtimes3(a);
    printf("%d\n",a);

	return 0;
}
