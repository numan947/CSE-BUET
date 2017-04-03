;S.MAHMDUL HASAN (NUMAN) 1305043
.MODEL SMALL
.STACK 100h
.DATA
    dig1 db 0
    dig0 db 0
    num db ?
    sum dw 0
    cnt dw 0
    msg1 db 'Enter value of n: $'
    msg2 db 'Summation of the series is: $'
    
    ans db 0,0,0,0

.CODE

main proc
    
    mov ax,@DATA
    mov ds,ax 
    mov ah,9
    LEA dx,msg1
    int 21h
    
    mov ah,1
    int 21h
    
    mov dig1,al
    add dig1,-48
    
    int 21h
    mov dig0,al
    add dig0,-48
    
    ;//////creating number from input//////
    mov cx,10
    mov bl,0
    
    FACTOR:
       add bl,dig1        
    loop FACTOR
    
    add bl,dig0
    
    mov num,bl
    ;//////number creation done/////////////
    
    ;/////calculating sum////////// 
    cmp num,0
    je PRINT
    
    mov cl,num
    mov bx,1
    mov sum,0
    
    CALC_SUM:
        add sum,bx
        add bx,bx
    loop CALC_SUM
    ;////////////sum calculation done/////////////
    
    ;//////getting digits from msb to lsb
    
    ;3rd pos
    mov cnt,0
        
    WHILE3:
        cmp sum,1000
        JL d3
        inc cnt 
        add sum,-1000
        
        cmp cnt,10
        JL WHILE3
        add cnt,-10
        jmp WHILE3    
    d3:
        mov bx,cnt
        mov ans+3,bl   
    
    ;2nd pos
    mov cnt,0
    
    WHILE2:
        cmp sum,100
        JL d2
        inc cnt 
        add sum,-100
        jmp WHILE2    
    d2:
        mov bx,cnt
        mov ans+2,bl 
    
    ;1st pos
    mov cnt,0
    
    WHILE1:
        cmp sum,10
        JL d1
        inc cnt 
        add sum,-10
        jmp WHILE1    
    d1:
        mov bx,cnt
        mov ans+1,bl 
          
    ;0th pos
     mov bx,sum
     mov ans,bl 
   
   ;////printing digits/////
    
    PRINT:
    mov ah,2
    mov dl,0ah
    int 21h
    mov dl,0dh
    int 21h
    
    
    mov ah,9
    LEA dx,msg2
    int 21h
    
    mov ah,2
    mov dl,ans+3
    add dl,48
    int 21h
    
    mov dl,ans+2
    add dl,48
    int 21h
    
    mov dl,ans+1
    add dl,48
    int 21h
    
    mov dl,ans
    add dl,48
    int 21h

    mov ah,4ch
    int 21h

main endp