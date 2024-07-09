# Link bootloader

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMENT "[ ** ] Stripping bootloader binary"
  COMMAND objcopy -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}
)
