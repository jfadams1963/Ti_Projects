brkcnt(cd)
Prgm
(c) string (BF code)
(c) Returns the counts of open and
(c) close brackets to assist in
(c) troubleshooting bracket mis-matches.

Local ip,opnb,clob,sz

0->opnb
0->clob
dim(cd)->sz

For ip,1,sz
  If mid(cd,ip,1)="[" Then
    opnb+1->opnb
  ElseIf mid(cd,ip,1)="]" Then 
    clob+1->clob
  EndIf
EndFor

Disp "Open: "&string(opnb)
Disp "Close "&string(clob)
EndPrgm
