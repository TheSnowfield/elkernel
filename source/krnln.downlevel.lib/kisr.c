#include "stdint.h"

// 中斷接收器
// 内部使用的中斷函數表
typedef void
(__stdcall kisr_notifunc)();
static kisr_notifunc* lpfnIsrCallback;
static const void* _kisr_fault_table[32];

// 取得中斷索引函數地址
void* __stdcall
_kisr_get_service(uint8_t nIndex) {
  return nIndex < 32 ? _kisr_fault_table[nIndex] : NULL;
}

// 設置中斷接收器
void __stdcall
_kisr_set_callback(kisr_notifunc* pfnCallback) {
  lpfnIsrCallback = pfnCallback;
}

// 内部使用的一個跳板
void __declspec(naked)
_callback_kisr_stub() {
  __asm {




    iret
  }
}


// Intel保留的中斷函數 0-31
#define FAULTDEF(i) \
  void __declspec(naked) _kisr_fault##i(){ \
    __asm { xchg bx, bx }; \
    __asm { cli }; \
    __asm { pop eax }; \
    __asm { push i }; \
    __asm { jmp _callback_kisr_stub }; \
  }

// 一大堆中斷跳轉函數
FAULTDEF(0); FAULTDEF(1); FAULTDEF(2); FAULTDEF(3);
FAULTDEF(4); FAULTDEF(5); FAULTDEF(6); FAULTDEF(7);
FAULTDEF(8); FAULTDEF(9); FAULTDEF(10); FAULTDEF(11);
FAULTDEF(12); FAULTDEF(13); FAULTDEF(14); FAULTDEF(15);
FAULTDEF(16); FAULTDEF(17); FAULTDEF(18); FAULTDEF(19);
FAULTDEF(20); FAULTDEF(21); FAULTDEF(22); FAULTDEF(23);
FAULTDEF(24); FAULTDEF(25); FAULTDEF(26); FAULTDEF(27);
FAULTDEF(28); FAULTDEF(29); FAULTDEF(30); FAULTDEF(31);

static const void* _kisr_fault_table[32] = {
  _kisr_fault0,_kisr_fault1,_kisr_fault2,_kisr_fault3,
  _kisr_fault4,_kisr_fault5,_kisr_fault6,_kisr_fault7,
  _kisr_fault8,_kisr_fault9,_kisr_fault10,_kisr_fault11,
  _kisr_fault12,_kisr_fault13,_kisr_fault14,_kisr_fault15,
  _kisr_fault16,_kisr_fault17,_kisr_fault18,_kisr_fault19,
  _kisr_fault20,_kisr_fault21,_kisr_fault22,_kisr_fault23,
  _kisr_fault24,_kisr_fault25,_kisr_fault26,_kisr_fault27,
  _kisr_fault28,_kisr_fault29,_kisr_fault30,_kisr_fault31
};