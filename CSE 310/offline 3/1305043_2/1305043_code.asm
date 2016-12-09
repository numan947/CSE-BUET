TITLE PROGRAM:numan947
.model small
.stack 100h

.data

a dw ? ,? ,?
i dw ?
t0 dw ?
t1 dw ?
t2 dw ?
t3 dw ?

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
mov ax, i
cmp ax, 2
jl L0
mov t3, 0
jmp L1
L0:
mov t3, 1
L1:
mov ax, t3
cmp ax, 1
jne L2
mov ax, 5
lea di, a
add di, 2
add di, 2
mov [di], ax
L2:
mov ax, 7
mov i, ax

main endp
end main
