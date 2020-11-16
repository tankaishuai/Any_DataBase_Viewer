#pragma once
#include <windows.h>

struct IDb32Fetch
{
  virtual bool OnFetch(
    long lRows, long lCols, long lNumCols,
    const void *varKey, bool bIsUnicodeKey, 
    const VARIANT *varVal) = 0;
};

struct IDb32;

#define DB32_SCHEMA_DEFAULT  (-1L)
#define DB32_FLAG_MASK       0x00FF
#define DB32_FLAG_ASYNC      0x0100
#define DB32_FLAG_UNIQUED    0x0200
#define DB32_FLAG_TEXTA      0x0400
#define DB32_FLAG_TEXTW      0x0800
#define DB32_FLAG_UTF8       0x1000

struct IDb32
{
  virtual void   Delete() = 0;
  virtual bool   Open(LPCWSTR szConn, LPCWSTR szUser = nullptr, LPCWSTR szPassword = nullptr) = 0;
  virtual bool   IsOpen() const = 0;
  virtual bool   GetSchema(long lType, LPCWSTR szSql = nullptr) = 0;
  virtual bool   Execute(LPCWSTR szSql, long lFlags, const void *pBlob1, ...) = 0;
  virtual bool   Fetch(IDb32Fetch *pFetch, long lMaxRows, long lFlags) = 0;
  virtual void   Close() = 0;
  virtual long   GetDDL(LPCWSTR szTbl, LPWSTR szText, long cchText) = 0;
  virtual void * RawHandle() = 0;
  virtual bool   ExecuteAsync(HWND hWnd, UINT uMsg, LPCWSTR szSql, long lFlags, const void *pBlob1, ...) = 0;
  virtual bool   FetchAsync(WPARAM wParam, LPARAM lParam, IDb32Fetch *pFetch, long lMaxRows, long lFlags) = 0;
  virtual bool   CancelAsync(HWND hWnd, UINT uMsg) = 0;
};

IDb32 * win32db_open(LPCWSTR szConn, LPCWSTR szUser, LPCWSTR szPassword);

void *  win32db_blob_ptr(const VARIANT *varVal);
int     win32db_blob_bytes(const VARIANT *varVal);
bool    win32db_blob_is_valid(const VARIANT *varVal);
