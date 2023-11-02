#include "include/stdint.h"
#include "include/ekrnln.h"
#include "include/eapp.h"

static EAPP_MEMNOTIFUNC* lpfnMemoryCallback;

/**
 *  @brief 易主程序入口 (位於易程序)
*/
extern int (EStartup)();

/**
 *  @brief 易程序入口 (位於系統核心支持庫)
*/
int __cdecl krnl_MMain() {

  __asm {
    mov ax, 0x0010
    mov ds, ax
    mov gs, ax
    mov es, ax

    mov esp, 0xFFFE   // 設置棧底

    xor eax, eax      // 清空寄存器
    mov ebx, eax      // 為接下來的代碼做準備
    mov ecx, eax
    mov edx, eax

    finit
    
    // bochs 魔術斷點
    xchg bx, bx

    // 因爲易語言要先在堆上初始化一些數組 (位於 EStartup)
    // 但是因爲我們的代碼在 ecode (_启动子程序)
    // EStartup 會比 ecode 先調用，導致我們的堆管理器還沒被初始化就被調用了
    // 所以我們先調用 ecode
    push 0x01         // 0x01 調用原因: 初始化
    call __eapp_info.lpfnEcode

    // bochs 魔術斷點
    xchg bx, bx

    // 取得 EStartup 的地址 (跳過13字節)
    mov eax, EStartup
    add eax, 13

    // 判斷是否是 CALL 指令
  nextinit:
    cmp byte ptr [eax], 0xe8
    jne endinit
    
    // 調用易語言的 init array
    mov ebx, [eax+1]
    add ebx, eax
    add ebx, 5
    call ebx
    add eax, 5
    jmp nextinit

  endinit:
    push 0x00         // 0x01 調用原因: 正式啓動内核
    call __eapp_info.lpfnEcode

    jmp $
  }
}

/**
 *  @brief 設置内存管理通知函數 (自己定的 非支持庫函數)
*/
void __stdcall krnl_MMSetCallback(EAPP_MEMNOTIFUNC* pfnCallback) {
  lpfnMemoryCallback = pfnCallback;
}

/**
 *  @brief 釋放内存
*/
void __cdecl krnl_MFree(void *lpMemory) {

  // 還沒準備好
  if (!lpfnMemoryCallback)
    return;

  // 通知上級函數
  lpfnMemoryCallback(
    KRNLN_KMEMORY_NOTIFY_FREEMEM, (uint32_t)lpMemory, 0
  );
}

/**
 *  @brief 申請内存
*/
void* __cdecl krnl_MMalloc(uint32_t uBytes) {

  // 還沒準備好
  if (!lpfnMemoryCallback)
    return NULL;

  // 通知上級函數
  void* lpMemory = (void*)lpfnMemoryCallback(
    KRNLN_KMEMORY_NOTIFY_MALLOC, uBytes, 0
  );
  return lpMemory;
}

/**
 *  @brief 重新分配内存
*/
void* __cdecl krnl_MRealloc(void* lpMemory, uint32_t uBytes) {

  // 還沒準備好
  if (!lpfnMemoryCallback)
    return NULL;

  // 通知上級函數
  void* lpMemoryNew = (void*)lpfnMemoryCallback(
    KRNLN_KMEMORY_NOTIFY_REALLOC, (uint32_t)lpMemory, uBytes
  );
  return lpMemoryNew;
}

/**
 *  @brief 申請内存 (不檢查)
*/
void* __cdecl krnl_MMallocNoCheck(uint32_t uBytes) {
  return NULL;
}

/**
 *  @brief 算术运算 - 求余数
 * 
 *  调用格式： 〈双精度小数型〉 求余数 （双精度小数型 被除数，双精度小数型 除数，... ） - 系统核心支持库->算术运算
 *  英文名称：mod
 *  求出两个数值的商，并返回余数部分，运算符号为“ % ”或“Mod”。本命令为初级命令。命令参数表中最后一个参数可以被重复添加。
 *  参数<1>的名称为“被除数”，类型为“双精度小数型（double）”。
 *  参数<2>的名称为“除数”，类型为“双精度小数型（double）”。
*/
void __cdecl krnln_fnMod(PMDATA_INF pRetData, UINT32 uArgCount, PMDATA_INF pArgInf) {

  // 遍歷參數 逐一計算
  INT32 dResult = pArgInf[0].m_double;
  for (int i = 1; i < (int)uArgCount; ++i) {
    (int)dResult %= (int)(&pArgInf[i].m_double);
  }

  // 返回
  pRetData->m_double = (DOUBLE)dResult;
}

/**
 *  @brief 数值转换 - 到整数
 *
 *  调用格式： 〈整数型〉 到整数 （通用型 待转换的文本或数值） - 系统核心支持库->数值转换
 *  英文名称：ToInt
 *  返回包含于文本内的整数值，文本中是一个适当类型的数值，支持全角书写方式。本命令也可用作将其他类型的数据转换为整数。本命令为初级命令。
 *  参数<1>的名称为“待转换的文本或数值”，类型为“通用型（all）”。
*/
void __cdecl krnln_fnToInt(PMDATA_INF pRetData, UINT32 uArgCount, PMDATA_INF pArgInf) {
  switch (pArgInf->m_dtDataType) {
    case SDT_BOOL:
    case SDT_INT:
    case SDT_SHORT:
    case SDT_SUB_PTR:
      pRetData->m_int = pArgInf->m_int; 
      return;
  }
}

#define KRNLN_DUMMY_SYMBOL_NAKED(name) __declspec(naked) name() { __asm { ret }; }
#define KRNLN_DUMMY_SYMBOL_STDCALL(name, arg) void __stdcall name##arg { return; }
KRNLN_DUMMY_SYMBOL_NAKED(krnl_MCallDllCmd);      // 調用外部DLL命令
KRNLN_DUMMY_SYMBOL_NAKED(krnl_MCallKrnlLibCmd);  // 調用支持庫内命令
KRNLN_DUMMY_SYMBOL_NAKED(krnl_MCallLibCmd);      // 調用核心庫除外的支持庫函數
KRNLN_DUMMY_SYMBOL_NAKED(krnln_MGetDllCmdAdr);   // 獲取外部DLL命令地址
KRNLN_DUMMY_SYMBOL_NAKED(krnl_MExitProcess);     // 程序結束 退出進程
KRNLN_DUMMY_SYMBOL_NAKED(krnl_MLoadBeginWin);    // 沒什麽用的 暫時沒見到過 (看名字像創建窗口
KRNLN_DUMMY_SYMBOL_NAKED(krnl_MMessageLoop);     // 窗口消息循環 沒什麽用
KRNLN_DUMMY_SYMBOL_NAKED(krnl_MOtherHelp);       // 貌似是初始化用途的函數 沒什麽用
KRNLN_DUMMY_SYMBOL_NAKED(krnl_MReadProperty);    // 讀窗口屬性字段 不用窗口組件沒什麽用
KRNLN_DUMMY_SYMBOL_NAKED(krnl_MReportError);     // 報告錯誤 目前沒什麽用
KRNLN_DUMMY_SYMBOL_NAKED(krnl_MWriteProperty);   // 寫窗口屬性字段 不用窗口組件沒什麽用
KRNLN_DUMMY_SYMBOL_STDCALL(krnl_ProcessNotifyLib, (int _, int __, int ___)); // 核心支持庫通知回調函數 沒什麽用
