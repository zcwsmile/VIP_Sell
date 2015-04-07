#pragma once

#include <ucExtInc.h>
#include <types.h>

class uiStrFmt
{
public:
	virtual const uString & Format() const = 0;
};

class ucStrStream
{
public:
	UCEAPI ucStrStream();
	UCEAPI ~ucStrStream();
	UCEAPI const uString & GetString();
	UCEAPI bool IsEmpty() const;
	UCEAPI void Clear();

	operator const uString & ()
	{
		return GetString();
	}
	const char * c_str()
	{
		return GetString().c_str();
	}
	operator const char* ()
	{
		return c_str();
	}

	//////////////////////////////////////////////////////////////////////////
	//  input
	UCEAPI ucStrStream & operator <<(const uiStrFmt & fmt);
	UCEAPI ucStrStream & operator <<(int i);
	UCEAPI ucStrStream & operator <<(unsigned int i);
	UCEAPI ucStrStream & operator <<(const char * s);
	UCEAPI ucStrStream & operator <<(const uString & s);
	UCEAPI ucStrStream & operator <<(double f);
	UCEAPI ucStrStream & operator <<(float f);
	UCEAPI ucStrStream & operator <<(const t_int64 &i);
	UCEAPI ucStrStream & operator <<(const t_uint64 &i);
private:
	void * m_inner;
};

class ucStrFmtInt : public uiStrFmt
{
public:
	enum PrefixType
	{
		none,
		zero,
		blank
	};

	UCEAPI ucStrFmtInt(unsigned int val, int num, bool hex=true, PrefixType prefix=ucStrFmtInt::zero);
	virtual const uString & Format() const
	{
		return m_str;
	}
private:
	uString m_str;
};
