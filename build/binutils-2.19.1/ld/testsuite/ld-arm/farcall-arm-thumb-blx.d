.*:     file format .*

Disassembly of section .text:

00001000 <__bar_from_arm>:
    1000:	e51ff004 	ldr	pc, \[pc, #-4\]	; 1004 <__bar_from_arm\+0x4>
    1004:	02001015 	.word	0x02001015

00001008 <_start>:
    1008:	ebfffffc 	bl	1000 <__bar_from_arm>
Disassembly of section .foo:

02001014 <bar>:
 2001014:	4770      	bx	lr
