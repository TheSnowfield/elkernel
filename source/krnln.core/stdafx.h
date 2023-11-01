#pragma once
#include "stdint.h"
#include "elib.h"

typedef uint32_t
  (__stdcall kmemory_notifunc)
  (uint32_t uNotifyType, uint32_t voidArgument0, uint32_t voidArgument1);

static kmemory_notifunc* lpfnMemoryCallback;

#define KERNEL_KMEMORY_NOTIFY_MALLOC  0x00
#define KERNEL_KMEMORY_NOTIFY_REALLOC 0x01
#define KERNEL_KMEMORY_NOTIFY_FREEMEM 0x02
