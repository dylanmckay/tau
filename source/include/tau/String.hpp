#pragma once

//#include <string>
#include <unicode/unistr.h>

namespace tau
{
    /*!
     * note that ICU does not use exceptions.
     */
    class String
    {

    public:

        /*!
         * Creates a new empty string.
         */
        inline String() : m_string("")
        {

        }

        inline String(const icu::UnicodeString& str) : m_string(str)
        {

        }

        /*!
         * Creates a new string from the given ASCII or UTF-8 string.
         */
        inline String(const char* str) : m_string(str)
        {

        }

        inline String operator+(const String& str) const
        {
            return String(this->m_string + str.m_string);
        }

        /*!
         * Converts the string to a UTF-8 byte array and returns it.
         * \note The returned array is only guarenteed to hold the string until another call to this function on any String object.
         */
        const char* getUTF8Data() const;

    private:

        icu::UnicodeString m_string;
    };
}

inline std::ostream& operator<< (std::ostream& stream, const tau::String& string)
{
    const char* data = string.getUTF8Data();

    stream << std::string(data);

    return stream;
}
