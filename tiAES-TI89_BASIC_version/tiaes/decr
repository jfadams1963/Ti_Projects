decr(w)
Prgm
(c) mat (key schedule = array w)
(c) Subroutine sections are labled with the FIPS 197
(c) nomenclature.

Local i,c,r,rd,ns

(c) round nr
(c) AddRoundKey()
nr->rd
st^T->ns
For r,1,4
  ns[r] xor w[r+rd*4]->ns[r]
EndFor
ns^T->st

(c) ShiftRows()
newMat(4,4)->ns
 (c) row 1, 0 shift
st[1]->ns[1]
 (c) row 2, 1 right shift
st[2,4]->ns[2,1]
st[2,1]->ns[2,2]
st[2,2]->ns[2,3]
st[2,3]->ns[2,4]
 (c) row 3, 2 right shifts
st[3,3]->ns[3,1]
st[3,4]->ns[3,2]
st[3,1]->ns[3,3]
st[3,2]->ns[3,4]
 (c) row 4, 3 right shifts
st[4,2]->ns[4,1]
st[4,3]->ns[4,2]
st[4,4]->ns[4,3]
st[4,1]->ns[4,4]
ns->st

(c) SubBytes()
For r,1,4
  For c,1,4
    sboxinv[st[r,c]+1]->st[r,c]
  EndFor
EndFor

(c) rounds nr-1 to 1
For rd,nr-1,1,-1
  (c) AddRoundKey()
  st^T->ns
  For r,1,4
    ns[r] xor w[r+rd*4]->ns[r]
  EndFor
  ns^T->st

  (c) MixColumns()
  newMat(4,4)->ns
  For c,1,4
    m14[st[1,c]+1] xor m11[st[2,c]+1] xor m13[st[3,c]+1] xor m9[st[4,c]+1]->ns[1,c]
    m9[st[1,c]+1] xor m14[st[2,c]+1] xor m11[st[3,c]+1] xor m13[st[4,c]+1]->ns[2,c]
    m13[st[1,c]+1] xor m9[st[2,c]+1] xor m14[st[3,c]+1] xor m11[st[4,c]+1]->ns[3,c]
    m11[st[1,c]+1] xor m13[st[2,c]+1] xor m9[st[3,c]+1] xor m14[st[4,c]+1]->ns[4,c]
  EndFor
  ns->st

  (c) ShiftRows()
  newMat(4,4)->ns
    (c) row 1, 0 shift
  st[1]->ns[1]
    (c) row 2, 1 right shift
  st[2,4]->ns[2,1]
  st[2,1]->ns[2,2]
  st[2,2]->ns[2,3]
  st[2,3]->ns[2,4]
    (c) row 3, 2 right shifts
  st[3,3]->ns[3,1]
  st[3,4]->ns[3,2]
  st[3,1]->ns[3,3]
  st[3,2]->ns[3,4]
    (c) row 4, 3 right shifts
  st[4,2]->ns[4,1]
  st[4,3]->ns[4,2]
  st[4,4]->ns[4,3]
  st[4,1]->ns[4,4]
  ns->st

  (c) SubBytes()
  For r,1,4
    For c,1,4
      sboxinv[st[r,c]+1]->st[r,c]
    EndFor
  EndFor
EndFor (c) end rounds nr-1 to 1

(c) round 0, whitening
(c) AddRoundKey()
0->rd
st^T->ns
For r,1,4
  ns[r] xor w[r+rd*4]->ns[r]
EndFor
ns^T->st

EndPrgm
