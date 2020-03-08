// 屑語言核心支持庫内部實現
// 申請内存 不檢測

#include "stdafx.h"

void* __cdecl
krnl_MMallocNoCheck_disable(uint32_t uBytes) {
  return NULL;
}
