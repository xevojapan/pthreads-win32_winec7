#include <winbase.h>
#include "posix_winec7.h"

static __int64 _onesec_in100ns = (__int64)10000000;

static FILETIME wce_getFILETIMEFromYear(WORD year)
{
	SYSTEMTIME s={0};
	FILETIME f;

	s.wYear      = year;
	s.wMonth     = 1;
	s.wDayOfWeek = 1;
	s.wDay       = 1;
	s.wMilliseconds = 500;

	SystemTimeToFileTime( &s, &f );
	return f;
}

static __int64 wce_FILETIME2int64(FILETIME f)
{
	__int64 t;

	t = f.dwHighDateTime;
	t <<= 32;
	t |= f.dwLowDateTime;
	return t;
}

static time_t wce_FILETIME2time_t(const FILETIME* f)
{
	FILETIME f1601, f1970;
	__int64 t, offset;

	f1601 = wce_getFILETIMEFromYear(1601);
	f1970 = wce_getFILETIMEFromYear(1970);

	offset = wce_FILETIME2int64(f1970) - wce_FILETIME2int64(f1601);

	t = wce_FILETIME2int64(*f);

	t -= offset;
	return (time_t)(t / _onesec_in100ns);
}



int winec7_ftime(struct timeb *tp){
	SYSTEMTIME s;
	FILETIME   f;

	GetLocalTime(&s);
	SystemTimeToFileTime( &s, &f );
	s.wMilliseconds = 500;/// no milliseconds, someone could complain
	tp->time     = wce_FILETIME2time_t(&f);
	tp->millitm  = s.wMilliseconds; 

	return 0;
}
     