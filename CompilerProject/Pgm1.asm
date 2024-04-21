sys_exit	eque	1
sys_read	eque	3
sys_write	eque	4
stdin		eque	0
stdout		eque	1


section.data
	userMsg	db	"Enter a integer:(lesst than 32,765):'
	lenUserMsgequ	$-userMsg
	displayMsg	db	'You entered: '
	lenDisplayMsg	equ	$-displayMsg
	newline	db	0xA
	Ten	DW	10
	printTempchar	db	'Tempchar = :'
	lenPrintTempchar	equ	$-printTempchar
	Result	db	'Ans='
	ResultValue	db'aaaaa'
			db	0xA
	ResultEnd	equ	$-Result'
	num	times 6 db'ABCDEF'
	numEnd		equ	$-num
	M		DW	7
	N		DW	85
	Lit12	DW	12


section	.bss
	TempChar	RESB	1
	testchar	RESB	1
	ReadInt		RESW	1
	tempint		RESW	1
	negflag		RESB	1
	X		RESW	1
	Y		RESW	1
	Z		RESW	1
	Temp1		RESW	1
	Temp2		RESW	1
	Temp3		RESW	1


	global_start

section.text

_start:		nop
Again:	call PrintString
	call GetAnInteger
	mov	ax,[ReadInt]
	mov	[Y],ax
	call PrintString
	call GetAnInteger
	mov	ax,[ReadInt]
	mov	[Z],ax
	mov	ax,[Y]
	mul	[Z]
	mov	[Temp1],ax
	mov	ax,[M]
	add	ax,[Temp1]
	mov	[Temp2],ax
	mov	ax,[Temp2]
	add	ax,[12]
	mov	[Temp3],ax
	mov	ax,[Temp3]
	mov	[X],ax
	mov	ax,[X]
	call	ConvertIntegerToString
	mov	eax,4
	mov	ebx,1
	mov	ecx,Result
	mov	edx,ResultEnd
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
<If>
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
	dec	ebx
	cmp	ebx,ResultValue
	jge	ConvertLoop
	ret


fini:
	mov	eax,sys_exit
	xor	ebx,ebx
	int	80h
