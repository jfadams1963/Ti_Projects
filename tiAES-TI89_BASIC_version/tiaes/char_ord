char_ord(str)
Func
(c) string (<= 16 chars)

Local i,r,st

newMat(4,4)->st
0->i

For r,1,4
	[mid(str,1+i,1),mid(str,2+i,1),mid(str,3+i,1),mid(str,4+i,1)]->st[r]
	i+4->i
EndFor

Return ord(st^T)
EndFunc
