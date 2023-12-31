//core.h
//(c) 2023 J Adams jfa63@duck.com
//Released under the 2-clause BSD license.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CRYPUTILS_H
#define CRYPUTILS_H
#include "cryputils.h"
#endif

/*
#ifndef KEYUTILS_H
#define KEYUTILS_H
#include "keyutils.h"
#endif
*/


//word bytes
#define NB 4

//data types
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned char block[4][4];
typedef unsigned char word[4];

//state blocks
block st,ns,iv,tb;

//globals
unsigned int nk = 8;
unsigned int nr = 14;
unsigned char w[64][4];
FILE *in,*out;
unsigned char key[32];

