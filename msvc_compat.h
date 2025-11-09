#ifndef MSVC_COMPAT_H
#define MSVC_COMPAT_H

// MSVC compatibility header for Intel Pin tools
// This header resolves conflicts between Pin's Linux CRT and Windows MSVC

// ============================================================================
// 1. Prevent Pin's CRT from redefining standard types
// ============================================================================

// Define these BEFORE Pin's headers try to define them
#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
#endif

#ifndef _WINT_T
#define _WINT_T
typedef unsigned short wint_t;
#endif

// ============================================================================
// 2. Fix GCC-specific keywords that MSVC doesn't understand
// ============================================================================

// Pin's CRT uses GCC-style __signed__ which MSVC doesn't have
#ifndef __signed__
#define __signed__ signed
#endif

// Inline keyword compatibility
#ifndef __inline__
#define __inline__ __inline
#endif

// ============================================================================
// 3. Provide missing standard library functions
// ============================================================================

// Include Windows CRT headers BEFORE Pin's headers
#include <ctype.h>
#include <wctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Make sure tolower/toupper are available in global namespace
#ifndef tolower
using ::tolower;
using ::toupper;
#endif

// ============================================================================
// 4. Fix Pin's STLport compatibility issues
// ============================================================================

// Ensure these are defined before STLport tries to use them
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

// ============================================================================
// 5. Disable Pin CRT's problematic headers
// ============================================================================

// Prevent Pin's wchar.h from being included (use Windows' instead)
#define _PIN_WCHAR_H_
#define __PIN_WCHAR_H__

// Prevent Pin's Linux kernel headers from being included
#define _ASM_GENERIC_INT_LL64_H
#define _LINUX_TYPES_H
#define __KERNEL_STRICT_NAMES

// ============================================================================
// 6. Windows-specific types that Pin expects
// ============================================================================

#ifndef __dev_t_defined
#define __dev_t_defined
typedef unsigned int dev_t;
#endif

// ============================================================================
// 7. MSVC pragma helpers
// ============================================================================

// Disable specific warnings that Pin triggers with MSVC
#pragma warning(disable: 4530) // C++ exception handler used, but unwind semantics are not enabled
#pragma warning(disable: 4577) // 'noexcept' used with no exception handling mode specified
#pragma warning(disable: 4244) // conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable: 4267) // conversion from 'size_t' to 'type', possible loss of data

#endif // MSVC_COMPAT_H
