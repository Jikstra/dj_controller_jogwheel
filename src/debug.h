#ifndef __DEBUG_H_INCLUDED__
#define __DEBUG_H_INCLUDED__

#ifdef DEBUG 
  #define IFDEBUG(x) x
  #define IFNDEBUG(x)
#else 
  #define IFDEBUG(x)
  #define IFNDEBUG(x) x
#endif

#endif
