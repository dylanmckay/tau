#pragma once

#include "forward.hpp"
#include "input/forward.hpp"
#include "../math/Dimension2.hpp"
#include "../math/Position2.hpp"
#include "Event.hpp"

namespace tau
{
    namespace graphics
    {
        class TauDevice
        {

        public:

            /*!
             * Creates a new Tau device.
             */
            static TauDevice* Create();

            /*!
             * Creates a new Tau device.
             */
            TauDevice();

            /*!
             * Destroys the device.
             */
            virtual ~TauDevice() { }


            /*!
             * Runs the device.
             */
            virtual void run() = 0;

            /*!
             * Gets a value indicating whether the driver is still running.
             */
            virtual bool isRunning() const = 0;

            /*!
             * Sets the listener that will listen to events on the device.
             * \param listener The listener, can be null.
             */
            void setListener(EventListener* listener);

            /*!
             * Gets the listener that is listening on the device, or null if there is no listener.
             */
            inline EventListener* getListener() { return m_listener; }

            /*!
             * Dispatches an event.
             */
            bool dispatchEvent(const Event& event);

            /*!
             * Gets the size of the drawable area in pixels.
             */
            virtual const math::Dimension2u& getSize() const = 0;

            /*!
             * Gets the video driver associated with the device.
             */
            virtual VideoDriver* getVideoDriver() = 0;

            /*!
             * Gets the scene manager.
             */
            virtual SceneManager* getSceneManager() = 0;

            /*!
             * Gets the mouse object for the driver, or null if no mouse exists.
             */
            virtual input::Mouse* getMouse() { return nullptr; }

            /*!
             * Converts the given 2 dimensional position to a 2 dimensional pixel position.
             */
            inline math::Position2u convertPosition2ToPixel(const math::Position2& pos) const
            {
                const math::Dimension2u& size = getSize();

                return math::Position2u((size.getWidth()/2) * (pos.getX()+1), (size.getHeight()/2) * (pos.getY()+1));
            }

            inline math::Position2 convertPixelToPosition2(const math::Position2u& pos) const
            {
                using namespace tau::math;

                const math::Dimension2u& size = getSize();

                Scalar pixelX = (Scalar)pos.getX();
                Scalar pixelY = (Scalar)pos.getY();

                Scalar width = (Scalar)size.getWidth();
                Scalar height = (Scalar)size.getHeight();

                return math::Position2((pixelX / (width / 2)) - 1, (pixelY / (height/2)) - 1);
            }

        private:

            EventListener* m_listener;

        };
    }
}
