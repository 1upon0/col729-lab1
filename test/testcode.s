	.text
	.file	"testcode.cpp"
	.globl	_Z3fooi
	.p2align	4, 0x90
	.type	_Z3fooi,@function
_Z3fooi:                                # @_Z3fooi
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp0:
	.cfi_def_cfa_offset 16
.Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -8(%rbp)
	movl	$0, -12(%rbp)
.LBB0_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	-12(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jge	.LBB0_4
# BB#2:                                 # %for.body
                                        #   in Loop: Header=BB0_1 Depth=1
	movabsq	$.L.str, %rdi
	movl	-12(%rbp), %esi
	movl	-8(%rbp), %edx
	movb	$0, %al
	callq	printf
	movl	%eax, -16(%rbp)         # 4-byte Spill
# BB#3:                                 # %for.inc
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	.LBB0_1
.LBB0_4:                                # %for.end
	cmpl	$0, -8(%rbp)
	jne	.LBB0_6
# BB#5:                                 # %if.then
	movl	$0, -4(%rbp)
	jmp	.LBB0_7
.LBB0_6:                                # %if.end
	movl	-8(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %edi
	callq	_Z3fooi
	addl	$1, %eax
	movl	%eax, -4(%rbp)
.LBB0_7:                                # %return
	movl	-4(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end0:
	.size	_Z3fooi, .Lfunc_end0-_Z3fooi
	.cfi_endproc

	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp3:
	.cfi_def_cfa_offset 16
.Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp5:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movabsq	$.L.str.1, %rdi
	movl	$0, -4(%rbp)
	movb	$0, %al
	callq	printf
	movl	$3, %edi
	movl	%eax, -12(%rbp)         # 4-byte Spill
	callq	_Z3fooi
	movabsq	$.L.str.2, %rdi
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %esi
	movb	$0, %al
	callq	printf
	movabsq	$.L.str.3, %rdi
	movl	%eax, -16(%rbp)         # 4-byte Spill
	movb	$0, %al
	callq	printf
	xorl	%esi, %esi
	movl	%eax, -20(%rbp)         # 4-byte Spill
	movl	%esi, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"This is foo! %d/%d\n"
	.size	.L.str, 20

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"This is main!\n"
	.size	.L.str.1, 15

	.type	.L.str.2,@object        # @.str.2
.L.str.2:
	.asciz	"Foo says %d\n"
	.size	.L.str.2, 13

	.type	.L.str.3,@object        # @.str.3
.L.str.3:
	.asciz	"Bye!\n"
	.size	.L.str.3, 6


	.ident	"clang version 4.0.0 (http://llvm.org/git/clang.git 12dcbf43701c142e8313d322c14b53a6c2957826) (http://llvm.org/git/llvm.git 9f072db19bc4f674b85c936c7983212c4034030d)"
	.section	".note.GNU-stack","",@progbits
