project(boot)

# search the source codes
set(_BOOT_SRC "")
set(_SEARCH_FILES "")
  file(GLOB_RECURSE _SEARCH_FILES ${ELKERNEL_BOOT_DIR}/*.s)
  list(APPEND _BOOT_SRC ${_SEARCH_FILES})

# batch assembling
set(_BOOT_BINARY "")
set(_LINK_CMD "")
set(CUSTOM_IMM_PATH ${ELKERNEL_BUILD_DIR}/CMakeFiles)
  foreach(_SRC IN LISTS _BOOT_SRC)
    get_filename_component(_FILE ${_SRC} NAME)
    set (_LINK_CMD ${_LINK_CMD} ${CUSTOM_IMM_PATH}/${_FILE}.dir/${_FILE}.o)
    add_custom_target(${_FILE} ALL
      # COMMAND mkdir -p ${CUSTOM_IMM_PATH}
      COMMAND echo "as --32 ${_SRC} -o ${CUSTOM_IMM_PATH}/${PROJECT_NAME}.dir/${_FILE}.o"
      COMMAND as --32 ${_SRC} -o ${CUSTOM_IMM_PATH}/${_FILE}.dir/${_FILE}.o
    )
endforeach()

# link executable
add_custom_target(${PROJECT_NAME} ALL
  COMMENT "Linking bootloader ${PROJECT_NAME}.elf"
  COMMAND ld -m elf_i386 -T ${ELKERNEL_BOOT_DIR}/link.ld ${_LINK_CMD} -o ${PROJECT_NAME}.elf

  COMMENT "Stripping bootloader binary"
  COMMAND objcopy -O binary
    --set-section-flags .bootable_sig=alloc,load,readonly
    --verbose
    ${PROJECT_NAME}.elf ${PROJECT_NAME}
)
