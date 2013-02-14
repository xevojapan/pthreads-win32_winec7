#ifndef __POSIX_WINEC7_H__
#define __POSIX_WINEC7_H__

#include <crtdefs.h>



struct timeb{
    time_t         time;
    unsigned short millitm;
};

int winec7_ftime(struct timeb *tp);


#endif //__POSIX_WINEC7_H__