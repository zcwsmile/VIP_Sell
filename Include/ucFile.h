// ucFile.h: interface for the ucFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UCFILE_H__3D0E0FEC_2E17_4EEF_B906_D97694985EBE__INCLUDED_)
#define AFX_UCFILE_H__3D0E0FEC_2E17_4EEF_B906_D97694985EBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <uString.h>

#define UFILE_OPEN		0x01
#define UFILE_CREATE	0x02
#define UFILE_READ		0x10
#define UFILE_WRITE		0x20
#define UFILE_APPEND	0x40

class ucFile
{
public:
	enum {begin,current,end};

	UCAPI void Close();
	UCAPI bool Open(const char * szFileName,long nFlag);
	UCAPI long Seek(long nOff,long nForm);
	UCAPI unsigned long Write(const void * pBuf,unsigned long nBufLen);
	UCAPI unsigned long Read(void * pBuf,unsigned long nBufLen);
	UCAPI void Flush();
	UCAPI unsigned long GetLength() const;
	UCAPI unsigned long GetPosition() const;
	UCAPI ucFile();
	UCAPI static bool Exist(const char * szFileName);

	~ucFile()
	{
		Close();
	}

	bool IsOpen() const
	{
		return m_file!=NULL;
	}
private:
	FILE * m_file;
	mutable unsigned long m_nFileLength;
};

#endif // !defined(AFX_UCFILE_H__3D0E0FEC_2E17_4EEF_B906_D97694985EBE__INCLUDED_)
