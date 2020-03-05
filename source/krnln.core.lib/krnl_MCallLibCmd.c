// 屑語言核心支持庫内部實現
// 用於調用核心庫除外的支持庫函數

__declspec(naked)
krnl_MCallLibCmd() {
  __asm {
    lea     edx, [esp + 8]
    sub     esp, 12
    push    edx
    push    dword ptr[esp + 20]
    mov     dword ptr[esp + 8], 0
    mov     dword ptr[esp + 12], 0
    mov     dword ptr[esp + 16], 0
    lea     edx, [esp + 8]
    push    edx
    call    ebx
    mov     eax, [esp + 12]
    mov     edx, [esp + 16]
    mov     ecx, [esp + 20]
    add     esp, 24
    retn
  }
}