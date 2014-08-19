#include "../include/OpenGLVideoDriver.hpp"

#include <tau/math/LineSegment3.hpp>

#include "../include/apiwrap.hpp"


using namespace tau;
using namespace tau::graphics;
using namespace tau::graphics::opengl;











OpenGLVideoDriver::OpenGLVideoDriver() : m_backColor(ColorF::FromRGB(179,214,242))
{

    glClearColor(m_backColor.getRed(), m_backColor.getGreen(), m_backColor.getBlue(), m_backColor.getAlpha());
}

void OpenGLVideoDriver::clear(bool backBuffer, bool zBuffer)
{
    // Check if both args are false.
    if((!backBuffer) && (!zBuffer))
        return;


    GLbitfield mask;

    mask = (backBuffer ? GL_COLOR_BUFFER_BIT : 0) | (zBuffer ? GL_DEPTH_BUFFER_BIT : 0);

    glClearColor(m_backColor.getRed(), m_backColor.getGreen(), m_backColor.getBlue(), m_backColor.getAlpha());
    glClear(mask);
}

void OpenGLVideoDriver::drawLineSegment3(const math::LineSegment3& line, const ColorF& color, math::Scalar lineWidth)
{
    tglLineWidth(lineWidth);
    glBegin(GL_LINES);
    {
        tglColor(color);

        tglVertex(line.getPoint1());
        tglVertex(line.getPoint2());
    }
    glEnd();
}

void OpenGLVideoDriver::setViewMatrix(const math::Matrix4& mat)
{
    glMatrixMode(GL_MODELVIEW);
    tglMultMatrix(mat);
}

void OpenGLVideoDriver::setProjectionMatrix(const math::Matrix4& mat)
{
    glMatrixMode(GL_PROJECTION);
    tglLoadMatrix(mat);
}

void OpenGLVideoDriver::setBackgroundColor(const ColorF& color)
{
    m_backColor = color;
}

ColorF OpenGLVideoDriver::getBackgroundColor() const
{
    return m_backColor;
}
