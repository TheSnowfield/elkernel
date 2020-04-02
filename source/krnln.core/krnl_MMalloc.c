// 屑語言核心支持庫内部實現
// 申請内存

#include "stdafx.h"

void* __cdecl
krnl_MMalloc(uint32_t uBytes) {

  // 還沒準備好
  if (!lpfnMemoryCallback)
    return NULL;

  // 通知上級函數
  void* lpMemory = (void*)lpfnMemoryCallback(
    KERNEL_KMEMORY_NOTIFY_MALLOC, uBytes, 0
  );
  return lpMemory;
}
