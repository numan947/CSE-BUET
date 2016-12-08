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
t9 dw ?

.code

main proc

mov ax ,@data
mov ds ,ax
mov ax, 1
lea di, a
add di, 0
add di, 0
mov [di], ax
mov ax, 5
lea di, a
add di, 1
add di, 1
mov [di], ax
mov ax, i
mov bx, 9
mul bx
mov t0, ax
lea di, a
add di, t0
add di, t0
mov t1, [di]
lea di, a
add di, 1
add di, 1
mov t2, [di]
mov ax, t1
add ax, t2
mov t3, ax
mov ax, t3
mov i, ax
mov ax, 2
mov bx, 3
mul bx
mov t4, ax
mov ax, 5
mov bx, 3
xor dx, dx
div bx
mov t5, dx
mov ax, t5
cmp ax, 4
jl L0
mov t6, 0
jmp L1
L0:
mov t6, 1
L1:
cmp t6,1
jne L2
cmp 8,1
jne L2
mov t7, 1
jmp L3
L2:
mov t7, 0
L3:
mov ax, t4
add ax, t7
mov t8, ax
cmp t8,1
je L4
cmp 2,1
je L4
mov t9, 0
jmp L5
L4:
mov t9, 1
L5:
mov ax, t9
mov j, ax
mov ah, 4ch
int 21h

main endp
end main
