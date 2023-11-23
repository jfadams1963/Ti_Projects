tiaes()
Prgm

Local fn

Lbl top
ClrDraw
(c)RclPic tiaes\splash

Toolbar
	Title " File "
		Item "Encrypt",fenc
		Item "Decrypt",fdec
	Title " Quit ",end
EndTBar

Lbl fenc
ClrIO
InputStr "File:",fn
tiaes\dataenc(fn)
Goto top

Lbl fdec
ClrIO
InputStr "File:",fn
tiaes\datadec(fn)
Goto top

Lbl end
ClrDraw
ClrIO
DispHome

EndPrgm
