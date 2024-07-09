cmake_minimum_required(VERSION 3.10)

project(elf)
set(CMAKE_C_STANDARD 11)
add_compile_options(-m32 -masm=intel -nostdlib -nodefaultlibs)

# useful directories
set(ELKERNEL_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ELKERNEL_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(ELKERNEL_SOURCE_DIR ${ELKERNEL_ROOT_DIR}/src)
set(ELKERNEL_TARGET_DIR ${ELKERNEL_ROOT_DIR}/target)
set(ELKERNEL_TOOL_DIR ${ELKERNEL_ROOT_DIR}/tools)
set(ELKERNEL_BOOT_DIR ${ELKERNEL_ROOT_DIR}/boot)

# legacy bootloader
include(${ELKERNEL_BOOT_DIR}/boot.cmake)

# elkernel
include(${ELKERNEL_SOURCE_DIR}/elkernel.cmake)

# post builds
set(_POST_BUILDS "")
  file(GLOB_RECURSE _POST_BUILDS ${ELKERNEL_TARGET_DIR}/*.cmake)
foreach(POST_BUILD_FILE IN LISTS _POST_BUILDS)
  include(${POST_BUILD_FILE})
endforeach()

