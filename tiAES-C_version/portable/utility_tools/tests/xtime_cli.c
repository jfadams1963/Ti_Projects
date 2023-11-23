//Fips 197 xTimes
//xtime.c

#include <stdio.h>
#include "gfmath.h"


int main() {
    uint a,b;
    //b=0;
    printf("Enter: ");
    scanf("%u",&a);
/*    
    if (a == 0) {
        printf("%u\n",a);
        return 0;
    }
    
    if ((a & 128) > 0) b=1;
    a = (a << 1);
    a %= 256;
    if (b == 1) a^=27;
*/
	a=xtime(a);
    printf("%u\n",a);
	return 0;


}
