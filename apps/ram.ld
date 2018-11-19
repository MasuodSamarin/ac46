MEMORY
{
    flash(x)        : ORIGIN = 0x0001000000+5K, LENGTH = 16M      /* 16MBytes */
    ram0            : ORIGIN = 0x300000, LENGTH = 128k-256          /* 128KBytes-256 */
    ram1            : ORIGIN = 0x344000, LENGTH = 4k
}


SECTIONS
{
  . = ORIGIN(ram0);
  .data ALIGN(4):
  {
      *(.data*)

      _system_cfg_begin = .;
        *(.system_cfg)
      _system_cfg_end = .;

	  . = ALIGN(4);
	  *lbuf.o(.text .rodata*)
	  *run_loop.o(.text .rodata*)
	  *inquiry_scan.o(.text .rodata*)
	  *link_controller.o(.text .rodata*)
	  *irq.o(.text .rodata*)
	  *_umodsi3.o(.text .rodata*)
	  *_modsi3.o(.text .rodata*)
	  *_muldi3.o(.text .rodata*)
	  *_umulsi3_highpart.o(.text .rodata*)
	  *_lshrdi3.o(.text .rodata*)
	  *_ashldi3.o(.text .rodata*)
	  *_divdi3.o(.text .rodata*)
	  *_udivdi3.o(.text .rodata*)
	  *_umoddi3.o(.text .rodata*)
	  *_clz.o(.text .rodata*)
	  *lib_a-impure.o(.text .rodata*)
      *(.clock_lib)
	  *(.comm)
	  *(.comm_ro)
	  . = ALIGN(4);
  } > ram0

  .bss ALIGN(4):
  {
      *(.stack)
      *(.sddata*)
      *(.bss)
      *(.baseband_base)
      *(.baseband)
  } > ram0

  _SDRAM_BEGIN_ADDR = ORIGIN(ram0);
  _SRAM_END_ADDR  = . ;

  _sram_end  = . - ORIGIN(ram0);

  . = ORIGIN(ram1) ;
  .data1 ALIGN(4):
  {
      *memcpy.o(.text .rodata*)
      *memset.o(.text .rodata*)
      *(.flushinv_icache)
      *low_power.o(.text .rodata*)

  } > ram1

  .bss2 ALIGN(4):
  {
      *(.dac_buf_sec)
      *(.sd_buf)
      *(.usb_buf)
  } > ram1

  . = ORIGIN(flash) ;
  .text  ALIGN(4):
  {
      *startup.o(.text)


      _VM_CODE_START = . ;
      *(.vm)
      _VM_CODE_END = . ;

      _sound_dev_instance_begin = .;
       *(.sound_dev.ins)
      _sound_dev_instance_end = .;

	  _fsys_begin = .;
	  	*(.fsys)
	  _fsys_end = .;
	  _dev_drv_begin = .;
	  	*(.fsys_dev_drv)
	  _dev_drv_end = .;

	  _sound_proc_begin = .;
	  *(.sound_proc)
	  _sound_proc_end = .;
	  _sound_dev_begin = .;
	  *(.sound_dev)
	  _sound_dev_end = .;

	  _bt_sleep_begin = .;
	  *(.bt_sleep)
	  _bt_sleep_end = .;

	  _task_list_begin = .;
	  *(.task_info)
	  _task_list_end = .;

      *(.text .rodata*)
  } > flash

  _text_end = . ;


  _VM_CODE_SIZE = _VM_CODE_END - _VM_CODE_START;
  _text_size = SIZEOF(.text)+SIZEOF(.data);
  _alldata_size =  SIZEOF(.data) + SIZEOF(.bss);

  _bss_begin = ADDR(.bss ) ;
  _bss_size  = SIZEOF(.bss);

  _data_addr  = ADDR(.data) ;
  _data_begin = _text_end ;
  _data_size =  SIZEOF(.data) ;

  _data1_addr  = ADDR(.data1) ;
  _data1_begin = _text_end + SIZEOF(.data);
  _data1_size =  SIZEOF(.data1) ;

  _bss2_begin  = ADDR(.bss2) ;
  _bss2_size =  SIZEOF(.bss2) ;
}
