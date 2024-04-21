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
	Lit10	DW	10
	Lit1	DW	1


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
W1:	mov	ax,[J]
	cmp	ax,[10]
	JGE	L1
	mov	ax,[J]
	add	ax,[1]
	mov	[Temp1],ax
	mov	ax,[Temp1]
	mov	[J],ax
L1:	NOP
