#include "stdint.h"

void* __stdcall
_kmemory_malloc(uint32_t nSizeBytes) {

  return NULL;
}

void __stdcall
_kmemory_free(void* lpMemory) {

}

void __stdcall
_kmemory_fill(void* lpMemory, uint8_t nValue, uint32_t nLength) {

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
  uint8_t* lpWrite = (uint8_t*)lpMemory + nOffset;
  (*(uint16_t*)lpWrite) = nValue;
}