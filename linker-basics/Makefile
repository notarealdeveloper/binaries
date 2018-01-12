# linking with -Wl,-rpath and $(prefix)
# https://gcc.gnu.org/ml/gcc-help/2005-12/msg00017.html

# Each run:
# rm -f program && make program && echo && ldd ./program | grep boop | sed -r 's@^\s+@@' && echo && ./program

CC 	        = gcc
AS          = gas
LD          = ld
INCLUDE     = -I.
LIB         = boop
LIBSO		= libboop.so
OUTFILE     = program
CFLAGS      = -g -O -Wall -Wextra
MAKEFLAGS  += --no-print-directory --warn-undefined-variables
BUILDDIR    = ${PWD}

default:
	make $(LIB)
	make $(OUTFILE)

$(LIB):
	$(CC) $(CFLAGS) -c -fPIC $(LIB).c
	$(CC) $(CFLAGS) -shared -o $(LIBSO) $(LIB).o -lm

$(OUTFILE):
	@ #$(CC) $(CFLAGS) -o $(OUTFILE) $(OUTFILE).c -Wl,-R$(BUILDDIR) $(LIB).so
	@ #$(CC) $(CFLAGS) -o $(OUTFILE) $(OUTFILE).c -Wl,-R,$(BUILDDIR) $(LIB).so
	@ #$(CC) $(CFLAGS) -o $(OUTFILE) $(OUTFILE).c -Wl,-rpath,$(BUILDDIR) $(LIB).so
	@ # This works if you want to compile completely manually.
	$(CC) $(CFLAGS) -o $(OUTFILE).o -c $(OUTFILE).c
	$(LD) -o $(OUTFILE) -dynamic-linker /lib/ld-2.23.so -rpath=$(BUILDDIR) $(OUTFILE).o $(LIBSO) /usr/lib/crt{1,i,n}.o -lc

clean:
	rm -f $(OUTFILE) $(OUTFILE).o $(LIBSO) $(LIB).o
