#include "../../../include/tau/Timer.hpp"

#include <sys/time.h>

using namespace tau;

namespace
{
    unsigned int GetMilliseconds()
    {
        timeval tv;

        gettimeofday(&tv, nullptr);

        return ((tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
    }
}


Timer::Timer()
{
    mark();
}

math::Scalar Timer::mark()
{
    math::Scalar delta = getDelta();

    m_marked = GetMilliseconds();

    return delta;
}

math::Scalar Timer::getDelta() const
{
    return ((double)GetMilliseconds() - (double)m_marked) / 1000;
}
