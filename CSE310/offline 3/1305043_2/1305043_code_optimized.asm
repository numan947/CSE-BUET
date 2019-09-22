TITLE PROGRAM:numan947
.model small
.stack 100h
.data
a dw ? ,?
c dw ?
i dw ?
j dw ?
d dw ?
t0 dw ?
t1 dw ?
t2 dw ?
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
mov ax, 1
lea di, a
mov [di], ax
mov ax, 5
lea di, a
add di, 1
add di, 1
mov [di], ax
mov ax, 0
mov i, ax
L6:
mov ax, i
cmp ax, 2
jl L0
mov t0, 0
jmp L1
L0:
mov t0, 1
L1:
cmp t0, 0
je L7
mov ax, i
cmp ax, 0
je L2
mov t2, 0
jmp L3
L2:
mov t2, 1
L3:
mov ax, t2
cmp ax, 0
je L4
mov ax, 8
lea di, a
mov [di], ax
jmp L5
L4:
mov ax, 7
lea di, a
add di, 1
add di, 1
mov [di], ax
L5:
mov ax, i
add ax, 1
mov t1, ax
mov i, ax
jmp L6
L7:
lea di, a
mov bx, 2
L8:
cmp bx, 0
je L9
mov ax, [di]
call outdec
dec bx
inc di
inc di
mov ah,2
mov dl,0ah
int 21h
mov dl,0dh
int 21h
jmp L8
L9:
mov ah, 4ch
int 21h

main endp

end main