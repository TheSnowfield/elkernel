# Generate floppy image
set(ELKERNRL_FLOPPY elkernel-fdd.img)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMENT "[ ** ] Building ${ELKERNRL_FLOPPY}"
  COMMAND cp elkernel ${ELKERNRL_FLOPPY}
  COMMAND truncate -s 1474560 ${ELKERNRL_FLOPPY}
)
