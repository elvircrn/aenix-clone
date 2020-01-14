global load_lgdt

load_lgdt:
    mov eax, [esp + 4]
    lgdt [eax]
    ret

global init_lgdt

init_lgdt:
    mov ax, 0x10
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov fs, ax
