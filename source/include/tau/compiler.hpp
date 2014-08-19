#pragma once

/*
 * Check that we are using a C++ compiler.
 */
#if !defined(__cplusplus)
#error a C++ compiler must be used.
#endif

/*
 * Check if we have at least C++11, note that an actual version value
 * is a requirement of the standard unlike before, for example GCC < 4.7
 * would just define __cplusplus to 1.
 */
#if __cplusplus < 201103L
#error C++11 not supported, required for Tau.
#endif


#if defined(__GNUC__) // Check for GCC.

#define tau_forceinline         __attribute__((always_inline))
#define tau_packed              __attribute__((packed))
#define tau_deprecated          __attribute__((deprecated))
#define tau_deprecated_msg(msg) __attribute__((deprecated(msg)))


#else // Unknown compiler.
#error unknown compiler
#endif
