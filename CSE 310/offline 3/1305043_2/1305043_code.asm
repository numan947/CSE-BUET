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
 mov ah, 4ch
int 21h

main endp
end main
