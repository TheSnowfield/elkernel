cmake_minimum_required(VERSION 3.10)

project(elkernel)
set(CMAKE_C_STANDARD 11)
add_compile_options(-m32 -O3 -masm=intel -nostdlib -nodefaultlibs -fPIC)
set( CMAKE_VERBOSE_MAKEFILE on)

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Xlinker \"-T${ELKERNEL_SOURCE_DIR}/elkernel.ld\"")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Xlinker \"-melf_i386\"")

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

# add source files as kernel binary
add_executable(${PROJECT_NAME}
  ${ELKERNEL_SOURCE_FILE}
  ${ELKERNEL_BUILD_DIR}/elkernel.obj
)

# TODO
# pull docker image to build the source code

set(_POST_BUILDS "")
  file(GLOB_RECURSE _POST_BUILDS ${ELKERNEL_SOURCE_DIR}/target/*.cmake)
foreach(_BUILD IN LISTS _POST_BUILDS)
  include(${_BUILD})
endforeach()
