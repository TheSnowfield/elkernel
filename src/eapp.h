#ifndef _EAPP_H
#define _EAPP_H

#include "eint.h"

typedef struct {
  uint32_t dwLibFormatVer;
  char*    szGuid;
  int32_t  nMajorVersion;
  int32_t  nMinorVersion;
  int32_t  nBuildNumber;
  int32_t  nRqSysMajorVer;
  int32_t  nRqSysMinorVer;
  int32_t  nRqSysKrnlLibMajorVer;
  int32_t  nRqSysKrnlLibMinorVer;
  char*    szName;
}ELIBINFO;
typedef ELIBINFO* LPELIBINFO;

typedef struct {
  int32_t    nEAppMajorVersion;
  int32_t    nEAppMinorVersion;
  int32_t    nEAppBuildNumber;
  void*      lpfnEcode;
  void*      lpEConst;
  void*      lpVoid0;
  void*      lpEForm;
  uint32_t   uVoid0;
  uint32_t   uELibInfoCount;
  LPELIBINFO *lpELibInfos;
  uint32_t   uEDllImportCount;
  char**     lpEDllNames;
  char**     lpEDllSymbols;
}EAPPINFO;
typedef EAPPINFO* LPEAPPINFO;
typedef const EAPPINFO* LPCEAPPINFO;

#define KRNLN_KMEMORY_NOTIFY_MALLOC  0x00
#define KRNLN_KMEMORY_NOTIFY_REALLOC 0x01
#define KRNLN_KMEMORY_NOTIFY_FREEMEM 0x02
typedef uint32_t (EAPP_MEMNOTIFUNC) (uint32_t uNotifyType, uint32_t arg0, uint32_t arg1);

#endif /* _EAPP_H */
