set(_BINARY_PATH ${ELKERNEL_BUILD_DIR}/CMakeFiles/eapp.dir/elkernel.e.o)

# pull docker image to build the source code
add_custom_target(eapp ALL

  COMMENT "Docker pulling ghcr.io/thesnowfield/el-buildtool:latest"
  COMMAND docker pull ghcr.io/thesnowfield/el-buildtool:latest

  COMMENT "Building elkernel.obj use el-buildtool"
  COMMAND docker run
    -e INPUT_FILE=workspace/src/elkernel.e
    -e INPUT_OPT_FAST_ARRAY=\"true\"
    -e INPUT_OPT_STACK_CHECK=\"false\"
    -e INPUT_OPT_DEADLOOP_CHECK=\"false\"
    -v \"${ELKERNEL_ROOT_DIR}:/workspace\"
    ghcr.io/thesnowfield/el-buildtool:latest

  COMMAND mv -f
    ${ELKERNEL_SOURCE_DIR}/elkernel.obj
    ${_BINARY_PATH}
)

# Patch the quirky symbol
add_custom_command(TARGET eapp POST_BUILD
  COMMENT "[ ** ] Patching symbol '_krnl_ProcessNotifyLib@12'"
  COMMAND python3 ${ELKERNEL_TOOL_DIR}/patch-symbol.py
    _krnl_ProcessNotifyLib@12:_krnl_ProcessNotifyLib
    ${_BINARY_PATH}
    ${ELKERNEL_BUILD_DIR}/eapp.o
)
