	.file	"bufferoverflow.c"
	.section	.rodata
.LC0:
	.string	"Enter the password: "
.LC1:
	.string	"thegeekstuff"
.LC2:
	.string	"Wrong Password"
.LC3:
	.string	"Correct Password"
	.align 8
.LC4:
	.string	"pass is 0x%x, or ascii character %c\n"
.LC5:
	.string	"Root privileges granted"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp       # char buf[15]; char pass;
	movb	$0, -1(%rbp)    # char pass = 0;
	movl	$.LC0, %edi     # printf("Enter the password: ");
	movl	$0, %eax        # ...
	call	printf          # ...
	leaq	-16(%rbp), %rax # rax = address of buf[0]
	movq	%rax, %rdi      # rdi = address of buf[0]
	call	gets            # gets(buff);
	leaq	-16(%rbp), %rax # rax = address of buf[0]
	movl	$.LC1, %esi     # esi = address of "thegeekstuff"[0]
	movq	%rax, %rdi      # rdi = address of buf[0]
	call	strcmp          # Is the string in buf == "thegeekstuff"?
	testl	%eax, %eax      # ...
	je	.L2                 # If so, (i.e., correct password) go to .L2
	movl	$.LC2, %edi     # Otherwise, puts("Wrong Password");
	call	puts            # ...
	jmp	.L3                 # Goto .L3
.L2:
	movl	$.LC3, %edi     # puts("Correct Password");
	call	puts            # ...
	movb	$1, -1(%rbp)    # pass = 1;
.L3:
	movsbl	-1(%rbp), %edx  # printf("stuff with %x %c\n", pass, pass);
	movsbl	-1(%rbp), %eax  # ...
	movl	%eax, %esi      # ...
	movl	$.LC4, %edi     # ...
	movl	$0, %eax        # ...
	call	printf          # ...
	cmpb	$0, -1(%rbp)    # if (pass == 0)
	je	.L4                 # exit
	movl	$.LC5, %edi     # else if (pass != 0)
	call	puts            # puts("Root privileges granted");
.L4:
	movl	$0, %eax        # exit the program
	leave
	ret
	.size	main, .-main
	.section	.note.GNU-stack,"",@progbits
