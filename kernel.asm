section .multiboot
header_start:
    dd 0x1BADB002       
    dd 0x00000003       
    dd -(0x1BADB002 + 0x00000003) 

section .text
global _start
extern kmain           

_start:
    cli                
    mov esp, stack_top

    cmp eax, 0x2BADB002
    jne .no_multiboot

    push ebx           
    call kmain         

.no_multiboot:
    hlt                
    jmp $

section .bss
align 16
stack_bottom:
    resb 16384         
stack_top:
