cmake_minimum_required(VERSION 3.10)

project(bootloader)

# search the source codes
set(_BOOT_SRC "")
set(_SEARCH_FILES "")
  file(GLOB_RECURSE _SEARCH_FILES ${ELKERNEL_BOOT_DIR}/*.s)
  list(APPEND _BOOT_SRC ${_SEARCH_FILES})

# batch assembling
set(_BOOT_BINARY "")
set(_LINK_CMD "")
set(CUSTOM_IMM_PATH ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles)
  foreach(_SRC IN LISTS _BOOT_SRC)
    get_filename_component(_FILE ${_SRC} NAME)
    set (_LINK_CMD ${_LINK_CMD} ${CUSTOM_IMM_PATH}/${_FILE}.dir/${_FILE}.o)
    add_custom_target(${_FILE} ALL
      COMMAND mkdir -p ${CUSTOM_IMM_PATH}
      COMMAND as --32 ${_SRC} -o ${CUSTOM_IMM_PATH}/${_FILE}.dir/${_FILE}.o
    )
endforeach()

# link executable
add_custom_target(${PROJECT_NAME} ALL
  COMMENT "Linking bootloader ${PROJECT_NAME}.elf"
  COMMAND ld -m elf_i386 -T ${ELKERNEL_BOOT_DIR}/boot.ld ${_LINK_CMD} -o ${PROJECT_NAME}.elf
)

set(_POST_BUILDS "")
  file(GLOB_RECURSE _POST_BUILDS ${ELKERNEL_BOOT_DIR}/target/*.cmake)
foreach(_BUILD IN LISTS _POST_BUILDS)
  include(${_BUILD})
endforeach()
