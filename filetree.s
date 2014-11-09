	.section	__TEXT,__text,regular,pure_instructions
	.globl	_newNode
	.align	4, 0x90
_newNode:                               ## @newNode
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
	movabsq	$48, %rax
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movq	%rcx, -32(%rbp)
	movq	%rax, %rdi
	callq	_malloc
	movabsq	$255, %rdi
	movq	%rax, -40(%rbp)
	callq	_malloc
	movabsq	$255, %rdi
	movq	-40(%rbp), %rcx
	movq	%rax, 8(%rcx)
	callq	_malloc
	movq	-40(%rbp), %rcx
	movq	%rax, 16(%rcx)
	movq	-40(%rbp), %rax
	movq	8(%rax), %rdi
	movq	-8(%rbp), %rsi
	callq	_strcpy
	movq	-40(%rbp), %rcx
	movq	16(%rcx), %rdi
	movq	-16(%rbp), %rsi
	movq	%rax, -48(%rbp)         ## 8-byte Spill
	callq	_strcpy
	movl	-20(%rbp), %edx
	movq	-40(%rbp), %rcx
	movl	%edx, 24(%rcx)
	movq	-40(%rbp), %rcx
	movl	$0, 28(%rcx)
	movq	-40(%rbp), %rcx
	movq	$0, 32(%rcx)
	movq	-40(%rbp), %rcx
	movq	$0, 40(%rcx)
	movq	-32(%rbp), %rcx
	movq	%rcx, -32(%rbp)
	movq	-40(%rbp), %rcx
	movq	%rax, -56(%rbp)         ## 8-byte Spill
	movq	%rcx, %rax
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_findFile
	.align	4, 0x90
_findFile:                              ## @findFile
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
	subq	$32, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	-16(%rbp), %rsi
	movq	%rsi, -32(%rbp)
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$0, -32(%rbp)
	je	LBB1_5
## BB#2:                                ##   in Loop: Header=BB1_1 Depth=1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rdi
	movq	-24(%rbp), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB1_4
## BB#3:
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB1_6
LBB1_4:                                 ##   in Loop: Header=BB1_1 Depth=1
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -32(%rbp)
	jmp	LBB1_1
LBB1_5:
	movq	$0, -8(%rbp)
LBB1_6:
	movq	-8(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_changeDirectory
	.align	4, 0x90
_changeDirectory:                       ## @changeDirectory
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
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movl	$1, -28(%rbp)
	movl	$1, -32(%rbp)
	movq	-24(%rbp), %rdi
	callq	_strlen
	movl	%eax, %ecx
	movl	%ecx, -36(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-24(%rbp), %rdi
	leaq	L_.str(%rip), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB2_4
## BB#1:
	movq	-16(%rbp), %rax
	cmpq	$0, (%rax)
	je	LBB2_3
## BB#2:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB2_20
LBB2_3:
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB2_20
LBB2_4:
	movq	-24(%rbp), %rax
	movsbl	(%rax), %ecx
	cmpl	$47, %ecx
	je	LBB2_6
## BB#5:
	leaq	L_.str1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	$0, -8(%rbp)
	movl	%eax, -52(%rbp)         ## 4-byte Spill
	jmp	LBB2_20
LBB2_6:
	movq	-24(%rbp), %rdi
	callq	_strlen
	cmpq	$1, %rax
	jne	LBB2_8
## BB#7:
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB2_20
LBB2_8:
	jmp	LBB2_9
LBB2_9:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB2_10 Depth 2
	jmp	LBB2_10
LBB2_10:                                ##   Parent Loop BB2_9 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movb	$0, %al
	movslq	-32(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movsbl	(%rdx,%rcx), %esi
	cmpl	$0, %esi
	movb	%al, -53(%rbp)          ## 1-byte Spill
	je	LBB2_12
## BB#11:                               ##   in Loop: Header=BB2_10 Depth=2
	movslq	-32(%rbp), %rax
	movq	-24(%rbp), %rcx
	movsbl	(%rcx,%rax), %edx
	cmpl	$47, %edx
	setne	%sil
	movb	%sil, -53(%rbp)         ## 1-byte Spill
LBB2_12:                                ##   in Loop: Header=BB2_10 Depth=2
	movb	-53(%rbp), %al          ## 1-byte Reload
	testb	$1, %al
	jne	LBB2_13
	jmp	LBB2_14
LBB2_13:                                ##   in Loop: Header=BB2_10 Depth=2
	movl	-32(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -32(%rbp)
	jmp	LBB2_10
LBB2_14:                                ##   in Loop: Header=BB2_9 Depth=1
	movslq	-32(%rbp), %rax
	movq	-24(%rbp), %rcx
	movb	$0, (%rcx,%rax)
	movq	-48(%rbp), %rax
	movq	32(%rax), %rdi
	movq	-24(%rbp), %rax
	movslq	-28(%rbp), %rcx
	addq	%rcx, %rax
	movq	%rax, %rsi
	callq	_findFile
	movq	%rax, -48(%rbp)
	cmpq	$0, -48(%rbp)
	jne	LBB2_16
## BB#15:
	leaq	L_.str1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	$0, -8(%rbp)
	movl	%eax, -60(%rbp)         ## 4-byte Spill
	jmp	LBB2_20
LBB2_16:                                ##   in Loop: Header=BB2_9 Depth=1
	movl	-32(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jne	LBB2_18
## BB#17:
	movq	-48(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB2_20
LBB2_18:                                ##   in Loop: Header=BB2_9 Depth=1
	jmp	LBB2_19
LBB2_19:                                ##   in Loop: Header=BB2_9 Depth=1
	movslq	-32(%rbp), %rax
	movq	-24(%rbp), %rcx
	movb	$47, (%rcx,%rax)
	movl	-32(%rbp), %edx
	addl	$1, %edx
	movl	%edx, -32(%rbp)
	movl	%edx, -28(%rbp)
	jmp	LBB2_9
LBB2_20:
	movq	-8(%rbp), %rax
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_split
	.align	4, 0x90
_split:                                 ## @split
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
	subq	$80, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	%rdx, -32(%rbp)
	movq	-16(%rbp), %rdi
	callq	_strlen
	subq	$1, %rax
	movl	%eax, %ecx
	movl	%ecx, -36(%rbp)
	movq	-16(%rbp), %rax
	movsbl	(%rax), %ecx
	cmpl	$47, %ecx
	je	LBB3_2
## BB#1:
	movl	$0, -4(%rbp)
	jmp	LBB3_9
LBB3_2:
	jmp	LBB3_3
LBB3_3:                                 ## =>This Inner Loop Header: Depth=1
	movslq	-36(%rbp), %rax
	movq	-16(%rbp), %rcx
	movsbl	(%rcx,%rax), %edx
	cmpl	$47, %edx
	je	LBB3_5
## BB#4:                                ##   in Loop: Header=BB3_3 Depth=1
	movl	-36(%rbp), %eax
	addl	$4294967295, %eax       ## imm = 0xFFFFFFFF
	movl	%eax, -36(%rbp)
	jmp	LBB3_3
LBB3_5:
	cmpl	$0, -36(%rbp)
	jne	LBB3_7
## BB#6:
	movq	-24(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movslq	%eax, %rdx
	callq	_strncpy
	movq	%rax, -48(%rbp)         ## 8-byte Spill
	jmp	LBB3_8
LBB3_7:
	movq	-24(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movslq	-36(%rbp), %rdx
	callq	_strncpy
	movq	%rax, -56(%rbp)         ## 8-byte Spill
LBB3_8:
	movq	-32(%rbp), %rdi
	movq	-16(%rbp), %rax
	movl	-36(%rbp), %ecx
	addl	$1, %ecx
	movslq	%ecx, %rdx
	addq	%rdx, %rax
	movq	-16(%rbp), %rdx
	movq	%rdi, -64(%rbp)         ## 8-byte Spill
	movq	%rdx, %rdi
	movq	%rax, -72(%rbp)         ## 8-byte Spill
	callq	_strlen
	movslq	-36(%rbp), %rdx
	subq	%rdx, %rax
	movq	-64(%rbp), %rdi         ## 8-byte Reload
	movq	-72(%rbp), %rsi         ## 8-byte Reload
	movq	%rax, %rdx
	callq	_strncpy
	movl	$1, -4(%rbp)
	movq	%rax, -80(%rbp)         ## 8-byte Spill
LBB3_9:
	movl	-4(%rbp), %eax
	addq	$80, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_newFile
	.align	4, 0x90
_newFile:                               ## @newFile
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
	subq	$96, %rsp
	movabsq	$255, %rax
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movq	%rax, %rdi
	callq	_malloc
	movabsq	$255, %rdi
	movq	%rax, -40(%rbp)
	callq	_malloc
	movq	%rax, -48(%rbp)
	movq	-24(%rbp), %rdi
	movq	-40(%rbp), %rsi
	movq	-48(%rbp), %rdx
	callq	_split
	cmpl	$0, %eax
	jne	LBB4_2
## BB#1:
	leaq	L_.str1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-16(%rbp), %rdi
	movq	%rdi, -8(%rbp)
	movl	%eax, -60(%rbp)         ## 4-byte Spill
	jmp	LBB4_17
LBB4_2:
	movq	-48(%rbp), %rdi
	callq	_strlen
	cmpq	$0, %rax
	jne	LBB4_4
## BB#3:
	leaq	L_.str2(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-16(%rbp), %rdi
	movq	%rdi, -8(%rbp)
	movl	%eax, -64(%rbp)         ## 4-byte Spill
	jmp	LBB4_17
LBB4_4:
	jmp	LBB4_5
LBB4_5:
	movq	-16(%rbp), %rdi
	movq	-40(%rbp), %rsi
	callq	_changeDirectory
	movq	%rax, -56(%rbp)
	cmpq	$0, -56(%rbp)
	jne	LBB4_7
## BB#6:
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB4_17
LBB4_7:
	cmpl	$0, -28(%rbp)
	je	LBB4_12
## BB#8:
	movq	-56(%rbp), %rax
	movq	40(%rax), %rdi
	movq	-48(%rbp), %rsi
	callq	_findFile
	cmpq	$0, %rax
	je	LBB4_10
## BB#9:
	leaq	L_.str3(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -68(%rbp)         ## 4-byte Spill
	jmp	LBB4_11
LBB4_10:
	movq	-56(%rbp), %rax
	movq	40(%rax), %rdi
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rsi
	movl	-28(%rbp), %edx
	movq	-56(%rbp), %rcx
	movq	%rdi, -80(%rbp)         ## 8-byte Spill
	movq	%rax, %rdi
	callq	_newNode
	movq	-80(%rbp), %rdi         ## 8-byte Reload
	movq	%rax, %rsi
	callq	_add
	movq	-56(%rbp), %rcx
	movq	%rax, 40(%rcx)
	movq	-56(%rbp), %rax
	movl	28(%rax), %edx
	addl	$1, %edx
	movl	%edx, 28(%rax)
LBB4_11:
	jmp	LBB4_16
LBB4_12:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rdi
	movq	-48(%rbp), %rsi
	callq	_findFile
	cmpq	$0, %rax
	je	LBB4_14
## BB#13:
	leaq	L_.str3(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -84(%rbp)         ## 4-byte Spill
	jmp	LBB4_15
LBB4_14:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rdi
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rsi
	movl	-28(%rbp), %edx
	movq	-56(%rbp), %rcx
	movq	%rdi, -96(%rbp)         ## 8-byte Spill
	movq	%rax, %rdi
	callq	_newNode
	movq	-96(%rbp), %rdi         ## 8-byte Reload
	movq	%rax, %rsi
	callq	_add
	movq	-56(%rbp), %rcx
	movq	%rax, 32(%rcx)
	movq	-56(%rbp), %rax
	movl	28(%rax), %edx
	addl	$1, %edx
	movl	%edx, 28(%rax)
LBB4_15:
	jmp	LBB4_16
LBB4_16:
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
LBB4_17:
	movq	-8(%rbp), %rax
	addq	$96, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_removeFile
	.align	4, 0x90
_removeFile:                            ## @removeFile
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
	subq	$96, %rsp
	movabsq	$255, %rax
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	%rax, %rdi
	callq	_malloc
	movabsq	$255, %rdi
	movq	%rax, -32(%rbp)
	callq	_malloc
	movq	%rax, -40(%rbp)
	movq	-24(%rbp), %rdi
	movq	-32(%rbp), %rsi
	movq	-40(%rbp), %rdx
	callq	_split
	movq	-16(%rbp), %rdi
	movq	-32(%rbp), %rsi
	movl	%eax, -76(%rbp)         ## 4-byte Spill
	callq	_changeDirectory
	movq	%rax, -48(%rbp)
	cmpq	$0, -48(%rbp)
	jne	LBB5_2
## BB#1:
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB5_22
LBB5_2:
	movq	-48(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -56(%rbp)
	movl	$0, -68(%rbp)
LBB5_3:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB5_5 Depth 2
	cmpl	$2, -68(%rbp)
	jge	LBB5_21
## BB#4:                                ##   in Loop: Header=BB5_3 Depth=1
	movl	$1, -72(%rbp)
	movq	$0, -64(%rbp)
LBB5_5:                                 ##   Parent Loop BB5_3 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	cmpq	$0, -56(%rbp)
	je	LBB5_19
## BB#6:                                ##   in Loop: Header=BB5_5 Depth=2
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rdi
	movq	-40(%rbp), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB5_18
## BB#7:
	cmpl	$0, -68(%rbp)
	jne	LBB5_9
## BB#8:
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	cmpl	$0, 28(%rax)
	jne	LBB5_16
LBB5_9:
	cmpq	$0, -64(%rbp)
	jne	LBB5_14
## BB#10:
	cmpl	$0, -68(%rbp)
	je	LBB5_12
## BB#11:
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	movq	8(%rax), %rax
	movq	-48(%rbp), %rcx
	movq	%rax, 40(%rcx)
	jmp	LBB5_13
LBB5_12:
	movq	-48(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movq	-48(%rbp), %rcx
	movq	%rax, 32(%rcx)
LBB5_13:
	jmp	LBB5_15
LBB5_14:
	movq	-56(%rbp), %rax
	movq	8(%rax), %rax
	movq	-64(%rbp), %rcx
	movq	%rax, 8(%rcx)
LBB5_15:
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	callq	_free
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	callq	_free
	movq	-48(%rbp), %rax
	movl	28(%rax), %ecx
	addl	$4294967295, %ecx       ## imm = 0xFFFFFFFF
	movl	%ecx, 28(%rax)
	jmp	LBB5_17
LBB5_16:
	leaq	L_.str4(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -80(%rbp)         ## 4-byte Spill
LBB5_17:
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB5_22
LBB5_18:                                ##   in Loop: Header=BB5_5 Depth=2
	movq	-56(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	-56(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -56(%rbp)
	jmp	LBB5_5
LBB5_19:                                ##   in Loop: Header=BB5_3 Depth=1
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, -56(%rbp)
## BB#20:                               ##   in Loop: Header=BB5_3 Depth=1
	movl	-68(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -68(%rbp)
	jmp	LBB5_3
LBB5_21:
	leaq	L_.str1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-16(%rbp), %rdi
	movq	%rdi, -8(%rbp)
	movl	%eax, -84(%rbp)         ## 4-byte Spill
LBB5_22:
	movq	-8(%rbp), %rax
	addq	$96, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_listDirectory
	.align	4, 0x90
_listDirectory:                         ## @listDirectory
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp32:
	.cfi_def_cfa_offset 16
Ltmp33:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp34:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	callq	_changeDirectory
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	LBB6_2
## BB#1:
	leaq	L_.str5(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	jmp	LBB6_8
LBB6_2:
	leaq	L_.str6(%rip), %rdi
	movq	-16(%rbp), %rsi
	movb	$0, %al
	callq	_printf
	movq	-24(%rbp), %rsi
	movq	32(%rsi), %rsi
	movq	%rsi, -32(%rbp)
	movl	%eax, -40(%rbp)         ## 4-byte Spill
LBB6_3:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$0, -32(%rbp)
	je	LBB6_5
## BB#4:                                ##   in Loop: Header=BB6_3 Depth=1
	leaq	L_.str7(%rip), %rdi
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rsi
	movb	$0, %al
	callq	_printf
	movq	-32(%rbp), %rsi
	movq	8(%rsi), %rsi
	movq	%rsi, -32(%rbp)
	movl	%eax, -44(%rbp)         ## 4-byte Spill
	jmp	LBB6_3
LBB6_5:
	movq	-24(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, -32(%rbp)
LBB6_6:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$0, -32(%rbp)
	je	LBB6_8
## BB#7:                                ##   in Loop: Header=BB6_6 Depth=1
	leaq	L_.str7(%rip), %rdi
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rsi
	movb	$0, %al
	callq	_printf
	movq	-32(%rbp), %rsi
	movq	8(%rsi), %rsi
	movq	%rsi, -32(%rbp)
	movl	%eax, -48(%rbp)         ## 4-byte Spill
	jmp	LBB6_6
LBB6_8:
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_showTree
	.align	4, 0x90
_showTree:                              ## @showTree
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp37:
	.cfi_def_cfa_offset 16
Ltmp38:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp39:
	.cfi_def_cfa_register %rbp
	subq	$80, %rsp
	movq	%rdi, -8(%rbp)
	movb	$0, %al
	callq	_queueConstructor
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rdi
	movq	-8(%rbp), %rsi
	callq	_addQueue
	movl	$0, -20(%rbp)
	movq	%rax, -48(%rbp)         ## 8-byte Spill
LBB7_1:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB7_6 Depth 2
                                        ##     Child Loop BB7_9 Depth 2
	movq	-16(%rbp), %rax
	cmpq	$0, (%rax)
	je	LBB7_12
## BB#2:                                ##   in Loop: Header=BB7_1 Depth=1
	movq	-16(%rbp), %rdi
	callq	_removeQueue
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	16(%rax), %rdi
	leaq	L_.str8(%rip), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	je	LBB7_4
## BB#3:                                ##   in Loop: Header=BB7_1 Depth=1
	leaq	L_.str9(%rip), %rdi
	movq	-32(%rbp), %rax
	movq	16(%rax), %rsi
	movq	-32(%rbp), %rax
	movq	8(%rax), %rdx
	movb	$0, %al
	callq	_printf
	movl	%eax, -52(%rbp)         ## 4-byte Spill
	jmp	LBB7_5
LBB7_4:                                 ##   in Loop: Header=BB7_1 Depth=1
	leaq	L_.str10(%rip), %rdi
	movq	-32(%rbp), %rax
	movq	16(%rax), %rsi
	movq	-32(%rbp), %rax
	movq	8(%rax), %rdx
	movb	$0, %al
	callq	_printf
	movl	%eax, -56(%rbp)         ## 4-byte Spill
LBB7_5:                                 ##   in Loop: Header=BB7_1 Depth=1
	movq	-32(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -40(%rbp)
LBB7_6:                                 ##   Parent Loop BB7_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	cmpq	$0, -40(%rbp)
	je	LBB7_8
## BB#7:                                ##   in Loop: Header=BB7_6 Depth=2
	leaq	L_.str11(%rip), %rdi
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rsi
	movb	$0, %al
	callq	_printf
	movq	-16(%rbp), %rdi
	movq	-40(%rbp), %rsi
	movq	(%rsi), %rsi
	movl	%eax, -60(%rbp)         ## 4-byte Spill
	callq	_addQueue
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rsi
	movq	%rsi, -40(%rbp)
	movq	%rax, -72(%rbp)         ## 8-byte Spill
	jmp	LBB7_6
LBB7_8:                                 ##   in Loop: Header=BB7_1 Depth=1
	movq	-32(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, -40(%rbp)
LBB7_9:                                 ##   Parent Loop BB7_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	cmpq	$0, -40(%rbp)
	je	LBB7_11
## BB#10:                               ##   in Loop: Header=BB7_9 Depth=2
	leaq	L_.str11(%rip), %rdi
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rsi
	movb	$0, %al
	callq	_printf
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rsi
	movq	%rsi, -40(%rbp)
	movl	%eax, -76(%rbp)         ## 4-byte Spill
	jmp	LBB7_9
LBB7_11:                                ##   in Loop: Header=BB7_1 Depth=1
	jmp	LBB7_1
LBB7_12:
	addq	$80, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	".."

L_.str1:                                ## @.str1
	.asciz	"ERROR: No such file or directory.\n"

L_.str2:                                ## @.str2
	.asciz	"ERROR: Couldn't create such file or directory.\n"

L_.str3:                                ## @.str3
	.asciz	"ERROR: File or directory already exists.\n"

L_.str4:                                ## @.str4
	.asciz	"ERROR: Directory is not empty.\n"

L_.str5:                                ## @.str5
	.asciz	"ERROR: No such file or Directory.\n"

L_.str6:                                ## @.str6
	.asciz	"%s: \n"

L_.str7:                                ## @.str7
	.asciz	"  %s\n"

L_.str8:                                ## @.str8
	.asciz	"/"

L_.str9:                                ## @.str9
	.asciz	"%s/%s:\n"

L_.str10:                               ## @.str10
	.asciz	"%s%s:\n"

L_.str11:                               ## @.str11
	.asciz	"  %s \n"


.subsections_via_symbols
