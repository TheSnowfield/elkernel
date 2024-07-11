OUTPUT_FORMAT("pe-i386")
ENTRY(_krnl_MMain);

. = 0x8000;

SECTIONS {

  .head ALIGN(4) : {
    LONG(_krnl_MMain);
    LONG(0x00000000)
    LONG(0x00000000)
    LONG(0x00000000)
  }

  .text ALIGN(4) : {
    *(.text)
    *(.text*)
    KEEP(*(.init))
    KEEP(*(.fini))
  }

  .rodata ALIGN(4) : {
    *(.rodata)
    *(.rodata*)
  }

  .data ALIGN(4) : {
    *(.data)
    *(.data*)
    *(.rdata) /* quirky section from epl*/
    *(.eh_frame)
  }

  .bss ALIGN(4) : {
    *(.bss)
    *(.bss*)
  }

  /DISCARD/ : {
    *(.debug*)
    *(.comment)
  }

}
