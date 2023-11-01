// 屑語言核心支持庫内部實現
// 重新分配内存

#include "stdafx.h"

void* __cdecl
krnl_MRealloc(void *lpMemory, uint32_t uBytes) {

  // 還沒準備好
  if (!lpfnMemoryCallback)
    return NULL;

  // 通知上級函數
  void* lpMemoryNew = (void*)lpfnMemoryCallback(
    KERNEL_KMEMORY_NOTIFY_REALLOC, (uint32_t)lpMemory, uBytes
  );
  return lpMemoryNew;
}