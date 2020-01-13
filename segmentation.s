global load_lgdt

load_lgdt:
    mov eax, [esp + 4]
    lgdt [eax]
    ret

global init

init:
    mov cs, 0x10
    mov ss, 0x10
    mov ds, 0x10
    mov es, 0x10
    mov gs, 0x10
    mov fs, 0x10
