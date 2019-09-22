.MODEL SMALL
.STACK 100h
.DATA
    len1 dw 0
    len2 dw 0
    str1 db 100 dup(0)
    str2 db 100 dup(0)
    cursize dw 0
    track   dw 0
    Invalid db "EMPTY STRING$"
    

.CODE


main proc
    mov ax,@data
    mov ds,ax
    mov es,ax
    mov len1,0
    mov len2,0
    
    ;input 1st string
    CLD
    mov ah,1
    lea di,str1
    INPUT1:
        int 21h
        cmp al,32d
        jle END1
        stosb
        inc len1
        jmp INPUT1
    END1:
   
    ;input 2nd string
    mov ah,2
    mov dl,0ah
    int 21h   ;giving new line
    mov dl,0dh
    int 21h
    
    
    CLD
    mov ah,1    
    lea di,str2 
    INPUT2:
        int 21h
        cmp al,32d
        jle END2
        stosb
        inc len2
        jmp INPUT2
    END2:
    
    
    mov ah,2
    mov dl,0ah
    int 21h   ;giving new line
    mov dl,0dh
    int 21h
        
    
    ;initializing controls
    mov ax,len1
    mov cursize,ax
    mov track,0
    
    ;special case check
    cmp ax,len2 
    jl break_out
    
    ;general case check
    lea si,str1
    while_out:
        
        ;control for breaking the loop
        mov ax,cursize
        cmp ax,track
        je break_out
        
        ;to track down the half-matched strings like ababab and ba 
        mov dx,cursize
        sub dx,track
        cmp dx,len2
        jl MISMATCH
        
        
        
        ;initializing second string for iterations 
        ;and making sure 1st one's iterator isn't affected
        lea di,str2
        mov cx,len2
        push si
        
        
        CLD   
        repe cmpsb
        jne MISMATCH
        
        MATCH:
            pop dx
            push si
           
            mov di,si
            add di,-1
            ;lea di,si
            ;sub di,len2     
            ;mov cx,cursize
            ;sub cx,track
            ;sub cx,len2
            ;s1[k-s2.size()]=s1[k];
            mov cx,len2
            lea si,str2
           
            
            DO:
               movsb
               add di,-2
               loop DO
            ;mov bx,len2
            ;sub cursize,bx  ;cursize-=len2
            pop si
            ;inc si          ;restore si
            jmp while_out
        
        MISMATCH:
            pop si
            add si,1
            inc track
       jmp while_out
    
    break_out:        


    mov ah,2
    lea si,str1
    mov cx,cursize
    
        
    cmp cursize,0
    jne OUTPUT
    
    CHANGE:
          lea dx,INVALID
          mov ah,9
          int 21h
          jmp HOUSE
    
    
    OUTPUT:
        lodsb
        mov dl,al
        int 21h
    loop OUTPUT
    
    
    HOUSE:
    mov ah,4ch
    int 21h
main endp