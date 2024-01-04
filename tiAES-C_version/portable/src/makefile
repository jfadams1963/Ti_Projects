CC      = cc
CFLAGS  = -g -w -Wall -Wextra -Wl,--allow-multiple-definition 
RM      = rm -f


default: tiaes 

tiaes:
	$(CC) $(CFLAGS) -o tiaes tiaes.c cryputils.c encr.c decr.c keyutils.c

test:
	$(CC) $(CFLAGS) -o test tests.d/test.c keyutils.c

teste:
	$(CC) $(CFLAGS) -o teste tests.d/test_e.c tests.d/encr_test.c cryputils.c tests.d/keyutils_test.c

testd:
	$(CC) $(CFLAGS) -o testd tests.d/test_d.c encr.c decr.c cryputils.c tests.d/keyutils_test.c

clean:
	$(RM) *.o tiaes test teste testd emsg dmsg
