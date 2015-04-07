#pragma once
#include "ucExtInc.h"
#include <uString.h>
#include <ucFile.h>
#include <ucstrstream.h>

class CTextLogger
{
public:
	enum EnLogFlag
	{
		FLAGS_MS		= 0x00000001,  //  output million second time
		FLAGS_THREAD	= 0x00000002,  //  output thread id
	};

	UCEAPI ~CTextLogger(void);
	UCEAPI static CTextLogger & Instance();

	UCEAPI void			SetFilePath(const char * szFilepath);
	UCEAPI void			Write(const char * fmt, ...);
	UCEAPI t_uint32		ModifyFlags(t_uint32 nAdd, t_uint32 nRemove);
private:
	CTextLogger(void);
	void CreateLogFile();
	CTextLogger(const CTextLogger &);
	const CTextLogger & operator=(const CTextLogger&);

	ucFile m_File;
	time_t m_tmNextDay;
	uString m_strPath;
	t_uint32 m_nFlags;
};

#define TEXTLOG		CTextLogger::Instance().Write
#define INIT_TEXTLOG(szpath)	CTextLogger::Instance().SetFilePath(szpath)

class CLoggerStream
{
public:
	CLoggerStream()
	{
		m_bCommit = false;
	}
	void Commit()
	{
		if(! m_bCommit)
		{
			m_bCommit = true;
			CTextLogger::Instance().Write(m_stm.c_str());
		}
	}
	~CLoggerStream()
	{
		Commit();
	}
	template<class T> CLoggerStream & operator<<(const T & t)
	{
		m_stm<<t;
		return *this;
	}
private:
	bool m_bCommit;
	ucStrStream m_stm;
};

#define BEGIN_LOG { CLoggerStream tmp_loggerstream_object; tmp_loggerstream_object
#define END_LOG ;}
