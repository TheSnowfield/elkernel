#pragma once

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

extern const EAPPINFO __eapp_info;
