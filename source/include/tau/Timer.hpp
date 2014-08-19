#pragma once

#include "math/Scalar.hpp"

namespace tau
{
    /*!
     * A millisecond-resolution timer.
     */
    class Timer
    {

    public:

        /*!
         * Creates a new timer.
         */
        Timer();

        /*!
         * Marks the current time, so the next call to mark() or getDelta() will get the time since the last call to this.
         * \return The number of seconds since the last call to this function or since the object was constructed, whichever was last.
         */
        math::Scalar mark();

        /*!
         * Gets the number of seconds passed since the currently marked time.
         * \return The number of seconds passed.
         */
        math::Scalar getDelta() const;

    public:

        unsigned int m_marked; // The millisecond of the current marked time.


    };
}
