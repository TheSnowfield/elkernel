OUTPUT_FORMAT("pe-i386")
ENTRY(_start);

SECTIONS {

  .text : ALIGN(4) {
    *(.text)
    *(.text*)
    KEEP(*(.init))
    KEEP(*(.fini))
  }

  .data : ALIGN(4) {
    *(.data);
    *(.data*);
  }

  .bss : ALIGN(4) {
    *(.bss)
  }

  .gdt_desc : ALIGN(4) {
    *(.gdt_desc)
  }

  .bootable_sig : {
    . = ALIGN(510);
    SHORT(0xaa55);
  }
}
