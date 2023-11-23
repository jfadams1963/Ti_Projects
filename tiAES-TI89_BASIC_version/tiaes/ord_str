ord_str(ob)
Func
(c) mat (encrypted output block)
(c) returns cypher string

Local r,c,cs,ch

""->cs (c) empty cypher string

(c) load by column
For c,1,4
	For r,1,4
		zh256[ob[r,c]+1]->ch
		cs&ch->cs
	EndFor
EndFor

Return cs
EndFunc
