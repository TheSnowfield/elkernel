#include "stdint.h"

typedef uint32_t
  ( __stdcall kmemory_notifunc)
  (uint32_t uNotifyType, uint32_t voidArgument0, uint32_t voidArgument1);


// 回調函數
static kmemory_notifunc *lpfnMemoryCallback = NULL;

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

void __stdcall
_kmemory_write64(void* lpMemory, uint64_t nValue, int32_t nOffset) {
  uint64_t* lpWrite = (uint64_t*)lpMemory + nOffset;
  (*(uint64_t*)lpWrite) = nValue;
}


#pragma optimize("", off)
void __stdcall
_kmemory_fill8(void* lpMemory, uint8_t nValue, uint32_t nLength) {
  uint8_t* lpWrite = lpMemory;
  while (nLength) {
    (*lpWrite) = nValue;
    ++lpWrite; --nLength;
  }
}

void __stdcall
_kmemory_fill16(void* lpMemory, uint16_t nValue, uint32_t nLength) {
  uint16_t* lpWrite = lpMemory;
  while (nLength) {
    (*lpWrite) = nValue;
    ++lpWrite; --nLength;
  }
}

void __stdcall
_kmemory_fill32(void* lpMemory, uint32_t nValue, uint32_t nLength) {
  uint32_t* lpWrite = lpMemory;
  while (nLength) {
    (*lpWrite) = nValue;
    ++lpWrite; --nLength;
  }
}

void __stdcall
_kmemory_fill64(void* lpMemory, uint64_t nValue, uint32_t nLength) {
  uint64_t* lpWrite = lpMemory;
  while (nLength) {
    (*lpWrite) = nValue;
    ++lpWrite; --nLength;
  }
}

#pragma optimize("", on)