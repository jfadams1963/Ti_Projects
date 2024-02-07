CC      = cc
CFLAGS  = -g -w -Wall -Wextra
LDFLAGS = -Wl,--allow-multiple-definition -lssl -lcrypto 
RM      = rm -f
UNAME  := $(shell uname)

ifeq ($(UNAME),FreeBSD)
	CFLAGS += -DBSD
else ifeq ($(UNAME),Linux)
	CFLAGS += -DLINUX
endif

default: tiaes

tiaes:
	$(CC) $(CFLAGS) -o tiaes tiaes.c cryputils.c encr.c decr.c keyutils.c sha256.c $(LDFLAGS)
clean:
	$(RM) tiaes
