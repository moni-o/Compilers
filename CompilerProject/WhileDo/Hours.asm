sys_exit	equ	1
sys_read	equ	3
sys_write	equ	4
stdin		equ	0
stdout		equ	1


section	.data
	userMsg	db	'Enter a integer:(less than 32,765):'
	lenUserMsg	equ	$	-	userMsg
	displayMsg	db	'You entered: '
	lenDisplayMsg	equ	$-displayMsg
	newline	db	0xA
	Ten	DW	10
	printTempchar	db	'Tempchar = :'
	lenPrintTempchar	equ	$-printTempchar
	Result	db	'Ans='
	ResultValue	db'aaaaa'
			db	0xA
	ResultEnd	equ	$-Result
	num	times 6 db'ABCDEF'
	numEnd		equ	$-num
	Lit1	DW	1
	Lit0	DW	0
	Lit7	DW	7
	Lit24	DW	24


section	.bss
	TempChar	RESB	1
	testchar	RESB	1
	ReadInt		RESW	1
	tempint		RESW	1
	negflag		RESB	1
	WEEKS		RESW	1
	HOURS		RESW	1
	WEEKCOUNT		RESW	1
	DAY		RESW	1
	Temp1		RESW	1
	Temp2		RESW	1
	Temp3		RESW	1
	Temp4		RESW	1
	Temp5		RESW	1
	Temp6		RESW	1
	Temp7		RESW	1


	global	_start

section	.text

_start:		nop
Again:	call PrintString
	call GetAnInteger
	mov	ax,[ReadInt]
	mov	[WEEKS],ax
	mov	ax,[Lit1]
	mov	[WEEKCOUNT],ax
	mov	ax,[Lit0]
	mov	[HOURS],ax
W1:	mov	ax,[WEEKCOUNT]
	cmp	ax,[WEEKS]
	JG	L1
	mov	ax,[Lit1]
	mov	[DAY],ax
W2:	mov	ax,[DAY]
	cmp	ax,[Lit7]
	JG	L2
	mov	ax,[HOURS]
	add	ax,[Lit24]
	mov	[Temp1],ax
	mov	ax,[Temp1]
	mov	[HOURS],ax
	mov	ax,[DAY]
	add	ax,[Lit1]
	mov	[Temp1],ax
	mov	ax,[Temp1]
	mov	[DAY],ax
	JMP	W2
L2:	NOP
	mov	ax,[WEEKCOUNT]
	add	ax,[Lit1]
	mov	[Temp1],ax
	mov	ax,[Temp1]
	mov	[WEEKCOUNT],ax
	JMP	W1
L1:	NOP
	mov	ax,[HOURS]
	call	ConvertIntegerToString
	mov	eax,4
	mov	ebx,1
	mov	ecx,Result
	mov	edx,ResultEnd
	int	80h


fini:
	mov	eax,sys_exit
	xor	ebx,ebx
	int	80h
PrintString:
	push	ax
	push	dx
	mov	eax,4
	mov	ebx,1
	mov	ecx,userMsg
	mov	edx,lenUserMsg
	int	80h
	pop	dx
	pop	ax
	ret


GetAnInteger:
	mov	eax,3
	mov	ebx,2
	mov	ecx,num
	mov	edx,6
	int	0x80
	mov	edx,eax
	mov	eax,4
	mov	ebx,1
	int 80h
ConvertStringToInteger:
	mov	ax,0
	mov[ReadInt],ax
	mov	ecx,num
	mov	bx,0
	mov	bl,byte[ecx]
Next:	sub	bl,'0'
	mov	ax,[ReadInt]
	mov	dx,10
	mul	dx
	add	ax,bx
	mov	[ReadInt],ax
	mov	bx,0
	add	ecx,1
	mov	bl,byte[ecx]
	cmp	bl,0XA
	jne	Next
	ret


ConvertIntegerToString:
	mov	ebx,ResultValue + 4
ConvertLoop:
	sub	dx,dx
	mov	cx,10
	div	cx
	add	dl,'0'
	mov [ebx], dl
	dec	ebx
	cmp	ebx,ResultValue
	jge	ConvertLoop
	ret
