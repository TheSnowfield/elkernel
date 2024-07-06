.intel_syntax noprefix

.text

.extern _EStartup
.extern ___eapp_info

.global _krnl_MMain
.global _krnl_MMalloc
.global _krnl_MMSetCallback
.global _krnl_MMallocNoCheck
.global _krnl_MFree
.global _krnl_MRealloc
.global _krnl_MCallKrnlLibCmd
.global _krnl_MCallDllCmd
.global _krnl_MCallLibCmd
.global _krnln_MGetDllCmdAdr
.global _krnl_MExitProcess
.global _krnl_MLoadBeginWin
.global _krnl_MMessageLoop
.global _krnl_MOtherHelp
.global _krnl_MReadProperty
.global _krnl_MReportError
.global _krnl_MWriteProperty
.global _krnl_ProcessNotifyLib

_krnl_MMain:
  push ebp
  mov ebp, esp
  push ebx

  mov ax, 0x0010
  mov ds, ax
  mov gs, ax
  mov es, ax

  mov esp, 0xFFFE   # 設置棧底

  xor eax, eax      # 清空寄存器
  mov ebx, eax      # 為接下來的代碼做準備
  mov ecx, eax
  mov edx, eax

  finit

  # bochs 魔術斷點
  xchg bx, bx

  # 因爲易語言要先在堆上初始化一些數組 (位於 _EStartup)
  # 但是因爲我們的代碼在 ecode (_启动子程序)
  # _EStartup 會比 ecode 先調用，導致我們的堆管理器還沒被初始化就被調用了
  # 所以我們先調用 ecode
  push 0x01         # 0x01 調用原因: 初始化
  call _krnl_MMain_eappinfo_ecode

  # 取得 _EStartup 的地址 (跳過13字節)
  mov eax, offset _EStartup
  add eax, 13

    # 判斷是否是 CALL 指令
  nextinit:
    cmp byte ptr [eax], 0xe8
    jne endinit
    
    # 調用易語言的 init array
    mov ebx, dword ptr [eax+1]
    add ebx, eax
    add ebx, 5
    call ebx
    add eax, 5
    jmp nextinit

  endinit:
    push 0x00         # 0x01 調用原因: 正式啓動内核
    call _krnl_MMain_eappinfo_ecode

    jmp $

  _krnl_MMain_eappinfo_ecode:
    jmp dword ptr [cs:___eapp_info + 12]


_krnl_MMSetCallback:
  mov eax, [esp + 4]
  mov _MemoryCallback, eax
  ret 4

_krnl_MMalloc:
  mov eax, dword ptr _MemoryCallback
  test eax, eax
  jnz _krnl_MMalloc_not_zero
    ret
  _krnl_MMalloc_not_zero:
    push 0          # arg1
    push [esp + 8]  # arg0
    push 0          # uNotifyType
    call eax
  ret

_krnl_MMallocNoCheck:
  jmp _krnl_MMalloc

_krnl_MFree:
  mov eax, dword ptr _MemoryCallback
  test eax, eax
  jz _krnl_MFree_not_zero
    ret
  _krnl_MFree_not_zero:
    push 0          # arg1
    push [esp + 8]  # arg0
    push 2          # uNotifyType
    call eax
  ret

_krnl_MRealloc:
  mov eax, dword ptr _MemoryCallback
  test eax, eax
  jnz _krnl_MRealloc_not_zero
    ret
  _krnl_MRealloc_not_zero:
    push dword ptr [esp + 8]   # arg1
    push dword ptr [esp + 8]   # arg0
    push 1           # uNotifyType
    call eax
  ret

_krnl_MCallKrnlLibCmd:
  lea eax, dword ptr [esp + 8]
  sub esp, 12
  push eax
  push dword ptr[esp + 20]
  xor eax, eax
  mov dword ptr [esp + 8], eax
  mov dword ptr [esp + 12], eax
  mov dword ptr [esp + 16], eax
  lea edx, dword ptr [esp + 8]
  push edx
  call ebx
  mov eax, dword ptr [esp + 12]
  mov edx, dword ptr [esp + 16]
  mov ecx, dword ptr [esp + 20]
  add esp, 24
  ret

_krnl_MCallDllCmd:      # 調用外部DLL命令
  ret

_krnl_MCallLibCmd:      # 調用核心庫除外的支持庫函數
  ret

_krnln_MGetDllCmdAdr:   # 獲取外部DLL命令地址
  ret

_krnl_MExitProcess:     # 程序結束 退出進程
  ret

_krnl_MLoadBeginWin:    # 沒什麽用的 暫時沒見到過 (看名字像創建窗口
  ret

_krnl_MMessageLoop:     # 窗口消息循環 沒什麽用
  ret

_krnl_MOtherHelp:       # 貌似是初始化用途的函數 沒什麽用
  ret

_krnl_MReadProperty:    # 讀窗口屬性字段 不用窗口組件沒什麽用
  ret

_krnl_MReportError:     # 報告錯誤 目前沒什麽用
  ret

_krnl_MWriteProperty:   # 寫窗口屬性字段 不用窗口組件沒什麽用
  ret

_krnl_ProcessNotifyLib: # 核心支持庫通知回調函數 沒什麽用
  ret 12

.data
_MemoryCallback:
  .4byte 0
