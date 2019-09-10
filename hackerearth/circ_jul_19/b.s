	.file	"b.cpp"
	.text
	.section	.text._ZNKSt5ctypeIcE8do_widenEc,"axG",@progbits,_ZNKSt5ctypeIcE8do_widenEc,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNKSt5ctypeIcE8do_widenEc
	.type	_ZNKSt5ctypeIcE8do_widenEc, @function
_ZNKSt5ctypeIcE8do_widenEc:
.LFB1321:
	.cfi_startproc
	movl	%esi, %eax
	ret
	.cfi_endproc
.LFE1321:
	.size	_ZNKSt5ctypeIcE8do_widenEc, .-_ZNKSt5ctypeIcE8do_widenEc
	.text
	.p2align 4,,15
	.type	_Z8binomialll.part.3, @function
_Z8binomialll.part.3:
.LFB2125:
	.cfi_startproc
	leaq	127(%rdi), %r8
	testq	%rdi, %rdi
	leaq	_ZL7factTab(%rip), %r10
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	cmovns	%rdi, %r8
	andq	$-128, %r8
	movq	(%r10,%r8,8), %rcx
	addq	$1, %r8
	cmpq	%r8, %rdi
	jl	.L4
	leaq	1(%rdi), %rbx
	movabsq	$-8543223828751151131, %r11
	.p2align 4,,10
	.p2align 3
.L5:
	imulq	%r8, %rcx
	addq	$1, %r8
	movq	%rcx, %rax
	movq	%rcx, %r9
	imulq	%r11
	movq	%r9, %rax
	sarq	$63, %rax
	leaq	(%rdx,%rcx), %rcx
	sarq	$29, %rcx
	subq	%rax, %rcx
	imulq	$1000000007, %rcx, %rcx
	subq	%rcx, %r9
	cmpq	%rbx, %r8
	movq	%r9, %rcx
	jne	.L5
.L4:
	leaq	127(%rsi), %r9
	testq	%rsi, %rsi
	cmovns	%rsi, %r9
	andq	$-128, %r9
	movq	(%r10,%r9,8), %r8
	addq	$1, %r9
	cmpq	%r9, %rsi
	jl	.L6
	leaq	1(%rsi), %rbp
	movabsq	$-8543223828751151131, %rbx
	.p2align 4,,10
	.p2align 3
.L7:
	movq	%r8, %r11
	imulq	%r9, %r11
	addq	$1, %r9
	movq	%r11, %rax
	imulq	%rbx
	movq	%r11, %rax
	sarq	$63, %rax
	leaq	(%rdx,%r11), %r8
	sarq	$29, %r8
	subq	%rax, %r8
	imulq	$1000000007, %r8, %r8
	subq	%r8, %r11
	cmpq	%rbp, %r9
	movq	%r11, %r8
	jne	.L7
.L6:
	subq	%rsi, %rdi
	leaq	127(%rdi), %rsi
	testq	%rdi, %rdi
	cmovns	%rdi, %rsi
	andq	$-128, %rsi
	movq	(%r10,%rsi,8), %rax
	addq	$1, %rsi
	cmpq	%rsi, %rdi
	jl	.L8
	addq	$1, %rdi
	movabsq	$-8543223828751151131, %r10
	.p2align 4,,10
	.p2align 3
.L9:
	imulq	%rsi, %rax
	addq	$1, %rsi
	movq	%rax, %r9
	imulq	%r10
	leaq	(%rdx,%r9), %rax
	movq	%r9, %rdx
	sarq	$63, %rdx
	sarq	$29, %rax
	subq	%rdx, %rax
	imulq	$1000000007, %rax, %rax
	subq	%rax, %r9
	cmpq	%rdi, %rsi
	movq	%r9, %rax
	jne	.L9
.L8:
	imulq	%r8, %rax
	movabsq	$-8543223828751151131, %r10
	movq	%rax, %rsi
	imulq	%r10
	movq	%rsi, %rax
	sarq	$63, %rax
	leaq	(%rdx,%rsi), %r8
	sarq	$29, %r8
	subq	%rax, %r8
	imulq	$1000000007, %r8, %r8
	subq	%r8, %rsi
	movq	%rsi, %r8
	jne	.L24
	movq	%r8, %rax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L24:
	.cfi_restore_state
	movl	$33, %esi
	movabsq	$4294967296, %rdi
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L11:
	sarq	%rdi
	subl	$1, %esi
	je	.L25
.L13:
	imulq	%rdx, %rdx
	movq	%rdx, %rax
	movq	%rdx, %r9
	mulq	%r10
	shrq	$29, %rdx
	imulq	$1000000007, %rdx, %rdx
	subq	%rdx, %r9
	testl	$1000000005, %edi
	movq	%r9, %rdx
	je	.L11
	imulq	%r8, %rdx
	sarq	%rdi
	movq	%rdx, %rax
	movq	%rdx, %r9
	imulq	%r10
	movq	%r9, %rax
	sarq	$63, %rax
	addq	%r9, %rdx
	sarq	$29, %rdx
	subq	%rax, %rdx
	imulq	$1000000007, %rdx, %rdx
	subq	%rdx, %r9
	subl	$1, %esi
	movq	%r9, %rdx
	jne	.L13
.L25:
	imulq	%rdx, %rcx
	movabsq	$-8543223828751151131, %rdx
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	movq	%rcx, %rax
	imulq	%rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	leaq	(%rdx,%rcx), %r8
	sarq	$29, %r8
	subq	%rax, %r8
	imulq	$1000000007, %r8, %r8
	subq	%r8, %rcx
	movq	%rcx, %r8
	movq	%r8, %rax
	ret
	.cfi_endproc
.LFE2125:
	.size	_Z8binomialll.part.3, .-_Z8binomialll.part.3
	.p2align 4,,15
	.globl	_Z11initFactTabv
	.type	_Z11initFactTabv, @function
_Z11initFactTabv:
.LFB1626:
	.cfi_startproc
	leaq	_ZL7factTab(%rip), %r8
	movq	$1, _ZL7factTab(%rip)
	movl	$2, %ecx
	movl	$2, %edx
	movabsq	$-8543223828751151131, %rdi
	.p2align 4,,10
	.p2align 3
.L27:
	addq	$1, %rcx
	cmpq	$500000004, %rcx
	je	.L30
.L29:
	movq	%rdx, %rsi
	imulq	%rcx, %rsi
	movq	%rsi, %rax
	imulq	%rdi
	movq	%rsi, %rax
	sarq	$63, %rax
	addq	%rsi, %rdx
	sarq	$29, %rdx
	subq	%rax, %rdx
	imulq	$1000000007, %rdx, %rdx
	subq	%rdx, %rsi
	testb	$127, %cl
	movq	%rsi, %rdx
	jne	.L27
	movq	%rcx, %rax
	addq	$1, %rcx
	sarq	$7, %rax
	cmpq	$500000004, %rcx
	movq	%rsi, (%r8,%rax,8)
	jne	.L29
.L30:
	rep ret
	.cfi_endproc
.LFE1626:
	.size	_Z11initFactTabv, .-_Z11initFactTabv
	.p2align 4,,15
	.globl	_Z3powll
	.type	_Z3powll, @function
_Z3powll:
.LFB1627:
	.cfi_startproc
	xorl	%eax, %eax
	testq	%rdi, %rdi
	je	.L31
	movl	$33, %r8d
	movl	$1, %eax
	movabsq	$4294967296, %rcx
	movabsq	$-8543223828751151131, %r9
	.p2align 4,,10
	.p2align 3
.L34:
	imulq	%rax, %rax
	movq	%rax, %r10
	imulq	%r9
	leaq	(%rdx,%r10), %rax
	movq	%r10, %rdx
	sarq	$63, %rdx
	sarq	$29, %rax
	subq	%rdx, %rax
	imulq	$1000000007, %rax, %rax
	subq	%rax, %r10
	testq	%rcx, %rsi
	movq	%r10, %rax
	je	.L33
	imulq	%rdi, %rax
	movq	%rax, %r10
	imulq	%r9
	leaq	(%rdx,%r10), %rax
	movq	%r10, %rdx
	sarq	$63, %rdx
	sarq	$29, %rax
	subq	%rdx, %rax
	imulq	$1000000007, %rax, %rax
	subq	%rax, %r10
	movq	%r10, %rax
.L33:
	sarq	%rcx
	subl	$1, %r8d
	jne	.L34
.L31:
	rep ret
	.cfi_endproc
.LFE1627:
	.size	_Z3powll, .-_Z3powll
	.p2align 4,,15
	.globl	_Z3invl
	.type	_Z3invl, @function
_Z3invl:
.LFB1628:
	.cfi_startproc
	testq	%rdi, %rdi
	jne	.L52
	movq	%rdi, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L52:
	movl	$33, %ecx
	movabsq	$4294967296, %rsi
	movl	$1, %edx
	movabsq	$-8543223828751151131, %r9
	.p2align 4,,10
	.p2align 3
.L43:
	sarq	%rsi
	subl	$1, %ecx
	je	.L53
.L45:
	imulq	%rdx, %rdx
	movq	%rdx, %rax
	movq	%rdx, %r8
	mulq	%r9
	shrq	$29, %rdx
	imulq	$1000000007, %rdx, %rdx
	subq	%rdx, %r8
	testl	$1000000005, %esi
	movq	%r8, %rdx
	je	.L43
	imulq	%rdi, %rdx
	sarq	%rsi
	movq	%rdx, %rax
	movq	%rdx, %r8
	imulq	%r9
	movq	%r8, %rax
	sarq	$63, %rax
	addq	%r8, %rdx
	sarq	$29, %rdx
	subq	%rax, %rdx
	imulq	$1000000007, %rdx, %rdx
	subq	%rdx, %r8
	subl	$1, %ecx
	movq	%r8, %rdx
	jne	.L45
.L53:
	movq	%rdx, %rdi
	movq	%rdi, %rax
	ret
	.cfi_endproc
.LFE1628:
	.size	_Z3invl, .-_Z3invl
	.p2align 4,,15
	.globl	_Z9factoriall
	.type	_Z9factoriall, @function
_Z9factoriall:
.LFB1629:
	.cfi_startproc
	leaq	127(%rdi), %rcx
	testq	%rdi, %rdi
	leaq	_ZL7factTab(%rip), %rax
	cmovns	%rdi, %rcx
	andq	$-128, %rcx
	movq	(%rax,%rcx,8), %rax
	addq	$1, %rcx
	cmpq	%rcx, %rdi
	jl	.L54
	addq	$1, %rdi
	movabsq	$-8543223828751151131, %r8
	.p2align 4,,10
	.p2align 3
.L56:
	imulq	%rcx, %rax
	addq	$1, %rcx
	movq	%rax, %rsi
	imulq	%r8
	leaq	(%rdx,%rsi), %rax
	movq	%rsi, %rdx
	sarq	$63, %rdx
	sarq	$29, %rax
	subq	%rdx, %rax
	imulq	$1000000007, %rax, %rax
	subq	%rax, %rsi
	cmpq	%rcx, %rdi
	movq	%rsi, %rax
	jne	.L56
.L54:
	rep ret
	.cfi_endproc
.LFE1629:
	.size	_Z9factoriall, .-_Z9factoriall
	.p2align 4,,15
	.globl	_Z8binomialll
	.type	_Z8binomialll, @function
_Z8binomialll:
.LFB1630:
	.cfi_startproc
	testq	%rsi, %rsi
	js	.L59
	jmp	_Z8binomialll.part.3
	.p2align 4,,10
	.p2align 3
.L59:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE1630:
	.size	_Z8binomialll, .-_Z8binomialll
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB1631:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	leaq	_ZL7factTab(%rip), %r8
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movl	$2, %ecx
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movl	$2, %edx
	movabsq	$-8543223828751151131, %rdi
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	$1, _ZL7factTab(%rip)
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L61:
	addq	$1, %rcx
	cmpq	$500000004, %rcx
	je	.L90
.L63:
	movq	%rdx, %rsi
	imulq	%rcx, %rsi
	movq	%rsi, %rax
	imulq	%rdi
	movq	%rsi, %rax
	sarq	$63, %rax
	addq	%rsi, %rdx
	sarq	$29, %rdx
	subq	%rax, %rdx
	imulq	$1000000007, %rdx, %rdx
	subq	%rdx, %rsi
	testb	$127, %cl
	movq	%rsi, %rdx
	jne	.L61
	movq	%rcx, %rax
	addq	$1, %rcx
	sarq	$7, %rax
	cmpq	$500000004, %rcx
	movq	%rsi, (%r8,%rax,8)
	jne	.L63
.L90:
	leaq	44(%rsp), %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
	movl	44(%rsp), %eax
	testl	%eax, %eax
	jle	.L64
	leaq	48(%rsp), %rax
	leaq	_ZL7factTab(%rip), %rbp
	movl	$1, %ebx
	movabsq	$-8543223828751151131, %r15
	movq	%rax, 16(%rsp)
	.p2align 4,,10
	.p2align 3
.L78:
	movq	16(%rsp), %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSi10_M_extractIlEERSiRT_@PLT
	movq	48(%rsp), %r12
	testq	%r12, %r12
	movq	%r12, %rcx
	jle	.L80
	movl	$1, %r14d
	.p2align 4,,10
	.p2align 3
.L66:
	subq	%r14, %rcx
	addq	%r14, %r14
	cmpq	%r14, %rcx
	jge	.L66
	movq	%r12, %rax
	sarq	%r14
	subq	%rcx, %rax
.L65:
	movq	%rcx, %rsi
	movq	%rcx, %rdx
	xorl	%r10d, %r10d
	sarq	%rsi
	movq	%rax, 48(%rsp)
	subq	%rsi, %rdx
	testq	%rsi, %rsi
	js	.L67
	movq	%r14, %rdi
	movq	%rdx, 24(%rsp)
	movq	%rcx, 8(%rsp)
	call	_Z8binomialll.part.3
	movq	24(%rsp), %rdx
	movq	8(%rsp), %rcx
	movq	%rax, %r10
.L67:
	xorl	%r13d, %r13d
	testq	%rdx, %rdx
	movq	%r10, 8(%rsp)
	js	.L68
	movq	%rdx, %rsi
	movq	%r14, %rdi
	movq	%rcx, 24(%rsp)
	call	_Z8binomialll.part.3
	movq	8(%rsp), %r10
	movq	24(%rsp), %rcx
	imulq	%r10, %rax
	movq	%rax, %rdi
	imulq	%r15
	movq	%rdi, %rax
	sarq	$63, %rax
	leaq	(%rdx,%rdi), %r8
	sarq	$29, %r8
	subq	%rax, %r8
	imulq	$1000000007, %r8, %r8
	subq	%r8, %rdi
	movq	%rdi, %r13
.L68:
	leaq	-1(%rcx), %rdx
	xorl	%r10d, %r10d
	sarq	%rdx
	subq	%rdx, %rcx
	js	.L69
	movq	%rcx, %rsi
	movq	%r14, %rdi
	movq	%rdx, 8(%rsp)
	call	_Z8binomialll.part.3
	movq	8(%rsp), %rdx
	movq	%rax, %r10
.L69:
	testq	%rdx, %rdx
	movq	%r10, 8(%rsp)
	js	.L70
	movq	%rdx, %rsi
	movq	%r14, %rdi
	call	_Z8binomialll.part.3
	movq	8(%rsp), %r10
	imulq	%r10, %rax
	movq	%rax, %rcx
	imulq	%r15
	leaq	(%rdx,%rcx), %rax
	movq	%rcx, %rdx
	sarq	$63, %rdx
	sarq	$29, %rax
	subq	%rdx, %rax
	imulq	$1000000007, %rax, %rax
	subq	%rax, %rcx
	addq	%r13, %rcx
	movq	%rcx, %rax
	imulq	%r15
	movq	%rcx, %rax
	sarq	$63, %rax
	leaq	(%rdx,%rcx), %r8
	sarq	$29, %r8
	subq	%rax, %r8
	imulq	$1000000007, %r8, %r8
	subq	%r8, %rcx
	movq	%rcx, %r13
.L70:
	movq	%r12, %r10
	sarq	%r10
	leaq	127(%r10), %rsi
	testq	%r10, %r10
	cmovns	%r10, %rsi
	andq	$-128, %rsi
	movq	0(%rbp,%rsi,8), %rcx
	addq	$1, %rsi
	cmpq	%rsi, %r10
	jl	.L71
	leaq	1(%r10), %r11
	.p2align 4,,10
	.p2align 3
.L72:
	movq	%rcx, %rdi
	imulq	%rsi, %rdi
	addq	$1, %rsi
	movq	%rdi, %rax
	imulq	%r15
	movq	%rdi, %rax
	sarq	$63, %rax
	leaq	(%rdx,%rdi), %rcx
	sarq	$29, %rcx
	subq	%rax, %rcx
	imulq	$1000000007, %rcx, %rcx
	subq	%rcx, %rdi
	cmpq	%r11, %rsi
	movq	%rdi, %rcx
	jne	.L72
.L71:
	movq	%r12, %r9
	subq	%r10, %r9
	leaq	127(%r9), %rsi
	testq	%r9, %r9
	cmovns	%r9, %rsi
	andq	$-128, %rsi
	movq	0(%rbp,%rsi,8), %rdx
	addq	$1, %rsi
	cmpq	%rsi, %r9
	jl	.L73
	addq	$1, %r9
	.p2align 4,,10
	.p2align 3
.L74:
	movq	%rdx, %rdi
	imulq	%rsi, %rdi
	addq	$1, %rsi
	movq	%rdi, %rax
	imulq	%r15
	movq	%rdi, %rax
	sarq	$63, %rax
	addq	%rdi, %rdx
	sarq	$29, %rdx
	subq	%rax, %rdx
	imulq	$1000000007, %rdx, %rdx
	subq	%rdx, %rdi
	cmpq	%r9, %rsi
	movq	%rdi, %rdx
	jne	.L74
.L73:
	imulq	%rdx, %rcx
	leaq	_ZSt4cout(%rip), %rdi
	movq	%rcx, %rax
	imulq	%r15
	leaq	(%rdx,%rcx), %rax
	movq	%rcx, %rdx
	sarq	$63, %rdx
	sarq	$29, %rax
	subq	%rdx, %rax
	imulq	$1000000007, %rax, %rax
	subq	%rax, %rcx
	imulq	%r13, %rcx
	movq	%rcx, %rax
	movq	%rcx, %rsi
	imulq	%r15
	leaq	(%rdx,%rcx), %rax
	movq	%rcx, %rdx
	sarq	$63, %rdx
	sarq	$29, %rax
	subq	%rdx, %rax
	imulq	$1000000007, %rax, %rax
	subq	%rax, %rsi
	call	_ZNSo9_M_insertIlEERSoT_@PLT
	movq	%rax, %r13
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r13,%rax), %r14
	testq	%r14, %r14
	je	.L91
	cmpb	$0, 56(%r14)
	je	.L76
	movsbl	67(%r14), %esi
.L77:
	movq	%r13, %rdi
	addl	$1, %ebx
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	cmpl	%ebx, 44(%rsp)
	jge	.L78
.L64:
	xorl	%eax, %eax
	movq	56(%rsp), %rbx
	xorq	%fs:40, %rbx
	jne	.L92
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L76:
	.cfi_restore_state
	movq	%r14, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%r14), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdi
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%rdi, %rax
	je	.L77
	movq	%r14, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L77
.L80:
	xorl	%r14d, %r14d
	xorl	%eax, %eax
	jmp	.L65
.L92:
	call	__stack_chk_fail@PLT
.L91:
	call	_ZSt16__throw_bad_castv@PLT
	.cfi_endproc
.LFE1631:
	.size	main, .-main
	.p2align 4,,15
	.type	_GLOBAL__sub_I__Z11initFactTabv, @function
_GLOBAL__sub_I__Z11initFactTabv:
.LFB2121:
	.cfi_startproc
	leaq	_ZStL8__ioinit(%rip), %rdi
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	_ZNSt8ios_base4InitC1Ev@PLT
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZStL8__ioinit(%rip), %rsi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit@PLT
	.cfi_endproc
.LFE2121:
	.size	_GLOBAL__sub_I__Z11initFactTabv, .-_GLOBAL__sub_I__Z11initFactTabv
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z11initFactTabv
	.local	_ZL7factTab
	.comm	_ZL7factTab,31250000,32
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
