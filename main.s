	.file	"main.c"
	.text
	.section	.rodata
.LC0:
	.string	"usage: %s <event-file-path>"
.LC1:
	.string	"keylogger enabled"
.LC2:
	.string	"opened  file descriptor: %d\n"
.LC3:
	.string	"event read failed"
.LC4:
	.string	"not keyboard event"
.LC5:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	cmpl	$2, -52(%rbp)
	je	.L2
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	leaq	.LC0(%rip), %rdx
	movq	%rax, %rsi
	movq	%rdx, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$-1, %edi
	call	exit@PLT
.L2:
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-64(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	open@PLT
	movl	%eax, -40(%rbp)
	movl	-40(%rbp), %eax
	leaq	.LC2(%rip), %rdx
	movl	%eax, %esi
	movq	%rdx, %rdi
	movl	$0, %eax
	call	printf@PLT
.L6:
	leaq	-32(%rbp), %rcx
	movl	-40(%rbp), %eax
	movl	$24, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	movl	%eax, -36(%rbp)
	cmpl	$0, -36(%rbp)
	jns	.L3
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$-2, %edi
	call	exit@PLT
.L3:
	movzwl	-16(%rbp), %eax
	cmpw	$1, %ax
	je	.L4
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L5
.L4:
	movzwl	-14(%rbp), %eax
	movzwl	%ax, %eax
	leaq	.LC5(%rip), %rdx
	movl	%eax, %esi
	movq	%rdx, %rdi
	movl	$0, %eax
	call	printf@PLT
.L5:
	jmp	.L6
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (GNU) 15.2.1 20251112"
	.section	.note.GNU-stack,"",@progbits
