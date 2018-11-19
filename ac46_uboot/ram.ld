

MEMORY
{
    comm(rx)        : ORIGIN = 0x2000, LENGTH = 0xC000 /*40K*/
    ram(rw)         : ORIGIN = 0x0000, LENGTH = 0x3000
    rom_usb_ram(rw) : ORIGIN = 0x44000,LENGTH = 0x1000
}

ENTRY(__CHIP_RESET_ENTRY);

SECTIONS
{
    . = ORIGIN(comm);
    .text :
    {
        *(.start)
        *(.text)
        *(.rodata*)
        *(.comm_rodata)
        . = ALIGN(4);
        *(.data*)
        . = ALIGN(4);
    } > comm

    .bss ALIGN(16) :
    {
        *(.intr_stack)
        *(.stack)
        *(.bss)
        *(COMMON)
        . = ALIGN(4);
    }

    . = ORIGIN(rom_usb_ram);
    .usb_ram ALIGN(4):
    {
        *(.usbhost_var)
        *(.sd_var)
        . = ALIGN(4);
    }> rom_usb_ram

_bss_begin = ADDR(.bss ) ;
_bss_size  = SIZEOF(.bss);


_usb_bss_begin = ADDR(.usb_ram ) ;
_usb_bss_size  = SIZEOF(.usb_ram);
}
