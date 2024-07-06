OUTPUT_FORMAT("pe-i386")

ENTRY(_start)
. = 0x7c00;

SECTIONS {

  .text : {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    KEEP(*(.init))
    KEEP(*(.fini))
    . = ALIGN(4);
  }

  .rodata : {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  }

  .data : {
    . = ALIGN(4);
    *(.data)
    *(.data*)
    *(.rdata) /* quirky section from epl*/
    . = ALIGN(4);
  }

  .bss : {
    . = ALIGN(4);
    *(.bss)
    *(.bss*)
    . = ALIGN(4);
  }

}
