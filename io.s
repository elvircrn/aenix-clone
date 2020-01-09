global outb

outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

global inb

; inb - returns a byte from the given I/O port
; stack: [esp + 4] The address of the I/O port
;        [esp    ] The return address
inb:
    mov dx, [esp + 4]     ; move the address of the I/O port to the dx register
    in al, dx             ; ready a byte from the I/O port and store it into the al register
    ret                   ; return the read byte