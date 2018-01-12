# linking with -Wl,-rpath and $(prefix)
# https://gcc.gnu.org/ml/gcc-help/2005-12/msg00017.html

# Each run:
# rm -f program && make program && echo && ldd ./program | grep boop | sed -r 's@^\s+@@' && echo && ./program

CC 	        = gcc -Wall -Wextra
AS          = as
LD          = ld
MAKEFLAGS  += --no-print-directory --warn-undefined-variables
BUILDDIR    = ${PWD}

#uclibc_root = "/home/jason/Desktop/uclibc"
# So we don't have to keep the whole library around to use this as a working example.
uclibc_root = "./pretend_uclibc"

default:
	make libboop
	make linker-shit
	make program

libboop:
	$(CC) -c -fPIC -o boop.o boop.c
	$(CC) -shared -o libboop.so boop.o -lm

linker-shit:
	# I literally just stole these files from uclibc and changed __uClibc_main to __libc_start_main. It actually works. Fuck yeah, lol.
	# I think the crt stands for c runtime, and the 1, i, and n are like... well... a math notation pun. ;P
	# This is the assembly setup code for C programs.
	cp -v $(uclibc_root)/libc/sysdeps/linux/x86_64/crt{1,i,n}.S .
	sed -i 's/__uClibc_main/__libc_start_main/g' crt1.S
	$(AS) -o crt1.{o,S}
	$(AS) -o crti.{o,S}
	$(AS) -o crtn.{o,S}

program:
	$(CC) -S -o program.{s,c}
	$(AS) -o program.{o,s}
	$(LD) -dynamic-linker /lib/ld-linux-x86-64.so.2 -o program -rpath=$(BUILDDIR) program.o libboop.so ./crt{1,i,n}.o -lc

clean:
	rm -f *.o *.so *.s *.S program
