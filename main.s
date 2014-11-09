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
	subq	$64, %rsp
	movabsq	$255, %rax
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rax, %rdi
	callq	_malloc
	movabsq	$255, %rdi
	movq	%rax, -32(%rbp)
	callq	_malloc
	leaq	L_.str(%rip), %rsi
	movl	$0, %edx
	movabsq	$0, %rcx
	movq	%rax, -40(%rbp)
	movq	%rsi, %rdi
	callq	_newNode
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -56(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	leaq	L_.str1(%rip), %rdi
	movq	-32(%rbp), %rsi
	movq	-40(%rbp), %rdx
	movb	$0, %al
	callq	_scanf
	cmpl	$-1, %eax
	je	LBB0_18
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	movq	-32(%rbp), %rdi
	leaq	L_.str2(%rip), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB0_4
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	$0, %edx
	movq	-56(%rbp), %rdi
	movq	-40(%rbp), %rsi
	callq	_newFile
	movq	%rax, -56(%rbp)
	jmp	LBB0_17
LBB0_4:                                 ##   in Loop: Header=BB0_1 Depth=1
	movq	-32(%rbp), %rdi
	leaq	L_.str3(%rip), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB0_6
## BB#5:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	$1, %edx
	movq	-56(%rbp), %rdi
	movq	-40(%rbp), %rsi
	callq	_newFile
	movq	%rax, -56(%rbp)
	jmp	LBB0_16
LBB0_6:                                 ##   in Loop: Header=BB0_1 Depth=1
	movq	-32(%rbp), %rdi
	leaq	L_.str4(%rip), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB0_8
## BB#7:                                ##   in Loop: Header=BB0_1 Depth=1
	movq	-56(%rbp), %rdi
	movq	-40(%rbp), %rsi
	callq	_removeFile
	movq	%rax, -56(%rbp)
	jmp	LBB0_15
LBB0_8:                                 ##   in Loop: Header=BB0_1 Depth=1
	movq	-32(%rbp), %rdi
	leaq	L_.str5(%rip), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB0_10
## BB#9:                                ##   in Loop: Header=BB0_1 Depth=1
	movq	-56(%rbp), %rdi
	movq	-40(%rbp), %rsi
	callq	_listDirectory
	jmp	LBB0_14
LBB0_10:                                ##   in Loop: Header=BB0_1 Depth=1
	movq	-32(%rbp), %rdi
	leaq	L_.str6(%rip), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB0_12
## BB#11:                               ##   in Loop: Header=BB0_1 Depth=1
	movq	-56(%rbp), %rdi
	movq	-40(%rbp), %rsi
	callq	_changeDirectory
	movq	%rax, -56(%rbp)
	jmp	LBB0_13
LBB0_12:                                ##   in Loop: Header=BB0_1 Depth=1
	leaq	L_.str7(%rip), %rdi
	movq	-32(%rbp), %rsi
	movb	$0, %al
	callq	_printf
	movl	%eax, -60(%rbp)         ## 4-byte Spill
LBB0_13:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_14
LBB0_14:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_15
LBB0_15:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_16
LBB0_16:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_17
LBB0_17:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_1
LBB0_18:
	leaq	L_.str8(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-48(%rbp), %rdi
	movl	%eax, -64(%rbp)         ## 4-byte Spill
	callq	_showTree
	movl	$0, %eax
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.space	1

L_.str1:                                ## @.str1
	.asciz	"%s %s"

L_.str2:                                ## @.str2
	.asciz	"md"

L_.str3:                                ## @.str3
	.asciz	"ma"

L_.str4:                                ## @.str4
	.asciz	"rm"

L_.str5:                                ## @.str5
	.asciz	"ls"

L_.str6:                                ## @.str6
	.asciz	"cd"

L_.str7:                                ## @.str7
	.asciz	"Command \"%s\" not found.\n"

L_.str8:                                ## @.str8
	.asciz	"\n BFS of root directory:\n"


.subsections_via_symbols
