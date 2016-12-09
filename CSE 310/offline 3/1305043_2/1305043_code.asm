TITLE PROGRAM:numan947
.model small
.stack 100h

.data

a dw ? ,? ,?
i dw ?
t0 dw ?
t1 dw ?
t2 dw ?

.code

main proc

mov ax ,@data
mov ds ,ax
mov ax, 1
mov bx, 2
mul bx
mov t0, ax
lea di, a
add di, t0
add di, t0
mov t1, [di]
mov ax, i
mov bx, t1
mul bx
mov t2, ax
mov ax, t2
lea di, a
add di, 1
add di, 1
mov [di], ax
lea di, a
add di, 0
add di, 0
mov ax, [di]
call outdec
lea di, a
add di, 1
add di, 1
mov ax, [di]
call outdec
lea di, a
add di, 2
add di, 2
mov ax, [di]
call outdec

main endp

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

end main