//test_e.c
//(c) 2023 J Adams jfa63@duck.com
//Released under the 2-clause BSD license.

// Testing the encr() function.
// Need to test 256

#include "testcore.h"

#ifndef CRYPUTILS_H
#define CRYPUTILS_H
#include "cryputils.h"
#endif

extern void ke(void);
extern void encr(void);

uint nk = 8;
uint nr = 14;
//256 bit FIPS test key
unsigned char key[32] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f}
//plaintext
//00,11,22,33,44,55,66,77,88,99,aa,bb,cc,dd,ee,ff

unsigned char st[4][4] = {{0x00,0x44,0x88,0xcc},
						  {0x11,0x55,0x99,0xdd},
						  {0x22,0x66,0xaa,0xee},
						  {0x33,0x77,0xbb,0xff}};

int main(void) {
	int r,c;

	//display key 
	printf("FIPS197 256bit key:\n"); 
	for (c=0; c<16; c++) {
		printf("%x ",key[c]);
	}
	printf("\n");
	printf("Press ENTER\n");  
	getchar();

	ke();
	// display key schedule
	printf("Expanded key schedule:\n");
	for (r=0; r<44; r++) {
		for (c=0; c<4; c++) {
			printf("%x ", w[r][c]);
		}
		printf("\n");
	}
	printf("Press ENTER\n");  
	printf("\n");
	getchar();

	encr();

	return 0;
}
    
