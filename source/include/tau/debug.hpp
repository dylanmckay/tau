#pragma once


/*!
 * debug.h - Tau debugging functions.
 *
 * In debug builds, RTTI should be turned on.
 * In release builds, both RTTI and exceptions should be turned off.
 *
 */

#include "String.hpp"

#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <csignal>




// Comment the next line to disable Tau debugging.
#define TAU_DEBUG


// Debugging is enabled.
#if defined(TAU_DEBUG)

// Define the assertion macro.
#define TauAssert(expr) TauDoAssert(expr, #expr, __FILE__, __func__, __LINE__)

#else // No debugging.
#define TauAssert(expr)
#endif // defined(TAU_DEBUG)

namespace tau
{
    /*!
     * Terminates the program in an error state.
     */
    inline void terminate()
    {
        std::exit(EXIT_FAILURE);
    }

    inline void crash()
    {
        std::raise(SIGINT);
    }

    inline void TauDoAssert(bool expression, const String& msg, const String& file, const String& func, unsigned int line)
    {
        if(!expression)
        {
            // proper crash handling.
            std::cerr << "tau_assert: " << file << ":" << line << ", " << func << "(): assertion '" << msg << "' failed" << std::endl;
            crash();
        }
    }

    /*!
     * Called when a fatal bug is found.
     */
    inline void TauFatalBug(const String& msg)
    {
        std::cerr << "tau_fatal_bug: " << msg << std::endl;
        crash();
    }

    inline void TauUnimplemented()
    {
        TauFatalBug("unimplemented");
    }

    template<typename T>
    inline void TauUnimplemented(T target)
    {
        TauFatalBug(String("object '") + typeid(target).name() + "' not implemented");
    }
}
