.MODEL SMALL
.STACK 100h
.DATA
    dig1 db 0
    dig0 db 0
    num db ?
    tmp db ?
    sum dw 0
    cnt dw 0
    
    ans db 0,0,0,0

.CODE


main proc
    mov ah,1
    int 21h

    
    mov dig1,al
    add dig1,-48
    
    
    int 21h
    mov dig0,al
    
    
    ;/////////////
    mov ah,2
    mov dl,0ah
    int 21h
    mov dl,0dh
    int 21h

    mov dl,tmp
    int 21h
    
    ;//////////////
    
    
    ;//////creating number from input//////
    mov cx,10
    mov bl,0
    
    FACTOR:
    
        add bl,dig1        
    
    loop FACTOR
    
    add bl,dig0
    add bl,-48
    mov num,bl
    ;//////creating done/////////////
    
    ;/////calculating sum//////////
    
    mov cl,num
    mov bx,1
    mov sum,0
    
    CALC_SUM:
        add sum,bx
        add bx,bx
    loop CALC_SUM
    ;////////////calculation done/////////////
    
    
    ;0th pos
    mov bx,sum
    mov cnt,0
    
    WHILE0:
        cmp bx,10
        JL d0
        inc cnt 
        add bx,-10
        jmp WHILE0    
    d0:
        mov ans,bl
        ;jmp PRINT
        mov bx,cnt
        mov sum,bx
        
    
    ;1st pos
    mov bx,sum
    mov cnt,0
    
    WHILE1:
        cmp bx,10
        JL d1
        inc cnt 
        add bx,-10
        jmp WHILE1    
    d1:
        mov ans+1,bl
        ;jmp PRINT
        mov bx,cnt
        mov sum,bx 
        
    
    ;2nd pos
    mov bx,sum
    mov cnt,0
    
    WHILE2:
        cmp bx,10
        JL d2
        inc cnt 
        add bx,-10
        jmp WHILE2    
    d2:
        mov ans+2,bl
        ;jmp PRINT
        mov bx,cnt
        mov sum,bx 
        
        
    ;3rd pos
    
    mov bx,sum
    mov cnt,0
    
    WHILE3:
        cmp bx,10
        JL d3
        inc cnt 
        add bx,-10
        jmp WHILE3    
    d3:
        mov ans,bl
        ;jmp PRINT
        mov bx,cnt
        mov sum,bx     
    
    
    
    
    
    
    

    mov ah,2
    mov dl,0ah
    int 21h
    mov dl,0dh
    int 21h
    
    PRINT:
        

    mov dl,ans
    add dl,48
    int 21h
   ; mov dl,dig0
   ; int 21h

    mov ah,4ch
    int 21h




main endp
