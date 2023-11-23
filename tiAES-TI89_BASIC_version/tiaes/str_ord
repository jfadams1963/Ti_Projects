str_ord(cs)
Func
(c) string (cypher string)
(c) returns a state block

Local i,r,c,st

newMat(4,4)->st
1->i
(c) load by column
For c,1,4
	For r,1,4
		expr("0h"&mid(cs,i,2))->st[r,c]
		i+2->i
	EndFor
EndFor

Return st
EndFunc
