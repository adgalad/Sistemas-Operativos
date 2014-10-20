	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp2:
	.cfi_def_cfa_offset 16
Ltmp3:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp4:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rsi
	movq	8(%rsi), %rdi
	callq	_atoi
	movl	%eax, -20(%rbp)
	movq	-16(%rbp), %rsi
	movq	16(%rsi), %rdi
	callq	_atoi
	movq	-16(%rbp), %rsi
	movq	8(%rsi), %rdi
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	callq	_atoi
	movl	-36(%rbp), %ecx         ## 4-byte Reload
	subl	%eax, %ecx
	movl	%ecx, -24(%rbp)
	movq	-16(%rbp), %rsi
	movq	24(%rsi), %rdi
	movl	-20(%rbp), %esi
	movl	-24(%rbp), %edx
	callq	_readBinaryFile
	movl	$0, %esi
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rdi
	movl	-24(%rbp), %ecx
	subl	$1, %ecx
	movl	%ecx, %edx
	callq	_quickSort
	callq	_getpid
	movl	%eax, %edi
	callq	_itos
	movl	$0, %ecx
	movq	-32(%rbp), %rsi
	movl	-24(%rbp), %edx
	movq	%rax, %rdi
	callq	_writeFile
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.cfi_endproc


.subsections_via_symbols
