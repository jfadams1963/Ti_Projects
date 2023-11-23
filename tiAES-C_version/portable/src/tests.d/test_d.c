//test_d.c
//(c) 2023 J Adams jfa63@duck.com
//Released under the 2-clause BSD license.

// Testing the encr() function.

#include "testcore.h"

#ifndef CRYPUTILS_H
#define CRYPUTILS_H
#include "cryputils.h"
#endif

extern void ke(void);
extern void encr(void);
extern void decr(void);

uint nk = 4;
uint nr = 10;
unsigned char key[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
unsigned char st[4][4] = {{0x32,0x88,0x31,0xe0},
						  {0x43,0x5a,0x31,0x37},
						  {0xf6,0x30,0x98,0x07},
						  {0xa8,0x8d,0xa2,0x34}};

void main(void) {
	int r,c;

	//display  state
    printf("Initial state:\n");
    for (r=0; r<4; r++) {
        for (c=0; c<4; c++) {
            printf("%x ", st[r][c]);
        }
        printf("\n");
    }
    printf("Press ENTER\n");  
    getchar();

	ke();
/*
    printf("Key schedule:\n");
    for (r=0; r<44; r++) {
        for (c=0; c<4; c++) {
            printf("%x ", w[r][c]);
        }
        printf("\n");
    }
    printf("Press ENTER\n");
    getchar();
*/	
	encr();

    printf("Encrypted state, 10 rounds:\n");
    for (r=0; r<4; r++) {
        for (c=0; c<4; c++) {
            printf("%x ", st[r][c]);
        }
        printf("\n");
    }
    printf("Press ENTER\n");  
    getchar();

	decr();
    printf("Decrypted state:\n");
    for (r=0; r<4; r++) {
        for (c=0; c<4; c++) {
            printf("%x ", st[r][c]);
        }
        printf("\n");
    }
    printf("Press ENTER\n");  

	return;
}
 
