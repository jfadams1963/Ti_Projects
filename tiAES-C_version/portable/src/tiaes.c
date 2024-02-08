//tiaes.c
//(c) 2023 2024 J Adams jfa63@duck.com
//Released under the 2-clause BSD license.

/*
Usage: tiaes [e,d] <infile> <outfile>
*/

#include <unistd.h>
#include <string.h>

#ifdef BSD
    #include <readpassphrase.h>
#endif

#ifdef LINUX
    #include <bsd/readpassphrase.h>
#endif

#include "core.h"

#ifndef CRYPUTILS_H
    #define CRYPUTILS_H
    #include "cryputils.h"
#endif


int main(int argc, char* argv[]) {
    int i,sz;

    //arg checks
    if (argc != 4) {
        printf("Usage: tiaes [e,d] <infile> <outfile>\n");
        exit(1);
    }

    char* pwd = malloc(1024);
    if (pwd == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    readpassphrase("Passphrase: ", pwd, sizeof(pwd), 0);

    // Use the 256-bit hash of the passphrase as the key.
    // The SHA256() function takes a char* as input and returns
    // a unsigned char pointer.
    uchar* key =  SHA256(pwd);

    // Zero-out and deallocate pwd memory location
    memset(pwd, 0, sizeof(pwd)*sizeof(pwd[0]));
    free(pwd);

    // Do key expansion
    ke(key);

    // Zero-out and deallocate key memory location.
    memset(key, 0, 32*sizeof(key[0]));
    free(key);

    // Open the file handles first.
    // We close them in cbcdec() and cbcenc()
    // Refactor/consolodate this section!
    if (*argv[1] == 'e') {
        in = fopen(argv[2],"rb");
        if (!in) {
            printf("Could not open in file for reading!");
            // Zero out key schedule
            memset(w, 0, 64*4*sizeof(w[0][0]));
            return -1;
        }

        out = fopen(argv[3],"wb");
        if (!out) {
            printf("Could not open out file for writing!");
            // Zero out key schedule
            memset(w, 0, 64*4*sizeof(w[0][0]));
            return -1;
        } else {
            cbcenc();
        }

    } else if (*argv[1] == 'd') {;
        in = fopen(argv[2],"rb");
        if (!in) {
            printf("Could not open in file for reading!");
            // Zero out key schedule
            memset(w, 0, 64*4*sizeof(w[0][0]));
            return -1;
        }

        out = fopen(argv[3],"wb");
        if (!out) {
            printf("Could not open out file for writing!");
            // Zero out key schedule
            memset(w, 0, 64*4*sizeof(w[0][0]));
            return -1;
        } else {
            cbcdec();
        }

    } else {
        // Zero out key schedule
        memset(w, 0, 64*4*sizeof(w[0][0]));
        printf("Incorrect args:\n Usage: tiaes [e,d] <infile> <outfile>\n");
    }

    return 0;
}
 
