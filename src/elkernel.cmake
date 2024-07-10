cmake_minimum_required(VERSION 3.10)

include(${ELKERNEL_SOURCE_DIR}/eapp.cmake)
include(${ELKERNEL_SOURCE_DIR}/ekrnln.cmake)

# link executable
project(elkernel)
add_custom_target(${PROJECT_NAME} ALL
  DEPENDS ekrnln eapp

  COMMENT "Generating bootimg ld parameters"
  COMMAND python3
    ${ELKERNEL_TOOL_DIR}/make-bootimg-ld.py
    ${ELKERNEL_BUILD_DIR}

  COMMENT "Building ${PROJECT_NAME}.elf"
  COMMAND ld -m elf_i386
    -T ${ELKERNEL_SOURCE_DIR}/link.ld
    ${ELKERNEL_BUILD_DIR}/eapp.o
    ${ELKERNEL_BUILD_DIR}/libekrnln.a
    -o ${PROJECT_NAME}.elf

  COMMENT "Stripping ${PROJECT_NAME}.elf"
  COMMAND objcopy -O binary
    --set-section-flags .bootim=alloc,load,readonly
    ${PROJECT_NAME}.elf ${PROJECT_NAME}
)

set(_POST_BUILDS "")
  file(GLOB_RECURSE _POST_BUILDS ${ELKERNEL_SOURCE_DIR}/target/*.cmake)
foreach(_BUILD IN LISTS _POST_BUILDS)
  include(${_BUILD})
endforeach()
