;Prepared by S.Mahmudul Hasan (Numan)
;------------1305043
;------------Sec: A1
.MODEL SMALL
.STACK 100h
.DATA
    divisor DW 0
    num DW 0
    cnt DW 0
    n1 DW 0
    n2 DW 0
    msg1 db 'Yes$'
    msg2 db 'No$'
    

.CODE

main proc
    mov ax,@data
    mov ds,ax
    
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
   
   mov ah,2
   mov dl,0ah
   int 21h   ;giving new line
   mov dl,0dh
   int 21h
   
   
   mov ax,n1 ;for generating number
   mov bx,n2
   
       
    ;let the two numbers be in ax and bx
    
    push ax
    push bx
    
    call gen_number     ;ax stores the number generated in gen_number
    
    mov num,ax          ;for printing purpose of the generated number
    call print_num
    
    call get_unit       ;get_unit asssumes that the number's in AX and returns the value in dx
        
    cmp dx,0
    je YES
    
    NO:
        mov dl,32
        mov ah,2 ;giving the space
        int 21h
        
        lea dx,msg2
        mov ah,9
        int 21h
        jmp LAST 
    
    YES:   
        mov dl,32
        mov ah,2 ;giving the space
        int 21h
        
        lea dx,msg1
        mov ah,9
        int 21h    
    
    
    LAST:   
    mov ah,4ch
    int 21h
     
    main endp








;returns result in dx
get_unit proc
    
    push bx
    push ax
    
    mov dx,0
    mov bx,10
    
    idiv bx     ;now dx contains the remainder aka the unit's value  
    
    
    pop ax      ;restoring ax
    pop bx      ;restoring bx
    
        
    ret
    get_unit endp
               
               
               
                              
;the generated number will be in ax
gen_number proc
    
    push bp
    mov bp,sp
    
    ;if a<=1
    cmp word ptr[bp+6],1
    jle CASE1
    
    ;if b<=2
    cmp word ptr[bp+4],2
    jle CASE2
    
    ;recursive case
    jmp ELSE
    
    CASE1:
        mov ax,2
        jmp RETURN
    
    CASE2:
        mov ax,3
        jmp RETURN
         
    
    ELSE:
        ;compute (a-1,b)
        mov cx,[bp+6]
        dec cx
        push cx
        push [bp+4]
        call gen_number
        push ax
        
        ;compute (a,b-1)
        mov cx,[bp+4]
        dec cx
        push [bp+6]
        push cx
        call gen_number 
        
        
        pop bx
        add ax,bx
    
    RETURN:
        pop bp
        RET 4
    gen_number endp
    




;the number is in num
print_num proc
    push ax
    
    ;special case 0-9
    cmp num,10
    jle SPECIAL
    
    
    mov cnt,0    
    WHILE:
        cmp num,0
        jle PRINT
        
        
        mov divisor,10
        mov ax,num
        mov dx,0
        idiv divisor
        mov num,ax
        PUSH dx
        inc cnt  
        jmp WHILE
   
   
   PRINT:
        cmp cnt,0
        je RETURN1
        
        dec cnt
        pop ax
        mov dx,ax
        add dl,48
        mov ah,2
        int 21h     
        jmp PRINT
        
    SPECIAL:  
        mov dx,num
        add dl,48
        mov ah,2
        int 21h  
        
    RETURN1:
        pop ax
        RET
    print_num endp

end main

    