// 屑語言核心支持庫内部實現
// 調用外部DLL命令

#include "stdafx.h"

extern void* __cdecl krnln_MGetDllCmdAdr(uint32_t uCallIndex);

__declspec(naked)
krnl_MCallDllCmd() {
  __asm { ret }
}
