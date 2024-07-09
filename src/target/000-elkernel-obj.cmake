# Patch the quirky symbol
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMENT "[ ** ] Patching symbol '_krnl_ProcessNotifyLib@12'"
  COMMAND python3 ${ELKERNEL_TOOL_DIR}/patch-symbol.py
    _krnl_ProcessNotifyLib@12:_krnl_ProcessNotifyLib
    ${ELKERNEL_SOURCE_DIR}/elkernel.obj
    ${ELKERNEL_BUILD_DIR}/elkernel.obj
)
