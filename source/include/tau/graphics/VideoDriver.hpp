#pragma once

#include "ColorF.hpp"
#include "../math/LineSegment3.hpp"
#include "../math/forward.hpp"

namespace tau
{
    namespace graphics
    {
        class VideoDriver
        {

        public:

            /*!
             * Destroys the video driver.
             */
            virtual ~VideoDriver() { }


            /*!
             * Prepares for a render of the scene.
             * \note This clears the current view matrix.
             */
            virtual void beginScene(bool clearBackBuffer = true, bool clearZBuffer = true) = 0;

            /*!
             * Finishes rendering the scene.
             */
            virtual void endScene() = 0;

            /*!
             * Clears the back buffer and/or the Z buffer.
             */
            virtual void clear(bool backBuffer = true, bool zBuffer = true) = 0;

            /*!
             * Draws a line.
             */
            virtual void drawLineSegment3(const math::LineSegment3& line, const ColorF& color = White, const math::Scalar lineWidth = 1) = 0;

            inline void drawLineSegment3(const math::Vector3& p1, const math::Vector3& p2, const ColorF color = White, math::Scalar lineWidth = 1)
            {
                drawLineSegment3(math::LineSegment3(p1, p2),color, lineWidth);
            }

            virtual void setViewMatrix(const math::Matrix4& mat) = 0;

            /*!
             * Sets the transformation matrix.
             */
            virtual void setProjectionMatrix(const math::Matrix4& mat) = 0;

            /*!
             * Sets the scene background color.
             */
            virtual void setBackgroundColor(const ColorF& color) = 0;

            /*!
             * Gets the scene background color.
             */
            virtual ColorF getBackgroundColor() const = 0;
        };
    }
}
