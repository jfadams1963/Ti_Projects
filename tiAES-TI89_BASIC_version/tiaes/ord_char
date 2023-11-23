ord_char(ob)
(c) mat (decyphered output block)
(c) returns a plaintext string

Local r,c,ps

(c) convert block to characters
char(ob)->ob
(c) empty plaintext string
""->ps

(c) unload by column
For c,1,4
	For r,1,4
		ps&ob[r,c]->ps
	EndFor
EndFor

Return ps
EndFunc
