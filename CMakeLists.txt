cmake_minimum_required(VERSION 3.10)

# useful directories
set(ELKERNEL_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ELKERNEL_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(ELKERNEL_SOURCE_DIR ${ELKERNEL_ROOT_DIR}/src)
set(ELKERNEL_TARGET_DIR ${ELKERNEL_ROOT_DIR}/target)
set(ELKERNEL_TOOL_DIR ${ELKERNEL_ROOT_DIR}/tools)
set(ELKERNEL_BOOT_DIR ${ELKERNEL_ROOT_DIR}/boot)

# bootloader
include(${ELKERNEL_BOOT_DIR}/boot.cmake)

# elkernel
include(${ELKERNEL_SOURCE_DIR}/elkernel.cmake)

# make elfOS
project(elf)
add_custom_target(${PROJECT_NAME} ALL
  DEPENDS boot elkernel
  COMMENT "Run post builds"
)

# post builds
set(_POST_BUILDS "")
  file(GLOB_RECURSE _POST_BUILDS ${ELKERNEL_TARGET_DIR}/*.cmake)
foreach(POST_BUILD_FILE IN LISTS _POST_BUILDS)
  include(${POST_BUILD_FILE})
endforeach()
