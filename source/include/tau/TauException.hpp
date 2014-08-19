#pragma once

#include <stdexcept>

#include "String.hpp"

namespace tau
{
    class TauException : public std::exception
    {

    public:

        TauException()
        {

        }

        TauException(const String& message) : m_message(message)
        {

        }

        virtual const String& getMessage() const noexcept
        {
            return m_message;
        }

        const char* what() const noexcept override
        {
            return (const char*)getMessage().getUTF8Data();
        }

    private:

        String m_message;
    };
}
