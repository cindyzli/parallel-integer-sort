.section __TEXT,__text,regular,pure_instructions
.align 2
.global _merge_asm

.align 2
_merge_asm:
    stp x29, x30, [sp, #-16]! 
    mov x29, sp
    mov w5, #0         
    mov w6, #0     
    mov w7, #0       

.align 2
loop:
    cmp w5, w2
    b.ge right_only
    cmp w6, w4
    b.ge left_only
    ldr w8, [x1, w5, sxtw #2]  
    ldr w9, [x3, w6, sxtw #2]
    cmp w8, w9         
    ble copy_left    
    str w9, [x0, w7, sxtw #2]
    add w6, w6, #1     
    add w7, w7, #1    
    b loop

.align 2
copy_left:
    str w8, [x0, w7, sxtw #2]
    add w5, w5, #1      
    add w7, w7, #1     
    b loop

.align 2
left_only:
    cmp w5, w2
    b.ge done
    ldr w8, [x1, w5, sxtw #2]
    str w8, [x0, w7, sxtw #2]
    add w5, w5, #1
    add w7, w7, #1
    b left_only

.align 2
right_only:
    cmp w6, w4
    b.ge done
    ldr w8, [x3, w6, sxtw #2]
    str w8, [x0, w7, sxtw #2]
    add w6, w6, #1
    add w7, w7, #1
    b right_only

done:
    ldp x29, x30, [sp], #16 
    ret