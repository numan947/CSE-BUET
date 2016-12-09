TITLE PROGRAM:numan947
.model small
.stack 100h

.data

a dw ? ,? ,?
i dw ?

.code

OUTDEC PROC
;INPUT AX
PUSH AX
PUSH BX
PUSH CX
PUSH DX
OR AX,AX
JGE @END_IF1
PUSH AX
MOV DL,'-'
MOV AH,2
INT 21H
POP AX
NEG AX

@END_IF1:
XOR CX,CX
MOV BX,10D

@REPEAT1:
XOR DX,DX
DIV BX
PUSH DX
INC CX
OR AX,AX
JNE @REPEAT1

MOV AH,2

@PRINT_LOOP:

POP DX
OR DL,30H
INT 21H
LOOP @PRINT_LOOP

POP DX
POP CX
POP BX
POP AX
RET
OUTDEC ENDP

main proc

mov ax ,@data
mov ds ,ax
mov ax, 5
mov i, ax
mov ax, i
call outdec
mov ah, 4ch
int 21h

main endp

end main