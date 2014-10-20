	.section	__TEXT,__text,regular,pure_instructions
	.globl	_itos
	.align	4, 0x90
_itos:                                  ## @itos
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
	movabsq	$11, %rax
	movl	%edi, -12(%rbp)
	movq	%rax, %rdi
	callq	_malloc
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movb	$0, 10(%rax)
	movl	$9, -28(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movb	$0, %al
	cmpl	$0, -12(%rbp)
	movb	%al, -29(%rbp)          ## 1-byte Spill
	jle	LBB0_3
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	cmpl	$0, -28(%rbp)
	setge	%al
	movb	%al, -29(%rbp)          ## 1-byte Spill
LBB0_3:                                 ##   in Loop: Header=BB0_1 Depth=1
	movb	-29(%rbp), %al          ## 1-byte Reload
	testb	$1, %al
	jne	LBB0_4
	jmp	LBB0_5
LBB0_4:                                 ##   in Loop: Header=BB0_1 Depth=1
	movl	$10, %eax
	movl	-12(%rbp), %ecx
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	cltd
	movl	-36(%rbp), %ecx         ## 4-byte Reload
	idivl	%ecx
	addl	$48, %edx
	movb	%dl, %sil
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	addl	$4294967295, %edx       ## imm = 0xFFFFFFFF
	movl	%edx, -28(%rbp)
	movslq	%eax, %rdi
	movq	-24(%rbp), %r8
	movb	%sil, (%r8,%rdi)
	movl	-12(%rbp), %eax
	cltd
	idivl	%ecx
	movl	%eax, -12(%rbp)
	jmp	LBB0_1
LBB0_5:
	cmpl	$-1, -28(%rbp)
	jne	LBB0_8
## BB#6:
	cmpl	$0, -12(%rbp)
	jle	LBB0_8
## BB#7:
	movq	$0, -8(%rbp)
	jmp	LBB0_9
LBB0_8:
	movq	-24(%rbp), %rax
	movslq	-28(%rbp), %rcx
	addq	%rcx, %rax
	addq	$1, %rax
	movq	%rax, -8(%rbp)
LBB0_9:
	movq	-8(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	ret
	.cfi_endproc

	.globl	_readFile
	.align	4, 0x90
_readFile:                              ## @readFile
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp7:
	.cfi_def_cfa_offset 16
Ltmp8:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp9:
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	LBB1_2
## BB#1:
	movq	$0, -8(%rbp)
	jmp	LBB1_10
LBB1_2:
	leaq	L_.str(%rip), %rsi
	movq	-16(%rbp), %rdi
	callq	_fopen
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	je	LBB1_8
## BB#3:
	leaq	L_.str1(%rip), %rsi
	movq	-32(%rbp), %rdi
	movq	-24(%rbp), %rdx
	movb	$0, %al
	callq	_fscanf
	movq	-24(%rbp), %rdx
	movslq	(%rdx), %rdx
	shlq	$2, %rdx
	movq	%rdx, %rdi
	movl	%eax, -48(%rbp)         ## 4-byte Spill
	callq	_malloc
	movq	%rax, -40(%rbp)
	movl	$0, -44(%rbp)
LBB1_4:                                 ## =>This Inner Loop Header: Depth=1
	movl	-44(%rbp), %eax
	movq	-24(%rbp), %rcx
	cmpl	(%rcx), %eax
	jge	LBB1_7
## BB#5:                                ##   in Loop: Header=BB1_4 Depth=1
	leaq	L_.str1(%rip), %rsi
	movq	-32(%rbp), %rdi
	movslq	-44(%rbp), %rax
	movq	-40(%rbp), %rcx
	shlq	$2, %rax
	addq	%rax, %rcx
	movq	%rcx, %rdx
	movb	$0, %al
	callq	_fscanf
	movl	%eax, -52(%rbp)         ## 4-byte Spill
## BB#6:                                ##   in Loop: Header=BB1_4 Depth=1
	movl	-44(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -44(%rbp)
	jmp	LBB1_4
LBB1_7:
	movq	-32(%rbp), %rdi
	callq	_fclose
	movq	-40(%rbp), %rdi
	movq	%rdi, -8(%rbp)
	movl	%eax, -56(%rbp)         ## 4-byte Spill
	jmp	LBB1_10
LBB1_8:
	leaq	L_.str2(%rip), %rdi
	movq	-16(%rbp), %rsi
	movb	$0, %al
	callq	_printf
	movl	%eax, -60(%rbp)         ## 4-byte Spill
## BB#9:
	movq	$0, -8(%rbp)
LBB1_10:
	movq	-8(%rbp), %rax
	addq	$64, %rsp
	popq	%rbp
	ret
	.cfi_endproc

	.globl	_writeFile
	.align	4, 0x90
_writeFile:                             ## @writeFile
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp12:
	.cfi_def_cfa_offset 16
Ltmp13:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp14:
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	leaq	L_.str3(%rip), %rax
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movl	%ecx, -24(%rbp)
	movq	-8(%rbp), %rdi
	movq	%rax, %rsi
	callq	_fopen
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	je	LBB2_8
## BB#1:
	cmpl	$0, -24(%rbp)
	jne	LBB2_3
## BB#2:
	leaq	L_.str1(%rip), %rsi
	movq	-32(%rbp), %rdi
	movl	-20(%rbp), %edx
	movb	$0, %al
	callq	_fprintf
	movl	%eax, -40(%rbp)         ## 4-byte Spill
LBB2_3:
	movl	$0, -36(%rbp)
LBB2_4:                                 ## =>This Inner Loop Header: Depth=1
	movl	-36(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	LBB2_7
## BB#5:                                ##   in Loop: Header=BB2_4 Depth=1
	leaq	L_.str1(%rip), %rsi
	movq	-32(%rbp), %rdi
	movslq	-36(%rbp), %rax
	movq	-16(%rbp), %rcx
	movl	(%rcx,%rax,4), %edx
	movb	$0, %al
	callq	_fprintf
	movl	%eax, -44(%rbp)         ## 4-byte Spill
## BB#6:                                ##   in Loop: Header=BB2_4 Depth=1
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	LBB2_4
LBB2_7:
	movq	-32(%rbp), %rdi
	callq	_fclose
	movl	%eax, -48(%rbp)         ## 4-byte Spill
	jmp	LBB2_9
LBB2_8:
	leaq	L_.str4(%rip), %rdi
	movq	-8(%rbp), %rsi
	movb	$0, %al
	callq	_printf
	movl	%eax, -52(%rbp)         ## 4-byte Spill
LBB2_9:
	addq	$64, %rsp
	popq	%rbp
	ret
	.cfi_endproc

	.globl	_readBinaryFile
	.align	4, 0x90
_readBinaryFile:                        ## @readBinaryFile
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp17:
	.cfi_def_cfa_offset 16
Ltmp18:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp19:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	leaq	L_.str5(%rip), %rax
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	movq	-8(%rbp), %rdi
	movq	%rax, %rsi
	callq	_fopen
	movq	%rax, -24(%rbp)
	movslq	-16(%rbp), %rax
	shlq	$2, %rax
	movq	%rax, %rdi
	callq	_malloc
	movq	%rax, -32(%rbp)
	cmpl	$0, -12(%rbp)
	je	LBB3_2
## BB#1:
	movl	$0, %edx
	movq	-24(%rbp), %rdi
	movslq	-12(%rbp), %rax
	shlq	$2, %rax
	movq	%rax, %rsi
	callq	_fseek
	movl	%eax, -40(%rbp)         ## 4-byte Spill
LBB3_2:
	movl	$0, -36(%rbp)
LBB3_3:                                 ## =>This Inner Loop Header: Depth=1
	movl	-36(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jge	LBB3_6
## BB#4:                                ##   in Loop: Header=BB3_3 Depth=1
	movabsq	$4, %rsi
	movabsq	$1, %rdx
	movslq	-36(%rbp), %rax
	movq	-32(%rbp), %rcx
	shlq	$2, %rax
	addq	%rax, %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rdi
	movq	%rax, %rcx
	callq	_fread
	movq	%rax, -48(%rbp)         ## 8-byte Spill
## BB#5:                                ##   in Loop: Header=BB3_3 Depth=1
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	LBB3_3
LBB3_6:
	movq	-32(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	ret
	.cfi_endproc

	.globl	_quickSort
	.align	4, 0x90
_quickSort:                             ## @quickSort
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp22:
	.cfi_def_cfa_offset 16
Ltmp23:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp24:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	movl	-12(%rbp), %edx
	cmpl	-16(%rbp), %edx
	jne	LBB4_2
## BB#1:
	jmp	LBB4_21
LBB4_2:
	movl	$2, %eax
	movl	-12(%rbp), %ecx
	movl	%ecx, -20(%rbp)
	movl	-16(%rbp), %ecx
	movl	%ecx, -24(%rbp)
	movl	-20(%rbp), %ecx
	addl	-24(%rbp), %ecx
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	cltd
	movl	-36(%rbp), %ecx         ## 4-byte Reload
	idivl	%ecx
	movslq	%eax, %rsi
	movq	-8(%rbp), %rdi
	movl	(%rdi,%rsi,4), %eax
	movl	%eax, -32(%rbp)
LBB4_3:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB4_4 Depth 2
                                        ##     Child Loop BB4_9 Depth 2
	jmp	LBB4_4
LBB4_4:                                 ##   Parent Loop BB4_3 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movb	$0, %al
	movslq	-20(%rbp), %rcx
	movq	-8(%rbp), %rdx
	movl	(%rdx,%rcx,4), %esi
	cmpl	-32(%rbp), %esi
	movb	%al, -37(%rbp)          ## 1-byte Spill
	jge	LBB4_6
## BB#5:                                ##   in Loop: Header=BB4_4 Depth=2
	movl	-20(%rbp), %eax
	cmpl	-16(%rbp), %eax
	setl	%cl
	movb	%cl, -37(%rbp)          ## 1-byte Spill
LBB4_6:                                 ##   in Loop: Header=BB4_4 Depth=2
	movb	-37(%rbp), %al          ## 1-byte Reload
	testb	$1, %al
	jne	LBB4_7
	jmp	LBB4_8
LBB4_7:                                 ##   in Loop: Header=BB4_4 Depth=2
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	LBB4_4
LBB4_8:                                 ##   in Loop: Header=BB4_3 Depth=1
	jmp	LBB4_9
LBB4_9:                                 ##   Parent Loop BB4_3 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movb	$0, %al
	movl	-32(%rbp), %ecx
	movslq	-24(%rbp), %rdx
	movq	-8(%rbp), %rsi
	cmpl	(%rsi,%rdx,4), %ecx
	movb	%al, -38(%rbp)          ## 1-byte Spill
	jge	LBB4_11
## BB#10:                               ##   in Loop: Header=BB4_9 Depth=2
	movl	-24(%rbp), %eax
	cmpl	-12(%rbp), %eax
	setg	%cl
	movb	%cl, -38(%rbp)          ## 1-byte Spill
LBB4_11:                                ##   in Loop: Header=BB4_9 Depth=2
	movb	-38(%rbp), %al          ## 1-byte Reload
	testb	$1, %al
	jne	LBB4_12
	jmp	LBB4_13
LBB4_12:                                ##   in Loop: Header=BB4_9 Depth=2
	movl	-24(%rbp), %eax
	addl	$4294967295, %eax       ## imm = 0xFFFFFFFF
	movl	%eax, -24(%rbp)
	jmp	LBB4_9
LBB4_13:                                ##   in Loop: Header=BB4_3 Depth=1
	movl	-20(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jg	LBB4_15
## BB#14:                               ##   in Loop: Header=BB4_3 Depth=1
	movslq	-20(%rbp), %rax
	movq	-8(%rbp), %rcx
	movl	(%rcx,%rax,4), %edx
	movl	%edx, -28(%rbp)
	movslq	-24(%rbp), %rax
	movq	-8(%rbp), %rcx
	movl	(%rcx,%rax,4), %edx
	movslq	-20(%rbp), %rax
	movq	-8(%rbp), %rcx
	movl	%edx, (%rcx,%rax,4)
	movl	-28(%rbp), %edx
	movslq	-24(%rbp), %rax
	movq	-8(%rbp), %rcx
	movl	%edx, (%rcx,%rax,4)
	movl	-20(%rbp), %edx
	addl	$1, %edx
	movl	%edx, -20(%rbp)
	movl	-24(%rbp), %edx
	addl	$4294967295, %edx       ## imm = 0xFFFFFFFF
	movl	%edx, -24(%rbp)
LBB4_15:                                ##   in Loop: Header=BB4_3 Depth=1
	jmp	LBB4_16
LBB4_16:                                ##   in Loop: Header=BB4_3 Depth=1
	movl	-20(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jle	LBB4_3
## BB#17:
	movl	-12(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	LBB4_19
## BB#18:
	movq	-8(%rbp), %rdi
	movl	-12(%rbp), %esi
	movl	-24(%rbp), %edx
	callq	_quickSort
LBB4_19:
	movl	-16(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jle	LBB4_21
## BB#20:
	movq	-8(%rbp), %rdi
	movl	-20(%rbp), %esi
	movl	-16(%rbp), %edx
	callq	_quickSort
LBB4_21:
	addq	$48, %rsp
	popq	%rbp
	ret
	.cfi_endproc

	.globl	_merge
	.align	4, 0x90
_merge:                                 ## @merge
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp27:
	.cfi_def_cfa_offset 16
Ltmp28:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp29:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movl	%ecx, -24(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -32(%rbp)
	movl	$0, -36(%rbp)
	movl	-20(%rbp), %ecx
	addl	-24(%rbp), %ecx
	movslq	%ecx, %rsi
	shlq	$2, %rsi
	movq	%rsi, %rdi
	callq	_malloc
	movq	%rax, -48(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -36(%rbp)
LBB5_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-36(%rbp), %eax
	movl	-20(%rbp), %ecx
	addl	-24(%rbp), %ecx
	cmpl	%ecx, %eax
	jge	LBB5_13
## BB#2:                                ##   in Loop: Header=BB5_1 Depth=1
	movl	-28(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jne	LBB5_4
## BB#3:                                ##   in Loop: Header=BB5_1 Depth=1
	movl	-32(%rbp), %eax
	movl	%eax, %ecx
	addl	$1, %ecx
	movl	%ecx, -32(%rbp)
	movslq	%eax, %rdx
	movq	-16(%rbp), %rsi
	movl	(%rsi,%rdx,4), %eax
	movslq	-36(%rbp), %rdx
	movq	-48(%rbp), %rsi
	movl	%eax, (%rsi,%rdx,4)
	jmp	LBB5_11
LBB5_4:                                 ##   in Loop: Header=BB5_1 Depth=1
	movl	-32(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jne	LBB5_6
## BB#5:                                ##   in Loop: Header=BB5_1 Depth=1
	movl	-28(%rbp), %eax
	movl	%eax, %ecx
	addl	$1, %ecx
	movl	%ecx, -28(%rbp)
	movslq	%eax, %rdx
	movq	-8(%rbp), %rsi
	movl	(%rsi,%rdx,4), %eax
	movslq	-36(%rbp), %rdx
	movq	-48(%rbp), %rsi
	movl	%eax, (%rsi,%rdx,4)
	jmp	LBB5_10
LBB5_6:                                 ##   in Loop: Header=BB5_1 Depth=1
	movslq	-28(%rbp), %rax
	movq	-8(%rbp), %rcx
	movl	(%rcx,%rax,4), %edx
	movslq	-32(%rbp), %rax
	movq	-16(%rbp), %rcx
	cmpl	(%rcx,%rax,4), %edx
	jge	LBB5_8
## BB#7:                                ##   in Loop: Header=BB5_1 Depth=1
	movl	-28(%rbp), %eax
	movl	%eax, %ecx
	addl	$1, %ecx
	movl	%ecx, -28(%rbp)
	movslq	%eax, %rdx
	movq	-8(%rbp), %rsi
	movl	(%rsi,%rdx,4), %eax
	movslq	-36(%rbp), %rdx
	movq	-48(%rbp), %rsi
	movl	%eax, (%rsi,%rdx,4)
	jmp	LBB5_9
LBB5_8:                                 ##   in Loop: Header=BB5_1 Depth=1
	movl	-32(%rbp), %eax
	movl	%eax, %ecx
	addl	$1, %ecx
	movl	%ecx, -32(%rbp)
	movslq	%eax, %rdx
	movq	-16(%rbp), %rsi
	movl	(%rsi,%rdx,4), %eax
	movslq	-36(%rbp), %rdx
	movq	-48(%rbp), %rsi
	movl	%eax, (%rsi,%rdx,4)
LBB5_9:                                 ##   in Loop: Header=BB5_1 Depth=1
	jmp	LBB5_10
LBB5_10:                                ##   in Loop: Header=BB5_1 Depth=1
	jmp	LBB5_11
LBB5_11:                                ##   in Loop: Header=BB5_1 Depth=1
	jmp	LBB5_12
LBB5_12:                                ##   in Loop: Header=BB5_1 Depth=1
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	LBB5_1
LBB5_13:
	movq	-48(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	ret
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"r"

L_.str1:                                ## @.str1
	.asciz	"%d\n"

L_.str2:                                ## @.str2
	.asciz	"Error leyendo archivo \"%s\" \n"

L_.str3:                                ## @.str3
	.asciz	"w"

L_.str4:                                ## @.str4
	.asciz	"Error creando archivo \"%s\" \n"

L_.str5:                                ## @.str5
	.asciz	"rb"


.subsections_via_symbols
