;S.MAHMDUL HASAN (NUMAN) 1305043 

.model small
.stack 100h

.DATA               
    num dw 0
    flag db 0
    
    n1 dw 0
    n2 dw 0

    cyc  dw 0
    max_cyc dw 0
    
    temp dw 0
    divisor dw 0
  
    
    
.CODE


main proc
    
    mov ax, @data
    mov ds, ax
        
    ;check if greater than 10000
INPUT:   
    mov n1,0
    mov n2,0
    mov flag,0
    mov max_cyc,0
    
    input1:
        mov ah,1
        int 21h
        add al,-48
        cmp al,0
        jl input2
        cmp al,9
        jg input2
        mov bl,al
        
        mov ax,10
        IMUL n1
        mov n1,ax
        add n1,bx
        jmp input1 
    
    input2:
        mov ah,1
        int 21h
        add al,-48
        cmp al,0
        jl inputend
        cmp al,9
        jg inputend
        mov bl,al
        
        mov ax,10
        IMUL n2
        mov n2,ax
        add n2,bx
        jmp input2   
   inputend:
    
   
   ;swap if necessary
   
   
   
   ;while n1<=n2
   
    WHILE:
        mov bx,n2
        cmp n1,bx
        jg break
        
        mov bx,n1
        mov temp,bx
        mov cyc,0
        
        
        WHILE_INNER:
            cmp temp,1
            je break_inner
            inc cyc
            
            test temp,1
            jz ins2
            
            ins1:
                mov ax,3
                imul temp
                mov temp,ax
                inc temp
                jmp WHILE_INNER
            ins2:
                mov ax,temp
                mov bx,2
                mov dx,0
                Idiv bx
                mov temp,ax
                jmp WHILE_INNER
                
        break_inner:
        inc n1
        inc cyc
        
        
        
        mov bx,cyc
        cmp max_cyc,bx
        jg WHILE 
        
        swap:
           mov max_cyc,bx 
        jmp WHILE
           
      break:
            mov ah,2
            mov dl,0ah
            int 21h
            mov dl,0dh
            int 21h
    
      
      
      mov bx,max_cyc
      mov num,bx

    
dig5:    
    cmp num,10000
    jl dig4
    
    mov divisor,10000
    mov ax,num
    mov dx,0
    idiv divisor
    mov num,dx
    
    mov ah,2
    mov dl,al
    add dl,48d
    int 21h
    mov flag,1
    
    jmp dig4
    
    
dig4:    
    
    cmp flag,1
    je process4
    cmp num,1000
    jl dig3 
    
    process4:
    mov divisor,1000
    mov ax,num
    mov dx,0
    idiv divisor
    mov num,dx
    
    mov ah,2
    mov dl,al
    add dl,48d
    int 21h
    mov flag,1
    
    jmp dig3
    

dig3:    
    cmp flag,1
    je process3
    cmp num,100
    jl dig2
    
    
    process3:
    mov divisor,100
    mov ax,num
    mov dx,0
    idiv divisor
    mov num,dx
    
    mov ah,2
    mov dl,al
    add dl,48d
    int 21h
    mov flag,1
    
    jmp dig2
    
    
dig2:    
    cmp flag,1
    je process2
    cmp num,10
    jl dig1
   
    process2:
    mov divisor,10
    mov ax,num
    mov dx,0
    idiv divisor
    mov num,dx
    
    mov ah,2
    mov dl,al
    add dl,48d
    int 21h
    mov flag,1
    
    jmp dig1
    
    
dig1:    
    process1:
    mov divisor,1
    mov ax,num
    mov dx,0
    idiv divisor
    mov num,dx
    
    mov ah,2
    mov dl,al
    add dl,48d
    int 21h
    mov flag,1
END:
    mov ah,2
    mov dl,0ah
    int 21h
    mov dl,0dh
    int 21h
    jmp INPUT
    
main endp