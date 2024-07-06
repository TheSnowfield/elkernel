# Link and generate the kernel file
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMENT "[ ** ] Linking kernel file ${PROJECT_NAME}.elf"
  COMMAND ld -m elf_i386 -T ../elkernel.lds lib${PROJECT_NAME}.a elkernel.obj -o ${PROJECT_NAME}.elf
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMENT "[ ** ] Stripping kernel binary"
  COMMAND cp ${PROJECT_NAME}.elf ${PROJECT_NAME}
  COMMAND objcopy -O binary ${PROJECT_NAME}
)
