project(ekrnln)
set(CMAKE_C_STANDARD 11)
add_compile_options(-m32 -masm=intel -nostdlib -nodefaultlibs -fPIC)
# set( CMAKE_VERBOSE_MAKEFILE on)

# find all src file
set(_SRC "")
set(_SEARCH_FILE "")
  file(GLOB_RECURSE _SEARCH_FILE ${ELKERNEL_SOURCE_DIR}/*.s)
  list(APPEND _SRC ${_SEARCH_FILE})
  file(GLOB_RECURSE _SEARCH_FILE ${ELKERNEL_SOURCE_DIR}/*.c)
  list(APPEND _SRC ${_SEARCH_FILE})
  set_property(SOURCE ${_SRC} PROPERTY LANGUAGE C)

# add include directories
include_directories(
  ${ELKERNEL_SOURCE_DIR}
)

# add source files
add_library(${PROJECT_NAME} STATIC
  ${_SRC}
)
