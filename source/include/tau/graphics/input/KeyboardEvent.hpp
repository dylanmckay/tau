#pragma once

#include "../Event.hpp"

#include "Key.hpp"

namespace tau
{
    namespace graphics
    {
        namespace input
        {
            class KeyboardEvent : public Event
            {

            public:

                inline KeyboardEvent(Key key, bool released = false) : m_key(key), m_released(released)
                {

                }

                Event::Type getEventType() const override
                {
                    return Event::Type::Keyboard;
                }

                inline Key getKey() const
                {
                    return m_key;
                }

                inline bool wasReleased() const
                {
                    return m_released;
                }


            private:

                Key m_key;
                bool m_released;


            };
        }
    }
}
