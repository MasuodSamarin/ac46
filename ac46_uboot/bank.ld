MEMORY
{
    comm : ORIGIN = 0x2000, LENGTH = 0xA000 /*40K*/
}

SECTIONS
{
    .text :
    {
       *(.start)
       *(.text)
       *(.rodata*)
       *(.comm_rodata)
     } > comm
}
