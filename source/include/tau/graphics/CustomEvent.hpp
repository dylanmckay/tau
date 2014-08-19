#pragma once

#include "Event.hpp"

namespace tau
{
    namespace graphics
    {
        /*!
         * Represents a custom event.
         */
        class CustomEvent : public Event
        {

        public:

            virtual ~CustomEvent();

            Event::Type getEventType() const override
            {
                return Event::Type::Custom;
            }

        };
    }
}
