#ifndef WIN_STDINT
#define WIN_STDINT

#if _MSC_VER <= 1500

typedef signed __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

#else

#include <stdint.h>

#endif // visual studio version

#endif