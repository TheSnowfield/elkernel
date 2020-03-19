#include "stdint.h"
#pragma warning(disable:4090)

// 中斷接收器
// 内部使用的中斷函數表
typedef void
(__stdcall kisr_notifunc)();
static kisr_notifunc* lpfnIsrCallback = NULL;
static const void* _kisr_fault_table[48];

// 中斷處理函數
void __declspec(naked)
_callback_kisr_stub() {
  __asm {

    // 保存寄存器
    pushad
    push ds
    push es
    push fs
    push gs

    // 設置段選擇器
    mov ax, 0x0010
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    // 將棧幀交給上級回調函數處理
    mov eax, esp
    push eax
    call lpfnIsrCallback

    // 恢復棧
    pop gs
    pop fs
    pop es
    pop ds
    popad

    // 彈出中斷索引號
    pop eax

    iretd
  }
}

// Intel保留的中斷函數 0-31
#define FAULTDEF(i) \
  void __declspec(naked) _kisr_irq_fault##i(){ \
    __asm { xchg bx, bx }; \
    __asm { cli }; \
    __asm { push i }; \
    __asm { jmp _callback_kisr_stub }; \
  }

#define IRQDEF(i) \
  void __declspec(naked) _kisr_irq##i(){ \
    __asm { cli }; \
    __asm { push i }; \
    __asm { jmp _callback_kisr_stub }; \
  }

// IDT 0 - 31
FAULTDEF(0); FAULTDEF(1); FAULTDEF(2); FAULTDEF(3);
FAULTDEF(4); FAULTDEF(5); FAULTDEF(6); FAULTDEF(7);
FAULTDEF(8); FAULTDEF(9); FAULTDEF(10); FAULTDEF(11);
FAULTDEF(12); FAULTDEF(13); FAULTDEF(14); FAULTDEF(15);
FAULTDEF(16); FAULTDEF(17); FAULTDEF(18); FAULTDEF(19);
FAULTDEF(20); FAULTDEF(21); FAULTDEF(22); FAULTDEF(23);
FAULTDEF(24); FAULTDEF(25); FAULTDEF(26); FAULTDEF(27);
FAULTDEF(28); FAULTDEF(29); FAULTDEF(30); FAULTDEF(31);

// IDT 32 - 47
IRQDEF(32); IRQDEF(33); IRQDEF(34); IRQDEF(35);
IRQDEF(36); IRQDEF(37); IRQDEF(38); IRQDEF(39);
IRQDEF(40); IRQDEF(41); IRQDEF(42); IRQDEF(43);
IRQDEF(44); IRQDEF(45); IRQDEF(46); IRQDEF(47);

// IDT 255
void __declspec(naked) 
_kisr_unknown() {
  __asm { xchg bx, bx };
  __asm { cli };
  __asm { pop eax };
  __asm { push 255 };
  __asm { jmp _callback_kisr_stub };
}

static const void* _kisr_fault_table[48] = {
  _kisr_irq_fault0,_kisr_irq_fault1,_kisr_irq_fault2,_kisr_irq_fault3,
  _kisr_irq_fault4,_kisr_irq_fault5,_kisr_irq_fault6,_kisr_irq_fault7,
  _kisr_irq_fault8,_kisr_irq_fault9,_kisr_irq_fault10,_kisr_irq_fault11,
  _kisr_irq_fault12,_kisr_irq_fault13,_kisr_irq_fault14,_kisr_irq_fault15,
  _kisr_irq_fault16,_kisr_irq_fault17,_kisr_irq_fault18,_kisr_irq_fault19,
  _kisr_irq_fault20,_kisr_irq_fault21,_kisr_irq_fault22,_kisr_irq_fault23,
  _kisr_irq_fault24,_kisr_irq_fault25,_kisr_irq_fault26,_kisr_irq_fault27,
  _kisr_irq_fault28,_kisr_irq_fault29,_kisr_irq_fault30,_kisr_irq_fault31,

  _kisr_irq32, _kisr_irq33,_kisr_irq34,_kisr_irq35,
  _kisr_irq36,_kisr_irq37,_kisr_irq38,_kisr_irq39,
  _kisr_irq40,_kisr_irq41,_kisr_irq42,_kisr_irq43,
  _kisr_irq44,_kisr_irq45,_kisr_irq46,_kisr_irq47
};

// 取得中斷索引函數地址
// 前32個是Intel保留
void* __stdcall
_kisr_get_service(uint8_t nIndex) {
  return nIndex < 47 ? _kisr_fault_table[nIndex] : _kisr_unknown;
}

// 設置中斷接收器
void __stdcall
_kisr_set_callback(kisr_notifunc* pfnCallback) {
  lpfnIsrCallback = pfnCallback;
}