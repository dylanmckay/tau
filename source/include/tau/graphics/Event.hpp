#pragma once

#include "forward.hpp"
#include "input/forward.hpp"


namespace tau
{
    namespace graphics
    {
        /*!
         * Base event class.
         */
        class Event
        {

        public:

            /*!
             * The type of an event.
             * Upon adding an event type, make sure to update EventListener::handleEvent.
             */
            enum class Type
            {
                Custom,    // A user-defined event.
                MouseMove, // A mouse move event.
                Keyboard   // A keyboard event.
            };

            virtual ~Event() { }

            /*!
             * Gets the type of the event.
             */
            virtual Event::Type getEventType() const = 0;
        };

    }
}
