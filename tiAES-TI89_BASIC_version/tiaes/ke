ke(k)
Func
(c) mat (key array)
(c) Key expansion algorithm; generates key schedule.

Local w,wl,tp,rcon,rw,i

(c) Set w length (rows) based on nr=number of rounds.
nb*(nr+1)->wl
newMat(wl,4)->w

(c) The round key constants
{1,2,4,8,16,32,64,128,27,54,108,216}->rcon

(c) Load key into the first 4 rows of w
For i,1,nk
    k[i]->w[i]
EndFor

(c) Expansion algorithm
For i,nk+1,wl
    w[i-1]->tp
        If mod(i-1,nk)=0 Then
            [rcon[(i-1)/nk],0,0,0]->rw
            subword(rotword(tp)) xor rw->tp
        ElseIf nk>6 and mod(i-1,nk)=4 Then
            subword(tp)->tp
        EndIf
    w[i-nk] xor tp->w[i]
EndFor

Return w
EndFunc
