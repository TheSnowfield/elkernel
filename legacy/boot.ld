OUTPUT_FORMAT("pe-i386")

ENTRY(_start);
BOOTSECT = 0x7c00;

SECTIONS {

  . = BOOTSECT;

  .text : SUBALIGN(4) {
    *(.text)
    *(.text*)
    KEEP(*(.init))
    KEEP(*(.fini))
  }

  .rodata : SUBALIGN(4) {
    *(.rodata);
    *(.rodata*);
  }

  .data : SUBALIGN(4) {
    *(.data);
    *(.data*);
  }

  .bootable_sig : AT(0x7dfe) {
    SHORT(0xaa55);
  }

  .bss : SUBALIGN(4) {
    *(.bss);
    *(.bss*);
  }

}
