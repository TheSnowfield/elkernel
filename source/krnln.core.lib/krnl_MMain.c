// 屑語言核心支持庫内部實現
// 備用主程序入口

#include "stdafx.h"
#include "eappinfo.h"

extern int (EStartup)();

int __cdecl
krnl_MMain() {
  __asm {
    xchg bx, bx
    mov ax, 0x0010
    mov ds, ax
    mov gs, ax
    mov es, ax

    mov esp, 0xFFFF // 設置棧底

    xor eax, eax      // 清空寄存器
    mov ebx, eax      // 為接下來的代碼做準備
    mov ecx, eax
    mov edx, eax

    call EStartup

    jmp $
  }
}
