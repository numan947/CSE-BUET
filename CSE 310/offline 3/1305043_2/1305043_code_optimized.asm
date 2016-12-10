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
t3 dw ?
t4 dw ?
t5 dw ?
t6 dw ?
t7 dw ?
t8 dw ?
.code
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
lea di, a
mov ax, [di]
mov t0, ax
lea di, a
add di, 1
add di, 1
mov ax, [di]
mov t1, ax
mov ax, t0
add ax, t1
mov t2, ax
mov i, ax
mov ax, 2
mov bx, 3
mul bx
mov t3, ax
mov ax, 5
mov bx, 3
xor dx, dx
div bx
mov t4, dx
mov ax, t4
cmp ax, 4
jl L0
mov t5, 0
jmp L1
L0:
mov t5, 1
L1:
mov ax, t5
cmp ax, 1
jne L2
mov ax, 8
cmp ax, 1
jne L2
mov t6, 1
jmp L3
L2:
mov t6, 0
L3:
mov ax, t3
add ax, t6
mov t7, ax
cmp ax, 1
je L4
mov ax, 2
cmp ax, 1
je L4
mov t8, 0
jmp L5
L4:
mov t8, 1
L5:
mov ax, t8
mov j, ax
lea di, a
inc [di]
mov ah, 4ch
int 21h

main endp

end main