CC      = cc
CFLAGS  = -g -w -Wall -Wextra -Wl,--allow-multiple-definition 
RM      = rm -f


default: tiaes 

tiaes:
	$(CC) $(CFLAGS) -o tiaes tiaes.c cryputils.c encr.c decr.c keyutils.c sha256.c

clean:
	$(RM) tiaes
