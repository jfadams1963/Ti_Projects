xmult_nt(a,b)
Func
(c) int,int
(c) This is the "no table" version for reference.

If a*b=0
	Return 0
If a=1
	Return b
If b=1
	Return a

Local d,e,i,t
0->t

If (a and 1) > 0
	b->d
shift(a,-1)->a (c) binary division by two
For i,1,7
	If (a and 1) > 0 Then
		b->t
		For e,1,i
			xtime(t)->t
		EndFor
		d xor t->d
	EndIf
	shift(a,-1)->a
EndFor

Return d
EndFunc
