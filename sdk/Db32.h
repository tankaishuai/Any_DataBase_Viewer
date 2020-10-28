#pragma once
#include <windows.h>

struct IDb32Fetch
{
  virtual bool OnFetch(
    long lRows, long lCols, long lNumCols,
    const void *varKey, bool bIsUnicodeKey, 
    const VARIANT *varVal) = 0;
};

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
#define DB32_FLAG_TEXTA      0x0400
#define DB32_FLAG_TEXTW      0x0800

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
IDb32 * win32db_open_v2(LPCWSTR szConn, LPCWSTR szUser, LPCWSTR szPassword);
bool    win32db_schema(IDb32 *pWrapper, long lType, LPCWSTR szSql);
bool    win32db_exec(IDb32 *pWrapper, LPCWSTR szSql, long lFlags);
bool    win32db_exec_v2(IDb32 *pWrapper, LPCWSTR szSql, long lMaxRows, long lFlags, OnFetch_t pfnFetch, void *pUser);
bool    win32db_fetch(IDb32 *pWrapper, long lMaxRows, long lFlags, OnFetch_t pfnFetch, void *pUser);
void    win32db_close(IDb32 *pWrapper);
long    win32db_get_ddl(IDb32 *pWrapper, LPCWSTR szTbl, LPWSTR szText, long cchText);
void *  win32db_raw_handle(IDb32 *pWrapper);

void *  win32db_blob_ptr(const VARIANT *varVal);
int     win32db_blob_bytes(const VARIANT *varVal);
bool    win32db_blob_is_valid(const VARIANT *varVal);

typedef IDb32 * (* win32db_raw_create_by_conn_t)(__inout LPCWSTR &szConn);
IDb32 * win32db_raw_create_by_conn(__inout LPCWSTR &szConn);
LRESULT APIENTRY win32db_open_guiA(HWND hParentWnd, HINSTANCE, LPCSTR szConn, UINT nCmdShow);
LRESULT APIENTRY win32db_open_guiW(HWND hParentWnd, HINSTANCE, LPCWSTR szConn, UINT nCmdShow);
INT_PTR win32db_open_gui_core(HWND hParentWnd, LPCWSTR szConn, bool bAllowSort, DLGPROC pfnWndProc);
