#ifndef MSVC_COMPAT_H
#define MSVC_COMPAT_H

// MSVC compatibility header for Intel Pin tools
// This header must be included BEFORE any Pin headers

#ifdef _MSC_VER

// Disable problematic MSVC warnings
#pragma warning(disable: 4530)
#pragma warning(disable: 4577)
#pragma warning(disable: 4091)
#pragma warning(disable: 4146)

// ============================================================================
// CRITICAL: Define GCC keywords BEFORE Pin headers see them
// ============================================================================
#ifndef __signed__
#define __signed__ signed
#endif

#ifndef __inline__
#define __inline__ __inline
#endif

#ifndef __attribute__
#define __attribute__(x)
#endif

// ============================================================================
// Pre-declare types that Pin's CRT will try to define incorrectly
// ============================================================================

// Prevent Pin's CRT from trying to declare these types
#define _WINT_T_DEFINED
#define _WCTYPE_T_DEFINED  
#define _WCTRANS_T_DEFINED
#define _DEV_T_DEFINED

// Now provide the actual type definitions
#ifndef _WINT_T
#define _WINT_T
typedef unsigned short wint_t;
#endif

#ifndef _WCTYPE_T
#define _WCTYPE_T
typedef unsigned short wctype_t;
#endif

#ifndef _WCTRANS_T
#define _WCTRANS_T
typedef unsigned short wctrans_t;
#endif

#ifndef _DEV_T
#define _DEV_T
typedef unsigned int dev_t;
#endif

// ============================================================================
// Forward declare FILE type (don't include stdio.h yet)
// ============================================================================
#ifndef _FILE_DEFINED
#define _FILE_DEFINED
struct _iobuf;
typedef struct _iobuf FILE;
#endif

// ============================================================================
// Declare standard C library functions BEFORE Pin's CRT tries to
// ============================================================================
#ifdef __cplusplus
extern "C" {
#endif

// Character classification - use __cdecl calling convention
int __cdecl isalnum(int);
int __cdecl isalpha(int);
int __cdecl iscntrl(int);
int __cdecl isdigit(int);
int __cdecl isgraph(int);
int __cdecl islower(int);
int __cdecl isprint(int);
int __cdecl ispunct(int);
int __cdecl isspace(int);
int __cdecl isupper(int);
int __cdecl isxdigit(int);
int __cdecl tolower(int);
int __cdecl toupper(int);

// Wide character functions
wint_t __cdecl btowc(int);
wint_t __cdecl fgetwc(FILE*);
wint_t __cdecl fputwc(wint_t, FILE*);
wint_t __cdecl getwc(FILE*);
wint_t __cdecl getwchar(void);
wint_t __cdecl putwc(wint_t, FILE*);
wint_t __cdecl putwchar(wint_t);
wint_t __cdecl towlower(wint_t);
wint_t __cdecl towupper(wint_t);
wint_t __cdecl ungetwc(wint_t, FILE*);
wint_t __cdecl towctrans(wint_t, wctrans_t);

#ifdef __cplusplus
}
#endif

// ============================================================================
// Prevent Pin's STLport from trying to use broken features
// ============================================================================
#define _STLP_NO_WCHAR_T
#define _STLP_NO_NATIVE_WIDE_STREAMS
#define _STLP_USE_NO_IOSTREAMS

// Tell Pin's CRT we already have these functions
#define _CTYPE_DEFINED
#define _WCTYPE_INLINE_DEFINED

// ============================================================================
// Ensure std:: namespace has access to these functions
// ============================================================================
#ifdef __cplusplus
namespace std {
    using ::isalnum;
    using ::isalpha;
    using ::iscntrl;
    using ::isdigit;
    using ::isgraph;
    using ::islower;
    using ::isprint;
    using ::ispunct;
    using ::isspace;
    using ::isupper;
    using ::isxdigit;
    using ::tolower;
    using ::toupper;
}
#endif

#endif // _MSC_VER
#endif // MSVC_COMPAT_H
