	.text
	.file	"test.c"
	.globl	routine                         # -- Begin function routine
	.p2align	4, 0x90
	.type	routine,@function
routine:                                # @routine
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	$0, -20(%rbp)
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	cmpl	$1000000, -20(%rbp)             # imm = 0xF4240
	jge	.LBB0_4
# %bb.2:                                #   in Loop: Header=BB0_1 Depth=1
	movq	-16(%rbp), %rax
	movl	12(%rax), %ecx
	addl	$1, %ecx
	movl	%ecx, 12(%rax)
# %bb.3:                                #   in Loop: Header=BB0_1 Depth=1
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	.LBB0_1
.LBB0_4:
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	routine, .Lfunc_end0-routine
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movl	$0, -4(%rbp)
	movl	$0, -28(%rbp)
	leaq	-16(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	leaq	routine(%rip), %rdx
	leaq	-40(%rbp), %rcx
	callq	pthread_create@PLT
	cmpl	$0, %eax
	je	.LBB1_2
# %bb.1:
	movl	$1, -4(%rbp)
	jmp	.LBB1_9
.LBB1_2:
	leaq	-24(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	leaq	routine(%rip), %rdx
	leaq	-40(%rbp), %rcx
	callq	pthread_create@PLT
	cmpl	$0, %eax
	je	.LBB1_4
# %bb.3:
	movl	$1, -4(%rbp)
	jmp	.LBB1_9
.LBB1_4:
	movq	-16(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	pthread_join@PLT
	cmpl	$0, %eax
	je	.LBB1_6
# %bb.5:
	movl	$1, -4(%rbp)
	jmp	.LBB1_9
.LBB1_6:
	movq	-24(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	pthread_join@PLT
	cmpl	$0, %eax
	je	.LBB1_8
# %bb.7:
	movl	$1, -4(%rbp)
	jmp	.LBB1_9
.LBB1_8:
	movl	-28(%rbp), %esi
	leaq	.L.str(%rip), %rdi
	movb	$0, %al
	callq	printf@PLT
	movl	$0, -4(%rbp)
.LBB1_9:
	movl	-4(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"Number of Mail: %d\n"
	.size	.L.str, 20

	.ident	"Ubuntu clang version 15.0.7"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym routine
	.addrsig_sym pthread_create
	.addrsig_sym pthread_join
	.addrsig_sym printf
