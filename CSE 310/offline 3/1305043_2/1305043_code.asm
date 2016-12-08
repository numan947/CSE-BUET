a dw ? ,?
c dw ?
i dw ?
j dw ?
d dw ?
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
lea di, a
add di, 0
add di, 0
mov t0, [di]
lea di, a
add di, 1
add di, 1
mov t1, [di]
mov ax, t0
add ax, t1mov t2, ax
mov ax, t2
mov i, ax
mov ah, 4ch
int 21h
