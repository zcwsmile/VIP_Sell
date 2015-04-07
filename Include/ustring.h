#ifndef __UC_STRING_HEADER_FILE__
#define __UC_STRING_HEADER_FILE__

#include "ucDef.h"
#include <assert.h>
#include <string.h>
#include <ctype.h>

#if _MSC_VER >= 1400
#pragma warning(disable: 4996)
#endif

inline void _ucStrUppercase( char * psz ) throw()
{
#ifdef _UC_WIN
	//#ifdef _UNICODE
	//	_wcsupr(psz);
	//#else
	_strupr(psz);
	//#endif
#elif defined(_UC_LINUX)
	for(; *psz; psz++)
		*psz = toupper(*psz);
#else
	_ucAssert(false);
#endif
}

inline void _ucStrLowercase( char * psz ) throw()
{
#ifdef _UC_WIN
	//#ifdef _UNICODE
	//	_wcslwr(psz);
	//#else
	_strlwr(psz);
	//#endif
#elif defined(_UC_LINUX)
	for(; * psz; psz++)
		*psz = tolower(*psz);
#else
	_ucAssert(false);
#endif
}

inline int  _ucStricmp( const char * pszA, const char * pszB ) throw()
{
#ifdef _UC_WIN
	//#ifdef _UNICODE
	//	return _wcsicmp(pszA,pszB);
	//#else
	return _stricmp(pszA,pszB);
	//#endif
#elif defined(_UC_LINUX)
	return strcasecmp(pszA, pszB);
#else
	_ucAssert(false);
#endif
}

inline int _ucStrcmp( const char * pszA, const char *pszB )
{
	//#ifdef _UNICODE
	//	return wcscmp(pszA,pszB);
	//#else
	return strcmp(pszA,pszB);
	//#endif
}

inline int _ucStrlen( const char * psz ) throw()
{
	// returns length in bytes
	//#ifdef _UNICODE
	//	return (psz != NULL) ? int( wcslen( psz ) ) : 0;
	//#else
	return (psz != NULL) ? int( strlen( psz ) ) : 0;
	//#endif 
}

inline int _ucIsspace( char ch ) throw()
{
	//#ifdef _UNICODE
	//	return iswspace(ch);
	//#else
	if(ch&0x80)
		return 0;
	return isspace(ch);
	//#endif
}

inline const char * _ucFindstr(const char * pszBlock, const char * pszMatch)
{
	//#ifdef _UNICODE
	//	return wcsstr(pszBlock,pszMatch);
	//#else
	return strstr(pszBlock,pszMatch);
	//#endif
}

/////////////////////////////////////////////////////////////////////////////////////

struct uStringData
{
	int nDataLength;  // Length of currently used data in XCHARs (not including terminating null)
	int nAllocLength;  // Length of allocated data in XCHARs (not including terminating null)
	long nRefs;     // Reference count: negative == locked

	void* data() throw()
	{
		return (this+1);
	}

	void AddRef() throw()
	{
		assert(nRefs > 0);
		++nRefs;
	}
	bool IsLocked() const throw()
	{
		return nRefs < 0;
	}
	UCAPI bool IsShared() const throw();
	UCAPI void Release() throw();
	void Lock() throw()
	{
		assert( nRefs <= 1 );
		nRefs--;
		if( nRefs == 0 )
		{
			// Locked buffers can't be shared, so no interlocked operation necessary
			nRefs = -1;
		}
	}
	void Unlock() throw()
	{
		assert( IsLocked() );

		if(IsLocked())
		{
			nRefs++;
			// Locked buffers can't be shared, so no interlocked operation necessary
			if( nRefs == 0 )
			{
				nRefs = 1;
			}
		}
	}
};

UCAPI uStringData* GetNilString();

class uSimpleString
{
public:
	operator const char *() const throw()
	{
		return( m_pszData );
	}
	char at( int iChar ) const
	{
		assert( (iChar >= 0) && (iChar <= size()) );  // Indexing the '\0' is OK
		if( (iChar < 0) || (iChar > size()) )
			return 0;

		return( m_pszData[iChar] );
	}
	char * buffer()
	{
		uStringData* pData = GetData();
		if( pData->IsShared() )
		{
			Fork( pData->nDataLength );
		}

		return( m_pszData );
	}
	char * buffer( int nMinBufferLength )
	{
		return( PrepareWrite( nMinBufferLength ) );
	}

	int size() const throw()
	{
		return( GetData()->nDataLength );
	}

	const char * c_str() const throw()
	{
		return( m_pszData );
	}
	bool empty() const throw()
	{
		return( size() == 0 );
	}
	char * lockbuffer()
	{
		uStringData* pData = GetData();
		if( pData->IsShared() )
		{
			Fork( pData->nDataLength );
			pData = GetData();  // Do it again, because the fork might have changed it
		}
		pData->Lock();

		return( m_pszData );
	}
	void unlockbuffer() throw()
	{
		uStringData* pData = GetData();
		pData->Unlock();
	}
	void releasebuffer()
	{
		SetLength( _ucStrlen( m_pszData ));
	}
	void releasebuffer(int len)
	{
		SetLength(len);
	}
	void setat( int iChar, char ch )
	{
		assert( (iChar >= 0) && (iChar < size()) );

		if( (iChar < 0) || (iChar >= size()) )
			return;

		int nLength = size();
		char * pszBuffer = buffer();
		pszBuffer[iChar] = ch;
		releasebuffer( nLength );

	}
	UCAPI void clear() throw();
	UCAPI static void Concatenate( uSimpleString& strResult, const char * psz1, int nLength1, const char * psz2, int nLength2 );
protected:
	UCAPI void Append( const char * pszSrc, int nLength );
	UCAPI uSimpleString( const char * pszSrc);
	UCAPI uSimpleString( const char* pchSrc, int nLength);
	
	uSimpleString() throw()
	{
		uStringData* pData = GetNilString();
		Attach( pData );
	}
	uSimpleString( const uSimpleString& strSrc )
	{
		uStringData* pSrcData = strSrc.GetData();
		uStringData* pNewData = CloneData( pSrcData );
		Attach( pNewData );
	}

	~uSimpleString() throw()
	{
		uStringData* pData = GetData();
		pData->Release();
	}

	uSimpleString& operator=( const uSimpleString& strSrc)
	{
		uStringData* pOldData = GetData();
		if(pOldData!=strSrc.GetData())
		{
			pOldData->Release();
			uStringData* pSrcData = strSrc.GetData();
			uStringData* pNewData = CloneData( pSrcData );
			Attach( pNewData );
		}
		return( *this );
	}
	uSimpleString& operator=( const char * pszSrc )
	{
		SetString( pszSrc );
		return( *this );
	}
	uSimpleString& operator+=( const char * pszSrc )
	{
		Append( pszSrc );
		return( *this );
	}
	uSimpleString& operator+=( char ch )
	{
		AppendChar( char( ch ) );
		return( *this );
	}
	// Implementation
private:
	void Append( const char * pszSrc )
	{
		Append( pszSrc, _ucStrlen( pszSrc ) );
	}

	void AppendChar( char ch )
	{
		unsigned int nOldLength = size();
		int nNewLength = nOldLength+1;
		char * pszBuffer = buffer( nNewLength );
		pszBuffer[nOldLength] = ch;
		releasebuffer( nNewLength );
	}
	void Attach( uStringData* pData ) throw()
	{
		m_pszData = static_cast< char * >( pData->data() );
	}
	uStringData* GetData() const throw()
	{
		return( reinterpret_cast< uStringData* >( m_pszData )-1 );
	}
	void SetLength( int nLength )
	{
		assert( nLength >= 0 );
		assert( nLength <= GetData()->nAllocLength );

		if( nLength < 0 || nLength > GetData()->nAllocLength)
			return;

		GetData()->nDataLength = nLength;
		m_pszData[nLength] = 0;
	}
	void SetString( const char * pszSrc )
	{
		SetString( pszSrc, _ucStrlen( pszSrc ) );
	}

	UCAPI static uStringData* CloneData( uStringData* pData );
	UCAPI char * PrepareWrite( int nLength );
	UCAPI void Fork( int nLength );
	UCAPI void SetString( const char * pszSrc, int nLength );

private:
	char * m_pszData;
};

class uString : public uSimpleString
{
public:
	uString() throw()
	{
	}
	uString( const uString& strSrc ) : uSimpleString( strSrc )
	{
	}
	uString( const char* pszSrc )
	{
		*this = pszSrc;
	}
	uString( const char* pch, int nLength ) : uSimpleString( pch, nLength)
	{
		releasebuffer();
	}
	// Destructor
	~uString() throw()
	{
	}

	// Assignment operators
	uString& operator=( const uString& strSrc )
	{
		uSimpleString::operator=( strSrc );
		return( *this );
	}

	uString& operator=( const char * pszSrc )
	{
		uSimpleString::operator=( pszSrc );
		return( *this );
	}

	uString& operator=( char ch )
	{
		char ach[2] = { ch, 0 };
		return( operator=( ach ) );
	}

	uString& operator+=( const char * pszSrc )
	{
		uSimpleString::operator+=( pszSrc );
		return( *this );
	}

	uString& operator+=( char ch )
	{
		uSimpleString::operator+=( ch );
		return( *this );
	}
	// Comparison

	int compare( const char * psz ) const throw()
	{
		assert( psz );
		return( _ucStrcmp( c_str(), psz ) );
	}

	int comparenocase( const char * psz ) const throw()
	{
		return( _ucStricmp( c_str(), psz ) );
	}

	// Advanced manipulation

	UCAPI int		erase( int iIndex, int nCount /*= 1*/ );
	UCAPI int		insert( int iIndex, char ch );
	UCAPI int		insert( int iIndex, const char * psz );
	UCAPI int		replace( char chOld, char chNew );
	UCAPI int		replace( const char * pszOld, const char * pszNew );
	UCAPI int		find( const char * pszSub, int iStart = 0 ) const throw();
	UCAPI int		rfind(const char * str,int pos=-1) const;
	UCAPI uString	substr( int iFirst, int nCount ) const;
	UCAPI uString&	trimright();
	UCAPI uString&	trimleft();
	UCAPI uString&	format(const char * fmt, ...);

	// manipulation

	//  Delete charactor(s) from iIndex to the end
	int erase(int iIndex)
	{
		if(iIndex<0) iIndex=0;
		return erase(iIndex, size()-iIndex);
	}
	
	uString& makeupper()
	{
		int nLength = size();
		char * pszBuffer = buffer( nLength );
		_ucStrUppercase( pszBuffer );
		releasebuffer( nLength );

		return( *this );
	}

	// Convert the string to lowercase
	uString& makelower()
	{
		int nLength = size();
		char * pszBuffer = buffer( nLength );
		_ucStrLowercase( pszBuffer );
		releasebuffer( nLength );

		return( *this );
	}

	// Remove all leading and trailing whitespace
	uString& trim()
	{
		return( trimright().trimleft() );
	}

	// Return the substring starting at index 'iFirst'
	uString substr( int iFirst ) const
	{
		return( substr( iFirst, size()-iFirst ) );
	}



	friend bool operator==( const uString& str1, const uString& str2 ) throw()
	{
		return( str1.compare( str2 ) == 0 );
	}

	friend bool operator==(const uString& str1, const char * psz2 ) throw()
	{
		return( str1.compare( psz2 ) == 0 );
	}

	friend bool operator==(const char * psz1, const uString& str2 ) throw()
	{
		return( str2.compare( psz1 ) == 0 );
	}

	friend bool operator!=( const uString& str1, const uString& str2 ) throw()
	{
		return( str1.compare( str2 ) != 0 );
	}

	friend bool operator!=(const uString& str1, const char * psz2 ) throw()
	{
		return( str1.compare( psz2 ) != 0 );
	}

	friend bool operator!=(const char * psz1, const uString& str2 ) throw()
	{
		return( str2.compare( psz1 ) != 0 );
	}

	friend bool operator<( const uString& str1, const uString& str2 ) throw()
	{
		return( str1.compare( str2 ) < 0 );
	}

	friend bool operator<( const uString& str1, const char * psz2 ) throw()
	{
		return( str1.compare( psz2 ) < 0 );
	}

	friend bool operator<( const char * psz1, const uString& str2 ) throw()
	{
		return( str2.compare( psz1 ) > 0 );
	}

	friend bool operator>( const uString& str1, const uString& str2 ) throw()
	{
		return( str1.compare( str2 ) > 0 );
	}

	friend bool operator>( const uString& str1, const char * psz2 ) throw()
	{
		return( str1.compare( psz2 ) > 0 );
	}

	friend bool operator>( const char * psz1, const uString& str2 ) throw()
	{
		return( str2.compare( psz1 ) < 0 );
	}

	friend bool operator<=( const uString& str1, const uString& str2 ) throw()
	{
		return( str1.compare( str2 ) <= 0 );
	}

	friend bool operator<=( const uString& str1, const char * psz2 ) throw()
	{
		return( str1.compare( psz2 ) <= 0 );
	}

	friend bool operator<=( const char * psz1, const uString& str2 ) throw()
	{
		return( str2.compare( psz1 ) >= 0 );
	}

	friend bool operator>=( const uString& str1, const uString& str2 ) throw()
	{
		return( str1.compare( str2 ) >= 0 );
	}

	friend bool operator>=( const uString& str1, const char * psz2 ) throw()
	{
		return( str1.compare( psz2 ) >= 0 );
	}

	friend bool operator>=( const char * psz1, const uString& str2 ) throw()
	{
		return( str2.compare( psz1 ) <= 0 );
	}
};

inline uString operator+( const uString& str1, const uString& str2 )
{
	uString strResult;
	uSimpleString::Concatenate( strResult, str1, str1.size(), str2, str2.size() );
	return( strResult );
}

inline uString operator+( const uString& str1, const char * psz2 )
{
	uString strResult;
	uSimpleString::Concatenate( strResult, str1, str1.size(), psz2, _ucStrlen( psz2 ) );
	return( strResult );
}

inline uString operator+( const char * psz1, const uString& str2 )
{
	uString strResult;
	uSimpleString::Concatenate( strResult, psz1, _ucStrlen( psz1 ), str2, str2.size() );
	return( strResult );
}

inline uString operator+( const uString& str1, char ch2 )
{
	uString strResult;
	char chTemp = char( ch2 );
	uSimpleString::Concatenate( strResult, str1, str1.size(), &chTemp, 1 );
	return( strResult );
}

inline uString operator+( char ch1, const uString& str2 )
{
	uString strResult;
	char chTemp = char( ch1 );
	uSimpleString::Concatenate( strResult, &chTemp, 1, str2, str2.size() );
	return( strResult );
}

UCAPI uString btoxa(const uByte * pb, int len);
UCAPI bool xatob(const char * xs, uByte * pb, int len);
UCAPI t_uint64 atoui64(const char * str);
UCAPI uString ui64toa(const t_uint64 ui);
UCAPI t_int64 atoi64(const char * str);
UCAPI uString i64toa(const t_int64 ui);


template<class BinType>
uString btoxa(const BinType & bt)
{
	return btoxa((uByte *)&bt, sizeof(bt));
}

template<class TBin>
bool xatob(const char * xs,TBin & ret)
{
	memset(&ret, 0, sizeof(TBin));
	int len=_ucStrlen(xs);

	if(len>sizeof(TBin)*2)
		len = sizeof(TBin)*2;

	return xatob(xs, (uByte*)&ret, sizeof(TBin));
}


#endif //__UC_STRING_HEADER_FILE__
