# Combine bootloader an kernel image
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMENT "[ ** ] Building ${PROJECT_NAME}"
  COMMAND cat boot elkernel > ${PROJECT_NAME}
)
