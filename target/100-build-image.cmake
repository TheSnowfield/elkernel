# Generate bootable CD
set(ELF_BOOTCD ${PROJECT_NAME}-cd.iso)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMENT "[ ** ] Building bootable iso ${ELF_BOOTCD}"
  COMMAND rm -rf .bootcd 2>&1
  COMMAND mkdir .bootcd
  COMMAND cp ${PROJECT_NAME} .bootcd/BOOT
  COMMAND truncate -s 1474560 .bootcd/BOOT
  COMMAND xorriso -as mkisofs -b BOOT -v -r -l -o ${ELF_BOOTCD} .bootcd
  COMMAND rm -rf .bootcd
)

# Generate floppy image
set(ELF_FLOPPY ${PROJECT_NAME}-fdd.img)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMENT "[ ** ] Building ${ELF_FLOPPY}"
  COMMAND cp ${PROJECT_NAME} ${ELF_FLOPPY}
  COMMAND truncate -s 1474560 ${ELF_FLOPPY}
)
