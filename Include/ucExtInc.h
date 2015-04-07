#pragma once

#ifdef _UC_WIN
	#ifdef _UC_EXT_PRJ
		#define UCEAPI	__declspec(dllexport)
	#else
		#define UCEAPI  __declspec(dllimport)
		#ifdef _DEBUG
			#pragma comment(lib,"ucExtd.lib")
		#else
			#pragma comment(lib,"ucExt.lib")
		#endif
	#endif
#else
	#define UCEAPI
#endif

#include <uString.h>
