//cryputils.c
//(c) 2023 J Adams jfa63@duck.com
//Released under the 2-clause BSD license.

#include "core.h"


//copy new state to state
void cpyns_st() {
    int r,c;
    for (r=0; r<4; r++) {
        for (c=0; c<4; c++) {
            st[r][c] = ns[r][c];
        }
    }
}

//copy temp block to iv
void cpytb_iv() {
    int r,c;
    for (r=0; r<4; r++) {
        for (c=0; c<4; c++) {
            iv[r][c] = tb[r][c];
        }
    }
}

//copy state to temp block
void cpyst_tb() {
    int r,c;
    for (r=0; r<4; r++) {
        for (c=0; c<4; c++) {
            tb[r][c] = st[r][c];
        }
    }
}

//copy state to IV
void cpyst_iv() {
    int r,c;
    for (r=0; r<4; r++) {
        for (c=0; c<4; c++) {
            iv[r][c] = st[r][c];
        }
    }
}

