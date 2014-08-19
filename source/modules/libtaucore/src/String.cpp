#include "../../../include/tau/String.hpp"

#include <unicode/bytestream.h>

using namespace tau;


static const unsigned int MaxStringSize = 1024*32; // 32KB.

static char StringBuffer[MaxStringSize]; // An internal buffer to hold strings.



const char* String::getUTF8Data() const
{
    CheckedArrayByteSink sink(StringBuffer, MaxStringSize);

    m_string.toUTF8(sink);

    return StringBuffer;
}
