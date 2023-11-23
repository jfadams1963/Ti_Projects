mkhextbl()
Func
(c) builds the hex table used for encr() out put.

setMode("BASE","HEX")

Local n,hl
newList(256)->hl

For n,0,255
	padstr(mid(string(n),3),2)->hl[n]
EndFor

setMode("BASE","DEC")

Return hl
EndFunc
