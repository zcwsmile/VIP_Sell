#pragma once
#include "ucExtInc.h"
//#include "types.h"

#ifdef _UC_LINUX
void init_daemon(void);
#endif

//////////////////////////////////////////////////////////////////////////
//  system

UCEAPI const uString &GetAppPath();
UCEAPI uString CreatePath(const char * szFilepath);
UCEAPI uString GetPathFromFilename(const uString filename);
UCEAPI bool LoadScriptLib(uString strName);
//  retrieves the number of milliseconds that have elapsed since the system was started
UCEAPI t_uint32 GetMSTick();

//////////////////////////////////////////////////////////////////////////
//  conversion

UCEAPI uString EncodeString(const uString & str, char seed);
UCEAPI uString DecodeString(const uString & str);
UCEAPI uString ConvertSecondTimeToString(const time_t &sec_time);
//  convert string to time, string as '2008-8-8 1:30:02' or '2008-8-8'
//  return 0 if failed
UCEAPI time_t ConvertStringToSecondTime(const uString & str);

//////////////////////////////////////////////////////////////////////////
//  configure

UCEAPI int		GetConfigInt(const char * szName, const char * szSpace=NULL);
UCEAPI uString	GetConfigStr(const char * szName, const char * szSpace=NULL);
UCEAPI void		SetConfigInt(const char * szName, int val, const char * szSpace=NULL);
UCEAPI void		SetConfigStr(const char * szName, const char* val, const char * szSpace=NULL);

//////////////////////////////////////////////////////////////////////////
//  etc

