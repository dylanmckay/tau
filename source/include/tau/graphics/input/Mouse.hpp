#pragma once

#include "../../math/Position2.hpp"

namespace tau
{
    namespace graphics
    {
        namespace input
        {
            class Mouse
            {

            public:

                virtual ~Mouse() { }

                virtual const math::Position2& getPosition() const = 0;

                virtual void setPosition(const math::Position2& pos) = 0;
            };
        }
    }
}
