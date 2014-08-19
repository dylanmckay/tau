#pragma once

#include <tau/graphics/VideoDriver.hpp>

namespace tau
{
    namespace graphics
    {
        namespace opengl
        {
            class OpenGLVideoDriver : public VideoDriver
            {

            public:

                OpenGLVideoDriver();

                virtual ~OpenGLVideoDriver() { }

                void clear(bool backBuffer = true, bool zBuffer = true) override;

                void drawLineSegment3(const math::LineSegment3& line, const ColorF& color, math::Scalar lineWidth = 1) override;

                void setViewMatrix(const math::Matrix4& mat) override;

                void setProjectionMatrix(const math::Matrix4& mat) override;

                void setBackgroundColor(const ColorF& color) override;

                ColorF getBackgroundColor() const override;

            private:

                ColorF m_backColor;
            };
        }
    }
}
