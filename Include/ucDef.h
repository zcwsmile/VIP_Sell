#ifndef _UDEF_INCLUDE_FILE_3_4324_08943_7173897932
#define _UDEF_INCLUDE_FILE_3_4324_08943_7173897932

///////////////////////////////////////////////////////
//  the UCAPI definition, for supported platform

//  for windows
#ifdef _UC_WIN

	#pragma warning(disable:4786)

	#ifdef _UC_EXPORT
		#ifdef _DEBUG
		#define UCAPI __declspec(dllexport)
		#else
		#define UCAPI
		#endif
	#else
		#ifdef _DEBUG
		#define UCAPI __declspec(dllimport)
		#else
		#define UCAPI
		#endif

		#ifndef _UC_MSW_PRJ
			#ifdef _DEBUG
				#pragma comment(lib,"ucBased.lib")
			#else
				#pragma comment(lib,"ucBase.lib")
			#endif
		#endif
	#endif

#endif  //#ifdef _UC_WIN

//  for linux
#ifdef _UC_LINUX
	#define UCAPI
#endif  //#ifdef _UC_LINUX

///////////////////////////////////////////////////////
//  data type

//#ifdef  _UNICODE
//	#define uChar wchar_t
//	#define UTEXT(x)	L ## x
//#else
	//#define uChar char
	//#define UTEXT(x)	x
//#endif

typedef void* HUCBUFFER;

#ifdef _UC_WIN
typedef unsigned __int32	uDWord;
typedef unsigned char       uByte;
typedef unsigned __int16	uWord;
typedef unsigned int		uUInt;

#else
//#include <unistd.h>
#include <sys/types.h>
typedef __uint32_t			uDWord;
//#define uDWord				__uint32_t
typedef unsigned char       uByte;
typedef __uint16_t			uWord;
//#define uWord				__uint16_t
typedef unsigned int		uUInt;
#endif

#ifndef NULL
#define NULL    0
#endif

#ifdef _UC_WIN

#define t_byte		unsigned char
#define t_int16		__int16
#define t_uint16	unsigned __int16
#define t_int32		__int32
#define t_uint32	unsigned __int32
#define t_int64		__int64
#define t_uint64	unsigned __int64

#else
#include <stdint.h>
#define t_byte		unsigned char
#define t_int16		int16_t
#define t_uint16	uint16_t
#define t_int32		int32_t
#define t_uint32	uint32_t
#define t_int64		int64_t
#define t_uint64	uint64_t

#endif

//  for uString data type
#include <uString.h>

///////////////////////////////////////////////////////
//  common global macro

#include <assert.h>
#define _ucAssert			assert


///////////////////////////////////////////////////////////////////

#endif //#ifndef _UDEF_INCLUDE_FILE_3_4324_08943_7173897932
