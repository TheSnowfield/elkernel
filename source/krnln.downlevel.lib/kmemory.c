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
  uint8_t* lpWrite = (uint8_t*)lpMemory + nOffset;
  return (*lpWrite);
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