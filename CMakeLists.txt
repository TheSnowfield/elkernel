cmake_minimum_required(VERSION 3.10)

project(elkernel)
set(CMAKE_C_STANDARD 11)
add_compile_options(-m32 -masm=intel -nostdlib -nodefaultlibs)

# useful directories
set(ELKERNEL_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ELKERNEL_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(ELKERNEL_SOURCE_DIR ${ELKERNEL_ROOT_DIR}/src)
set(ELKERNEL_TARGET_DIR ${ELKERNEL_ROOT_DIR}/target)
set(ELKERNEL_TOOL_DIR ${ELKERNEL_ROOT_DIR}/tools)

# find all src file
set(ELKERNEL_SOURCE_FILE "")
set(_SEARCH_FILES "")
  file(GLOB_RECURSE _SEARCH_FILES ${ELKERNEL_SOURCE_DIR}/*.s)
  list(APPEND ELKERNEL_SOURCE_FILE ${_SEARCH_FILES})
  file(GLOB_RECURSE _SEARCH_FILES ${ELKERNEL_SOURCE_DIR}/*.c)
  list(APPEND ELKERNEL_SOURCE_FILE ${_SEARCH_FILES})
  set_property(SOURCE ${ELKERNEL_SOURCE_FILE} PROPERTY LANGUAGE C)

# add include directories
include_directories(
  ${ELKERNEL_SOURCE_DIR}
)

# add source files as static library
add_library(${PROJECT_NAME} STATIC
  ${ELKERNEL_SOURCE_FILE}
)

# post builds
set(ELKERNEL_POST_BUILDS "")
  file(GLOB_RECURSE ELKERNEL_POST_BUILDS ${ELKERNEL_TARGET_DIR}/*.cmake)
foreach(POST_BUILD_FILE IN LISTS ELKERNEL_POST_BUILDS)
  include(${POST_BUILD_FILE})
endforeach()
