//test.c
//(c) 2023 J Adams jfa63@duck.com
//Released under the 2-clause BSD license.

#include "core.h"

#ifndef CRYPUTILS_H
#define CRYPUTILS_H
#include "cryputils.h"
#endif

extern void ke(void);

unsigned char key[] = {0x60,0x3d,0xeb,0x10,0x15,0xca,0x71,0xbe,0x2b,0x73,0xae,0xf0,0x85,0x7d,0x77,0x81,0x1f,0x35,0x2c,0x07,0x3b,0x61,0x08,0xd7,0x2d,0x98,0x10,0xa3,0x09,0x14,0xdf,0xf4};

int main(void) {
	int r,c;

	//display key 
	printf("FIPS 197 256bit key:\n"); 
	for (c=0; c<32; c++) {
		printf("%x ",key[c]);
	}
	printf("\n");
	printf("Press ENTER\n");  
	getchar();

	ke();
	// display key schedule
	printf("Expanded key schedule:\n");
	for (r=0; r<60; r++) {
		for (c=0; c<4; c++) {
			printf("%x ", w[r][c]);
		}
		printf("\n");
	}

	return 0;
}
    
