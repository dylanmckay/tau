#pragma once

#include "../Event.hpp"

#include "../../math/Position2.hpp"

namespace tau
{
    namespace graphics
    {
        namespace input
        {
            /*!
             * Occurs when a mouse is moved.
             */
            class MouseMoveEvent : public Event
            {

            public:

                inline MouseMoveEvent(const math::Position2& oldPos,
                                      const math::Position2& pos) :
                                      m_oldPositon(oldPos),
                                      m_position(pos)
                {

                }

                Event::Type getEventType() const override
                {
                    return Event::Type::MouseMove;
                }

                inline const math::Position2& getOldPosition() const
                {
                    return m_oldPositon;
                }

                inline const math::Position2& getPosition() const
                {
                    return m_position;
                }

                inline math::Position2 getDelta() const
                {
                    return m_position - m_oldPositon;
                }

            private:

                math::Position2 m_oldPositon;
                math::Position2 m_position;



            };
        }

    }
}




