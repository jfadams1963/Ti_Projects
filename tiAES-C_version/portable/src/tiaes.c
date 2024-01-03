//tiaes.c
//(c) 2023 J Adams jfa63@duck.com
//Released under the 2-clause BSD license.

/*
Usage: tiaes [e,d] <infile> <outfile>
*/

#include <unistd.h>
#include "core.h"

#ifndef CRYPUTILS_H
#define CRYPUTILS_H
#include "cryputils.h"
#endif


int main(int argc, char *argv[]) {
    int i,sz;

    //arg checks
    if (argc != 4) {
        printf("Usage: tiaes [e,d] <infile> <outfile>\n");
        exit(1);
    }

    uchar *pwd = getpass("Password: ");

    sz = sizeof(pwd);
    i = 0;
    while ((i < sz) && (i < 32) ) {
        key[i] = pwd[i];
	i++;
    }

    ke();

    //open the file handles
    in = fopen(argv[2],"rb");
    out = fopen(argv[3],"wb");

    if (*argv[1] == 'e') {
        cbcenc();
    } else if (*argv[1] == 'd') {;
        cbcdec();
    } else {
        printf("Incorrect args:\n Usage: tiaes [e,d] <infile> <outfile>\n");
    }

    //fclose(in);
    //fclose(out);

    return 0;
}
    
