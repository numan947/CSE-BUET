.Model Small
draw_row Macro x
    Local l1
; draws a line in row x from col 10 to col 300
    MOV AH, 0CH
    MOV AL, 4
    MOV CX, 10
    MOV DX, x
L1: INT 10h
    INC CX 
    CMP CX, 621
    JL L1
    EndM
draw_col Macro y
    Local l2
; draws a line col y from row 10 to row 189
    MOV AH, 0CH
    MOV AL, 4
    MOV CX, y
    MOV DX, 10
L2: INT 10h
    INC DX
    CMP DX, 461
    JL L2
    EndM
.stack 100h
.Data
new_timer_vec   dw  ?,?
old_timer_vec   dw  ?,?
timer_flag      db  0
new_key_vec     dw  ?,?
old_key_vec     dw  ?,?
scan_code       db  0
key_flag        db  0



tx11 dw 619
tx12 dw 719
tx21 dw 350
tx22 dw 450
tx31 dw 100
tx32 dw 200

nowx1 dw 0
nowx2 dw 0
nowx3 dw 0

px1 dw 11
px2 dw 81
playerPos dw 0

score dw 0
showScore db 'your score is: $'

game_end_flag dw 0




s1 dw 5
s2 dw 5
s3 dw 5
cnt dw 0
divisor dw 0
num dw 0


up_arrow=72
down_arrow=80
esc_key=1

.Code

set_display_mode Proc
; sets display mode and draws boundary;prepared by S.Mahmudul hasan 1305043
    MOV AH, 0
    MOV AL, 12h; 320x200 4 color
    INT 10h
; set bgd color
    MOV BH, 0
    MOV BL, 0; cyan
    INT 10h
; draw boundary
    draw_row 10
    draw_row 153
    draw_row 460
    draw_row 306
    draw_col 10
    draw_col 620
    ;draw_car 0
    RET
set_display_mode EndP

r1 proc   
    mov dx,30
    mov ah,0ch
    re1:
        int 10h
        inc dx
        cmp dx,134
        jle re1
    ret
    r1 endp

r2 proc
    mov dx,173
    mov ah,0ch
    re2:
        int 10h
        inc dx
        cmp dx,287
        jle re2 
    ret
    r2 endp

r3 proc
    mov dx,326
    mov ah,0ch
    re3:
        int 10h
        inc dx
        cmp dx,441
        jle re3
    ret
    r3 endp

move_rect1 Proc
    push ax
    push bx
    push cx
    push dx

    mov cx,tx11
    dec cx      ;update current pos
    mov tx11,cx ;save current pos
    MOV AL, 15  ;prepared by S.Mahmudul hasan 1305043
    cmp cx,10   ;check boundary crossed, i.e. the col is out of the boundary
    jle move1    
    CALL r1     

    move1:      
    
    mov cx,tx12 
    cmp cx,619
    jg move11
    mov al,0
    CALL r1
    move11:
    dec tx12
    call update_boundary_1
    ;comment*
    mov bx,tx11
    mov nowx1,bx
    cmp nowx1,12
    jg dr
    mov nowx1,12
    ;*
    dr:
    pop dx
    pop cx
    pop bx
    pop ax
    ret 
    move_rect1 EndP

    update_boundary_1 proc
    push cx
    mov cx,tx12
    cmp cx,10
    jg getOut
    mov tx11,620
    mov tx12,720
    inc score
    getOut:
    ;comment*
    mov bx,tx11
    mov nowx1,bx
    cmp nowx1,12
    jg drr
    mov nowx1,12
    ;*
    drr:
        pop cx
        ret
    update_boundary_1 endp
    
move_rect2 Proc
    push ax
    push bx
    push cx
    push dx

    
    mov cx,tx21
    dec cx      ;update current pos
    mov tx21,cx ;save current pos
    MOV AL, 15
    cmp cx,10   ;check boundary crossed, i.e. the col is out of the boundary
    jle move2    
    CALL r2     

    move2:      
    mov cx,tx22 
    cmp cx,619
    jg move22
    mov al,0
    CALL r2
    move22:
    dec tx22
    call update_boundary_2
    mov bx,tx21
    mov nowx2,bx
    cmp nowx2,12
    jg drr1
    mov nowx2,12
    ;*
    drr1:
        pop dx
        pop cx
        pop bx
        pop ax
    ret 
    move_rect2 EndP

update_boundary_2 proc
    push cx
    mov cx,tx22
    cmp cx,10
    jg getOut2
    mov tx21,620
    mov tx22,720
    inc score
    getOut2:
    mov bx,tx21
    mov nowx2,bx
    cmp nowx2,12
    jg drr11
    mov nowx2,12
    ;*
    drr11:
    pop cx  
    ret
    update_boundary_2 endp
    
    
move_rect3 Proc
    push ax
    push bx
    push cx
    push dx
        
    
    mov cx,tx31
    dec cx      ;update current pos
                ;prepared by S.Mahmudul hasan 1305043
    mov tx31,cx ;save current pos
    MOV AL, 15
    cmp cx,10   ;check boundary crossed, i.e. the col is out of the boundary
    jle move3    
    CALL r3     

    move3:      
    mov cx,tx32 
    cmp cx,619
    jg move33
    mov al,0
    CALL r3
    move33:
    dec tx32
    call update_boundary_3
    mov bx,tx31
    mov nowx3,bx
    cmp nowx3,12
    jg drr3
    mov nowx3,12
    ;*
    drr3:
    pop dx
    pop cx
    pop bx
    pop ax
    ret 
    move_rect3 EndP
    
update_boundary_3 proc
    push cx
    mov cx,tx32
    cmp cx,10
    jg getOut3
    mov tx31,620
    mov tx32,720
    inc score
    getOut3:
    mov bx,tx31
    mov nowx3,bx
    cmp nowx3,12
    jg drr33
    mov nowx3,12
    ;*
    drr33:
        pop cx
        ret
    update_boundary_3 endp
    
    
get_player_up proc
    push ax
    push bx
    push cx
    push dx
    

    mov cx,px1
    dpu:
        call r1
        inc cx
        cmp cx,px2
        jle dpu
    pop dx
    pop cx
    pop bx
    pop ax  
    ret
    get_player_up endp    

get_player_middle proc
    push ax
    push bx
    push cx
    push dx
    

    mov cx,px1
    dpm:
        call r2
        inc cx
        cmp cx,px2
        jle dpm
    pop dx
    pop cx
    pop bx
    pop ax  
    ret
    get_player_middle endp
    
    
    get_player_down proc
    push ax
    push bx
    push cx
    push dx
    

    mov cx,px1
    dpd:
        call r3
        inc cx
        cmp cx,px2
        jle dpd
    pop dx
    pop cx
    pop bx
    pop ax  
    ret
    get_player_down endp    

player_crush proc 
    push ax
    push bx
    push cx
    push dx
    
    chkNum1:
        cmp playerPos,1
        je gg1
    chkNum2:
        cmp playerPos,2
        je gg2
    chkNum3:
        cmp playerPos,3
        je gg3

    gg1:
    mov cx,nowx1 ;check 1st rect
    cmp cx,px2
    jle ENDGAME1
    jmp not_end
    
    gg2:
    mov cx,nowx2 ;check 2nd rect
    cmp cx,px2
    jle ENDGAME2
    jmp not_end
    
    gg3:
    mov cx,nowx3 ;check 3rd rect
    cmp cx,px2
    jle ENDGAME3
    jmp not_end
    
    
    ENDGAME1:
        mov game_end_flag,1
        jmp not_end
    ENDGAME2:
        mov game_end_flag,2
        jmp not_end
    ENDGAME3:
        mov game_end_flag,3
    not_end:
    
    pop dx
    pop cx
    pop bx
    pop ax
    ret 
    player_crush endp
    
move_player_up proc
    cmp playerPos,1
    je goBack1
    cmp playerPos,2
    je cpu2
    jmp cpu3
    
    cpu2:
        mov playerPos,1
        mov al,0
        call get_player_middle
        mov al,1
        call get_player_up    
        jmp goBack1
    cpu3:
        mov playerPos,2
        mov al,0
        call get_player_down
        mov al,1
        call get_player_middle
    goBack1:
    ret
    move_player_up endp

    ;prepared by S.Mahmudul hasan 1305043
    
    
move_player_down proc
    cmp playerPos,3
    je goBack2 
    cmp playerPos,2
    je cpd2
    jmp cpd1
    
    cpd2:
        mov playerPos,3
        mov al,0
        call get_player_middle
        mov al,1
        call get_player_down    
        jmp goBack2
    cpd1:
        mov playerPos,2
        mov al,0
        call get_player_up
        mov al,1
        call get_player_middle
    goBack2:
    ret
    move_player_down endp
    

    show_num proc
            ;special case 0-9
    cmp num,10
    jl SPECIAL


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
    RET
    show_num endp
    
    
    
timer_tick Proc
    PUSH DS
    PUSH AX
    
    MOV AX, Seg timer_flag
    MOV DS, AX
    MOV timer_flag, 1
    
    POP AX
    POP DS
    
    IRET
timer_tick EndP
   
setup_int Proc
; save old vector and set up new vector
; input: al = interrupt number
;    di = address of buffer for old vector
;prepared by S.Mahmudul hasan 1305043
;    si = address of buffer containing new vector
; save old interrupt vector
    MOV AH, 35h ; get vector
    INT 21h
    MOV [DI], BX    ; save offset
    MOV [DI+2], ES  ; save segment
; setup new vector
    MOV DX, [SI]    ; dx has offset
    PUSH DS     ; save ds
    MOV DS, [SI+2]  ; ds has the segment number
    MOV AH, 25h ; set vector
    INT 21h
    POP DS
    RET
setup_int EndP


keyboard_int proc
    push ds
    push ax 
    
    mov ax,seg scan_code
    mov ds,ax
    
    in al,60h
    push ax
    in al,61h
    
    mov ah,al
    or al,80h
    
    out 61h,al
    xchg ah,al
    out 61h,al
    pop ax
    mov ah,al
    test al,80h
    jne key_0
    mov scan_code,al
    mov key_flag,1
    key_0:
    mov al,20h
    out 20h,al
    
    pop ax
    pop ds
    
    IRET
    keyboard_int endp

main Proc
    MOV AX, @data
    MOV DS, AX
    mov score,0
    mov game_end_flag,0
    mov playerPos,2
; set up timer interrupt vector
    MOV new_timer_vec, offset timer_tick
    MOV new_timer_vec+2, CS
    MOV AL, 1CH; interrupt type
    LEA DI, old_timer_vec
    LEA SI, new_timer_vec
    CALL setup_int
    
    
    mov new_key_vec,offset keyboard_int
    mov new_key_vec+2,cs
    mov al,9h
    lea di,old_key_vec
    lea si, new_key_vec
    call setup_int
    
    
    
; start ball at col = 298, row = 100
;prepared by S.Mahmudul hasan 1305043
; for the rest of the program CX = ball row, DX = ball col
    ; set graphics display mode & draw border
    CALL set_display_mode
    
    push ax
    mov ax,tx11
    mov nowx1,ax
    mov ax,tx21
    mov nowx2,ax
    mov ax,tx31
    mov nowx3,ax
    pop ax
    
    
    mov cx,tx11
    call r1
    
    mov cx,tx21
    mov al,15
    draw2:
        call r2
        inc cx
        cmp cx,tx22
        jle draw2
    mov cx,tx31
    draw3:
        call r3
        inc cx
        cmp cx,tx32
        jle draw3
    
        
        mov al,1
        call get_player_middle
    

test_key:
    cmp key_flag,1
    jne test_timer
    mov key_flag,0
    cmp scan_code,esc_key
    jne tk_1
    jmp gameEnd
    
    tk_1:
        cmp scan_code,up_arrow
        jne tk_2
        ;;;todo uparrow
        call move_player_up
        jmp test_timer
    tk_2:
        cmp scan_code,down_arrow
        jne test_timer
        ;;todo downarrow 
        call move_player_down  
    
test_timer:
    CMP timer_flag, 1
    JNE test_key
    MOV timer_flag, 0
    
    mov cx,s1
    spd1:
        call move_rect1
        call player_crush
        loop spd1
    
    mov cx,s2
    spd2:
        call move_rect2
        call player_crush
        loop spd2
    
    mov cx,s3
    spd3:
        call move_rect3
        call player_crush
        loop spd3
    cmp game_end_flag,0
    jg gameEnd
    
test_timer2:
    CMP timer_flag, 1
    JNE test_timer2
    MOV timer_flag, 0
    JMP test_key
    

gameEnd:
mov ah,9
lea dx,showScore
int 21h

mov ax,score
mov num,ax
call show_num

mov ah,2
mov dl,0ah
int 21h
mov dl,0dh
int 21h
comment*
mov ax,nowx1
mov num,ax
call show_num

mov ah,2
mov dl,0ah
int 21h
mov dl,0dh
int 21h

mov ax,tx11
mov num,ax
call show_num

mov ah,2
mov dl,0ah
int 21h
mov dl,0dh
int 21h

mov ax,nowx2
mov num,ax
call show_num

mov ah,2
mov dl,0ah
int 21h
mov dl,0dh
int 21h

mov ax,tx21
mov num,ax
call show_num

mov ah,2
mov dl,0ah
int 21h
mov dl,0dh
int 21h

mov ax,nowx3
mov num,ax
call show_num

mov ah,2
mov dl,0ah
int 21h
mov dl,0dh
int 21h

mov ax,tx31
mov num,ax
call show_num

mov ah,2
mov dl,0ah
int 21h
mov dl,0dh
int 21h

mov ax,game_end_flag
mov num,ax
call show_num
    
*
mov ah,4ch
int 21h
mov ah,1
int 21h

main EndP
End main
;prepared by S.Mahmudul hasan 1305043