#pragma once
#include <windows.h>

typedef bool (* OnFetch_t)(
  long lRows, long lCols, long lNumCols,
  const void *varKey, bool bIsUnicodeKey, 
  const VARIANT *varVal,
  void *pUser);

struct IDb32;

#define DB32_SCHEMA_DEFAULT  (-1L)
#define DB32_FLAG_MASK       0x00FF
#define DB32_FLAG_ASYNC      0x0100
#define DB32_FLAG_UNIQUED    0x0200

IDb32 * win32db_open(LPCWSTR szConn, LPCWSTR szUser, LPCWSTR szPassword);
bool    win32db_schema(IDb32 *pWrapper, long lType, LPCWSTR szSql);
bool    win32db_exec(IDb32 *pWrapper, LPCWSTR szSql, long lFlags);
bool    win32db_fetch(IDb32 *pWrapper, long lMaxRows, long lFlags, OnFetch_t pfnFetch, void *pUser);
void    win32db_close(IDb32 *pWrapper);
