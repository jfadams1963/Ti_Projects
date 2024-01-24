//tiaes.c
//(c) 2023 2024 J Adams jfa63@duck.com
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

    char* pwd = getpass("Passphrase: ");
    // Use the 256-bit hash of the passphrase as the key.
    // The SHA256() function takes a char* as input and returns
    // a unsigned char pointer.
    uchar* key =  SHA256(pwd);

    // Do key expansion
    ke(key);

    // Open the file handles
    // We close them in cbcdec() and cbcenc()
    in = fopen(argv[2],"rb");
    out = fopen(argv[3],"wb");

    if (*argv[1] == 'e') {
        cbcenc();
    } else if (*argv[1] == 'd') {;
        cbcdec();
    } else {
        printf("Incorrect args:\n Usage: tiaes [e,d] <infile> <outfile>\n");
    }

    return 0;
}
 
