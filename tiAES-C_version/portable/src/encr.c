//encr.c
//(c) 2023 2024 J Adams jfa63@duck.com
//Released under the 2-clause BSD license.
//Subroutines are labeled with the FIPS 197 nomenclature.

#include "core.h"


/* AES Cipher() */
void encr() {
    int c,r,rd = 0;
    /* AddRoundKey()  (column of state) xor (row of RoundKey) */
    //round number 0
    for (r=0; r<4; r++) {
        for (c=0; c<4; c++) {
            st[c][r] ^= w[rd*4+r][c];
        }
    }

    //rounds 1 to nr-1
    for (rd=1; rd<(nr-1); rd++) {
        /*SubBytes()*/
        for (r=0; r<4; r++) {
            for (c=0; c<4; c++) {
                st[r][c] = sbox[st[r][c]];
            }
        }
        
        /* ShiftRows() */
        //row 1, no rotation
        ns[0][0] = st[0][0];
        ns[0][1] = st[0][1];
        ns[0][2] = st[0][2];
        ns[0][3] = st[0][3];
        //row 2, 1 rotation
        ns[1][0] = st[1][1];
        ns[1][1] = st[1][2];
        ns[1][2] = st[1][3];
        ns[1][3] = st[1][0];
        //row 3, 2 rotations
        ns[2][0] = st[2][2];
        ns[2][1] = st[2][3];
        ns[2][2] = st[2][0];
        ns[2][3] = st[2][1];
        //row 4, 3 rotations
        ns[3][0] = st[3][3];
        ns[3][1] = st[3][0];
        ns[3][2] = st[3][1];
        ns[3][3] = st[3][2];
        cpyns_st();
  
        /* MixColumns() */
        for (c=0; c<4; c++) {
            ns[0][c] = m2[st[0][c]] ^ m3[st[1][c]] ^ st[2][c] ^ st[3][c];
            ns[1][c] = st[0][c] ^ m2[st[1][c]] ^ m3[st[2][c]] ^ st[3][c];
            ns[2][c] = st[0][c] ^ st[1][c] ^ m2[st[2][c]] ^ m3[st[3][c]];
            ns[3][c] = m3[st[0][c]] ^ st[1][c] ^ st[2][c] ^ m2[st[3][c]];
        }
        cpyns_st();

        /* AddRoundKey() */
        //round rd
        for (r=0; r<4; r++) {
            for (c=0; c<4; c++) {
                st[c][r] ^= w[rd*4+r][c];
            }
        }
    }//end rounds nr-1 to 1

    /* SubBytes() */
    for (r=0; r<4; r++) {
        for (c=0; c<4; c++) {
            st[r][c] = sbox[st[r][c]];
        }
    }

    /* ShiftRows() */
    //row 1, no rotation
    ns[0][0] = st[0][0];
    ns[0][1] = st[0][1];
    ns[0][2] = st[0][2];
    ns[0][3] = st[0][3];
    //row 2, 1 rotation
    ns[1][0] = st[1][1];
    ns[1][1] = st[1][2];
    ns[1][2] = st[1][3];
    ns[1][3] = st[1][0];
    //row 3, 2 rotations
    ns[2][0] = st[2][2];
    ns[2][1] = st[2][3];
    ns[2][2] = st[2][0];
    ns[2][3] = st[2][1];
    //row 4, 3 rotations
    ns[3][0] = st[3][3];
    ns[3][1] = st[3][0];
    ns[3][2] = st[3][1];
    ns[3][3] = st[3][2];
    cpyns_st();

    /* AddRoundKey() */
    //round nr
    for (r=0; r<4; r++) {
        for (c=0; c<4; c++) {
            st[c][r] ^= w[(nr-1)*4+r][c];
        }
    }
}//end decr()


/* Implement CBC mode */
void cbcenc() {
    int i,r,c,s,b,sz,bsz;
    uchar ch,pd;

    // Size of input file 
    fseek(in, 0, SEEK_END);
    sz = ftell(in);
    fseek(in, 0, SEEK_SET);

    // Get padding size, add to sz for byte array size.
    if ((sz%16) > 0) {
        pd = (16-(sz%16));
    } else {
        pd = 16;
    }
    bsz = (sz + pd);

    // Next, read the bytes into an uchar array,
    // pad with padding bytes, close input file
    uchar barr[bsz];
    for (b=0; b<sz; b++) {
        if ((ch=fgetc(in)) != EOF) {
            barr[b] = (uchar) ch;
        }
    }
    for (b=sz; b<bsz; b++) {
        barr[b] = (uchar) pd;
    }
    fclose(in);

    // Get Initialization Vector block
    s = 60;
    for (r=0; r<4; r++) {
        for (c=0; c<4; c++) {
             iv[r][c] = w[s][c];
        }
        s++;
    }

    
    // Do encryption reading from byte array and write
    // to the output file. Close file.
    i = 0;
    while (i < bsz) {
        // Read bytes into state by _column_ !
        for (c=0; c<4; c++) {
            for (r=0; r<4; r++) {
                st[r][c] = barr[i];
                i++;
            }
        }
        // State = state xor IV
        for (r=0; r<4; r++) {
            for (c=0; c<4; c++) {
                st[r][c] = st[r][c] ^ iv[r][c];
            }
        }
        // Call encr()
        encr();
        // Copy state to next IV
        cpyst_iv();
        // Write bytes to outfile by _column_ !
        for (c=0; c<4; c++) {
            for (r=0; r<4; r++) {
                ch = st[r][c];
                fputc(ch, out);
            }
        }
    }
    fclose(out);
    // Zero out keymaterial, state and byte array
    memset(w, 0, 64*4*sizeof(w[0][0]));
    memset(iv, 0, 16*sizeof(iv[0][0]));
    memset(st, 0, 16*sizeof(st[0][0]));
    memset(barr, 0, bsz*sizeof(barr[0]));
}//end cbcenc()

