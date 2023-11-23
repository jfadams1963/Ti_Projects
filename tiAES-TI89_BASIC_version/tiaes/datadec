datadec(file)
Prgm
(c) string (filename)

Local ft,j,i,t,rsz,csz,sz,cel,ky,w,r,dout,dir

ClrIO 
blnktb()
Disp file
InputStr "y/n",r
If r!="y"
  goto quit

(c) test if file exists and protect
Try
  Archive #file
Else
  Pause "Filename?"
  Goto quit
EndTry

(c) output file
Lbl name
InputStr "Output",dout
If dout="dout" or dout="out" or dout=file
  Goto name

(c) get passphrase
InputStr "Passphrase",ky

(c) set cwd to tiaes\
setFold(tiaes)->dir
dir&"\"&file->file
dir&"\"&dout->dout

(c) set globals
setglbls(dim(ky))

(c) estimate time; based on TI-89 HW2
Disp getestd(blkcnt(file,32))
InputStr "Continue?",r
If f!="y"
  Goto quit

(c) file types
getType(#file)->ft
If ft="STR" Then
  Goto dostr
ElseIf ft="LIST" Then
  Goto dolst
ElseIf ft="MAT" Then
  Goto domat
Else
  Goto quit
EndIf

(c) strings
Lbl dostr
Disp "Busy"
kprep(ky)->w
cbcdec(#file,w)
out->#dout
Archive #dout
DelVar out,st
Goto end

(c) lists
Lbl dolst
dim(#file)->sz
#file->#dout
Disp "Busy"
kprep(ky)->w
For i,1,sz
  #file[i]->cel
  getType(cel)->t
  If t="STR" and cel!="" Then
    cbcdec(cel,w)
    out->#dout[i]
  EndIf
EndFor
Archive #dout
delVar out,st
Goto end

(c) matrices
Lbl domat
rowDim(#file)->rsz
colDim(#file)->csz
#file->#dout
Disp "Busy"
kprep(ky)->w
For j,1,csz
  For i,1,rsz
    #file[i,j]->cel
      getType(cel)->t
      If t="STR" and cel!="" Then
        cbcdec(cel,w)
        out->#dout[i,j]
    EndIf
  EndFor
EndFor
Archive #dout
DelVar out,st
Goto end

Lbl end
Pause "Done"

Lbl quit
setFold(#dir)
EndPrgm
