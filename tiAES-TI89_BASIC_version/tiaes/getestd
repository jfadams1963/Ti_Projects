getestd(cnt)
Func
(c) int
(c) takes block count, returns approx. decrypt time
(c) times were determined on a TI-89 HW4
(c) t = time to decrypt one block
(c) k = time to expand key schedule
(c) the =0.035 sec is for CBC overhead

Local t,k,tot,h,m,s

If nr=10 then
	0.358+0.035->t
	0.18->k
	If cnt<153
		Goto doms
	If cnt>=153
		Goto dohm
ElseIf nr=12 Then
	0.442+0.035->t
	0.2->k
	If cnt<126
		Goto doms
	If cnt>=126
		Goto dohm
ElseIf nr=14 Then
	0.52+0.035->t
	0.25->k
	If cnt<108
		Goto doms
	If cnt>=108
		Goto dohm
EndIf

Lbl doms
round(cnt*t+k,2)->tot
string(iPart(tot))->m
string(round(fPart(tot)*60,0))->s
Return m&"m "&s&"s"

Lbl dohm
round((cnt+t+k)/60,2)->tot
string(iPart(tot))->h
string(int(fPart(tot)*60))->m
Return h&"h "&m&"m"

EndFunc
