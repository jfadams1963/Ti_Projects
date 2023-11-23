setglbls(sz)
Prgm
(c) int
(c) size of the passphrase
(c) sets the globals bit, nk and nr 

If sz < 24 Then
	4->nk
	10->nr
	128->bit
ElseIf sz >= 24 and sz < 32 Then
	6->nk
	12->nr
	192->bit
ElseIf sz >= 32 Then
	8->nk
	14->nr
	256->bit
EndIf

EndPrgm
