#pragma once

#include "forward.hpp"

namespace tau
{
    namespace graphics
    {
        /*!
         * Listens to events.
         */
        class EventListener
        {

        public:

            virtual ~EventListener() { }

            /*!
             * Called when an event is generated.
             * \param event The event to handle.
             * \return true if the event was handled, false otherwise.
             */
            virtual bool onEvent(TauDevice* device, const Event& event) = 0;

        };
    }
}
