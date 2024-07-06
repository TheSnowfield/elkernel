# Generate bootable CD
set(ELKERNRL_BOOTCD elkernel-cd.iso)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMENT "[ ** ] Building bootable iso ${ELKERNRL_BOOTCD}"
  COMMAND rm -rf .bootcd 2>&1
  COMMAND mkdir .bootcd
  COMMAND cp elkernel .bootcd/BOOT
  COMMAND truncate -s 1474560 .bootcd/BOOT
  COMMAND xorriso -as mkisofs -b BOOT -v -r -l -o ${ELKERNRL_BOOTCD} .bootcd
  COMMAND rm -rf .bootcd
)
