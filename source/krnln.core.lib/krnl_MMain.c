// 屑語言核心支持庫内部實現
// 備用主程序入口

#include "stdafx.h"
#include "eappinfo.h"

extern int (EStartup)();

int __cdecl
krnl_MMain() {
  __asm { xor eax, eax }
  return EStartup();
}