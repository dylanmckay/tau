#pragma once

#include "compiler.hpp"
#include "debug.hpp"

namespace tau
{
    /*!
     * Implements basic reference counting on an object.
     */
    class ReferenceCounted
    {

    public:

        /*!
         * Destroys the reference counted object.
         */
        virtual ~ReferenceCounted()
        {
            // Throw an assertion if the object is deleted manually,
            // before all of its references have been dropped.
            TauAssert(m_references == 0);
        }

        /*!
         * Grabs another reference to the object.
         */
        tau_forceinline void grab()
        {
            m_references++;
        }

        /*!
         * Drops a reference to the object, deleting it if no more references are held.
         */
        tau_forceinline void drop()
        {
            m_references--;

            if(m_references < 1)
                delete this;
        }


    private:

        /*!
         * The number of references that are held to the object.
         * N.B. this could possibly be overkill, it's unlikely 2^64-1 references on 64-bit
         * will be held at any point. Could be size optimized.
         */
        unsigned int m_references;


    };
}
