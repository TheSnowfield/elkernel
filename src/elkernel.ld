OUTPUT_FORMAT("pe-i386")
ENTRY(_krnl_MMain);

SECTIONS {

  .bootim : {

    /*
      the boot description for bootloader
      equals the c struct is

      typedef struct {
        char[8]  magic;
        uint32_t crc32; // reserved
        uint32_t flags  // reserved
        uint32_t image_size;
        uint32_t entry_offset;
        uint64_t date;  // reserved
        char[32] version;
        ALIGN(512);
      } bootim_t;

    */

    LONG(0x454b4c45); LONG(0x4c454e52);
    LONG(0x00000000);
    LONG(0x00000000);
    LONG(_im_code_end - _im_code_start);
    LONG(_krnl_MMain);
    INCLUDE "ld_date.ld";
    INCLUDE "ld_version.ld"; . = ALIGN(32);

    /* align to 512B which is sector 1 */
    /* the first sector contains the bootloader */
    . = ALIGN(512);
  }

  _im_code_start = .;

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

  _im_code_end = .;
}
