#include "stdint.h"

void* __stdcall
_memory_malloc(uint32_t nSizeBytes) {

  return NULL;
}

void __stdcall
_memory_free(void* lpMemory) {

}

void __stdcall
_memory_fill(void* lpMemory, uint8_t nValue, uint32_t nLength) {

}

void __stdcall
_memory_write8(void* lpMemory, uint8_t nValue, int32_t nOffset) {
  uint8_t* lpWrite = (uint8_t*)lpMemory + nOffset;
  (*lpWrite) = nValue;
}