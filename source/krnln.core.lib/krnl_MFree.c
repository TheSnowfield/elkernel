﻿// 屑語言核心支持庫内部實現
// 釋放内存

#include "stdafx.h"

void __cdecl
krnl_MFree(void *lpMemory) {

  __asm { xchg bx, bx}
  __asm { xchg bx, bx}
  __asm { xchg bx, bx}
  __asm { xchg bx, bx}
  __asm { xchg bx, bx}

  // 還沒準備好
  if (!lpfnMemoryCallback)
    return NULL;

  // 通知上級函數
  lpfnMemoryCallback(
    KERNEL_KMEMORY_NOTIFY_FREEMEM, (uint32_t)lpMemory, 0
  );
}
