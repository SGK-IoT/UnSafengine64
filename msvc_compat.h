#ifndef MSVC_COMPAT_H
#define MSVC_COMPAT_H

// MSVC compatibility header for Intel Pin tools
// Fixes incompatibilities between Pin's Linux-based CRT and MSVC

#ifdef _MSC_VER

// Disable specific MSVC warnings
#pragma warning(disable: 4530) // C++ exception handler used, but unwind semantics are not enabled
#pragma warning(disable: 4577) // 'noexcept' used with no exception handling mode specified
#pragma warning(disable: 4091) // 'typedef ': ignored on left of '' when no variable is declared
#pragma warning(disable: 4146) // unary minus operator applied to unsigned type

// Include standard Windows headers first
#include <windows.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// Define GCC-style keywords for MSVC
#ifndef __signed__
#define __signed__ signed
#endif

#ifndef __inline__
#define __inline__ __inline
#endif

#ifndef __attribute__
#define __attribute__(x)
#endif

// Forward declare types that Pin's CRT expects
#ifndef _WINT_T_DEFINED
#define _WINT_T_DEFINED
typedef unsigned int wint_t;
#endif

#ifndef _WCTYPE_T_DEFINED
#define _WCTYPE_T_DEFINED
typedef int wctype_t;
#endif

#ifndef _WCTRANS_T_DEFINED
#define _WCTRANS_T_DEFINED
typedef int wctrans_t;
#endif

#ifndef _DEV_T_DEFINED
#define _DEV_T_DEFINED
typedef unsigned long long dev_t;
#endif

// Standard C library function declarations (prevent Pin CRT from declaring them)
#ifdef __cplusplus
extern "C" {
#endif

// Character classification functions
_Check_return_ int __cdecl isalnum(_In_ int _C);
_Check_return_ int __cdecl isalpha(_In_ int _C);
_Check_return_ int __cdecl iscntrl(_In_ int _C);
_Check_return_ int __cdecl isdigit(_In_ int _C);
_Check_return_ int __cdecl isgraph(_In_ int _C);
_Check_return_ int __cdecl islower(_In_ int _C);
_Check_return_ int __cdecl isprint(_In_ int _C);
_Check_return_ int __cdecl ispunct(_In_ int _C);
_Check_return_ int __cdecl isspace(_In_ int _C);
_Check_return_ int __cdecl isupper(_In_ int _C);
_Check_return_ int __cdecl isxdigit(_In_ int _C);
_Check_return_ int __cdecl tolower(_In_ int _C);
_Check_return_ int __cdecl toupper(_In_ int _C);

// Wide character functions
_Check_return_ wint_t __cdecl btowc(_In_ int _C);
_Check_return_ wint_t __cdecl fgetwc(_Inout_ FILE* _Stream);
_Check_return_ wint_t __cdecl fputwc(_In_ wint_t _C, _Inout_ FILE* _Stream);
_Check_return_ wint_t __cdecl getwc(_Inout_ FILE* _Stream);
_Check_return_ wint_t __cdecl getwchar(void);
_Check_return_ wint_t __cdecl putwc(_In_ wint_t _C, _Inout_ FILE* _Stream);
_Check_return_ wint_t __cdecl putwchar(_In_ wint_t _C);
_Check_return_ wint_t __cdecl towlower(_In_ wint_t _C);
_Check_return_ wint_t __cdecl towupper(_In_ wint_t _C);
_Check_return_ wint_t __cdecl ungetwc(_In_ wint_t _C, _Inout_ FILE* _Stream);
_Check_return_ wint_t __cdecl towctrans(_In_ wint_t _C, _In_ wctrans_t _Trans);

#ifdef __cplusplus
}
#endif

// Prevent Pin's STLport from trying to use problematic features
#define _STLP_NO_WCHAR_T
#define _STLP_NO_NATIVE_WIDE_STREAMS
#define _STLP_USE_MSVC_CTYPE

// Make sure std:: namespace has these functions available
namespace std {
    using ::tolower;
    using ::toupper;
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
}

// Additional compatibility macros for Pin CRT headers
#define WINT_MIN 0
#define WINT_MAX ((wint_t)-1)

#endif // _MSC_VER
#endif // MSVC_COMPAT_H
