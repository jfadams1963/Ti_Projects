blkcnt(f,n)
Func
(c) string,int

Local r,c,i,j,cel,bc,l,t

0->bc
getType(#f)->t

(c) count strings
If t="STR" Then
	dim(#f)->l
	If mod(l,n)=0
		l/n->bc
	If mod(l,n)!=0
		int(l/n/+1->bc
	Return bc
EndIf

(c) count lists
If t="LIST" Then
	dim(#f)->i
	For r,1,i
		#f[r]->cel
		If getType(cel)!="STR" or cel=""
			Cycle
		dim(cel)->l
		If mod(l,n)!=0 Then
			bc+l/n->bc
		ElseIf mod(l,n)!=0 Then
			bc+int(l/n)+1->bc
		EndIf
	EndFor
	Return bc
EndIf

(c) count matrices
If t="MAT" Then
	rowDim(#f)->i
	colDim(#f)->j
	For r,1,i
		For c,1,j
			#f[r,c]->cel
			If getType(cel)!="STR" or cel=""
				Cycle
			dim(cel)->l
			If mod(l,n)=0 Then
				bc+l/n->bc
			ElseIf mod(l,n)!=0 Then
				bc+int(l,n)+1->bc
			EndIf
		EndFor
	EndFor
	Return bc
EndIf

EndFunc
