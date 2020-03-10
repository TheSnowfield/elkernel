#include "stdint.h"

typedef uint32_t
  ( __stdcall kmemory_notifunc)
  (uint32_t uNotifyType, uint32_t voidArgument0, uint32_t voidArgument1);


// 回調函數
kmemory_notifunc *lpfnMemoryCallback = NULL;

void __stdcall
_kmemory_setcallback(kmemory_notifunc* pfnCallback) {
  lpfnMemoryCallback = pfnCallback;
}

void __stdcall
_kmemory_copy8(void* lpMemoryDst, void* lpMemorySrc,
  uint32_t nOffsetDst, uint32_t nOffsetSrc, uint32_t nLength) {

  uint8_t* lpWrite = (uint8_t*)lpMemoryDst + nOffsetDst;
  uint8_t* lpRead = (uint8_t*)lpMemorySrc + nOffsetSrc;

  for (uint32_t i = 0; i < nLength; ++i) {
    (*lpWrite) = (*lpRead);
    ++lpWrite; ++lpRead;
  }
}

uint8_t __stdcall
_kmemory_read8(void* lpMemory, int32_t nOffset) {
  uint8_t* lpRead = (uint8_t*)lpMemory + nOffset;
  return (*lpRead);
}

uint16_t __stdcall
_kmemory_read16(void* lpMemory, int32_t nOffset) {
  uint16_t* lpRead = (uint16_t*)lpMemory + nOffset;
  return (*lpRead);
}

uint32_t __stdcall
_kmemory_read32(void* lpMemory, int32_t nOffset) {
  uint32_t* lpRead = (uint32_t*)lpMemory + nOffset;
  return (*lpRead);
}

void __stdcall
_kmemory_write8(void* lpMemory, uint8_t nValue, int32_t nOffset) {
  uint8_t* lpWrite = (uint8_t*)lpMemory + nOffset;
  (*lpWrite) = nValue;
}

void __stdcall
_kmemory_write16(void* lpMemory, uint16_t nValue, int32_t nOffset) {
  uint16_t* lpWrite = (uint16_t*)lpMemory + nOffset;
  (*(uint16_t*)lpWrite) = nValue;
}

void __stdcall
_kmemory_write32(void* lpMemory, uint32_t nValue, int32_t nOffset) {
  uint32_t* lpWrite = (uint32_t*)lpMemory + nOffset;
  (*(uint32_t*)lpWrite) = nValue;
}

__declspec(naked)
_kmemory_fill8(void* lpMemory, uint8_t nValue, int32_t nLength) {
  //uint8_t* lpWrite = lpMemory;
  //while (nLength) {
  //  (*lpWrite) = nValue;
  //  ++lpWrite; --nLength;
  //}
  __asm {
    push	ebp
    mov	ebp, esp
    push	ecx

    mov	eax, DWORD PTR [ebp + 8]
    mov	DWORD PTR [ebp-4], eax
    LN2kmemory_fi:

    cmp	DWORD PTR [ebp + 16], 0
    je	SHORT LN1kmemory_fi

    mov	ecx, DWORD PTR [ebp - 4]
    mov	dl, BYTE PTR [ebp + 12]
    mov	BYTE PTR[ecx], dl

    mov	eax, DWORD PTR [ebp - 4]
    add	eax, 1
    mov	DWORD PTR [ebp - 4], eax
    mov	ecx, DWORD PTR [ebp + 16]
    sub	ecx, 1
    mov	DWORD PTR [ebp + 16], ecx

    jmp	SHORT LN2kmemory_fi
    LN1kmemory_fi:

    mov	esp, ebp
    pop	ebp
    ret	12
  }
}