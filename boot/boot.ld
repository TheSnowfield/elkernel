OUTPUT_FORMAT("pe-i386")

ENTRY(_start);
BOOTSECT = 0x7c00;

SECTIONS {

  . = BOOTSECT;

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

  .bootable_sig : AT(0x7dfe) {
    SHORT(0xaa55);
  }

}
