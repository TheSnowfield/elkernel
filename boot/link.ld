OUTPUT_FORMAT("pe-i386")
ENTRY(_start);

. = 0x7c00;

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

  _code_end = .;
  .bootable_sig : {
    . = 0x7e00 - _code_end - 4;
    SHORT(0xaa55);
  }
}
