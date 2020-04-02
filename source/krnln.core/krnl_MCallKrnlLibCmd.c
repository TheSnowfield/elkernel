// 屑語言核心支持庫内部實現
// 專門用於調用核心庫裏的其他函數

__declspec(naked)
krnl_MCallKrnlLibCmd() {
  __asm {
    lea     eax, [esp + 8]
    sub     esp, 12
    push    eax
    push    dword ptr[esp + 20]
    xor     eax, eax
    mov     [esp + 8], eax
    mov     [esp + 12], eax
    mov     [esp + 16], eax
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