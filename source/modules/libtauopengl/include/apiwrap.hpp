#pragma once

/*!
 * apiwrap.hpp
 *
 * Wrapper class around OpenGL functions. Tau scalars can be compiled as a single or
 * double precision floating point decimal, as such, this file wraps (hopefully) all the
 * [platform independent] OpenGL functions which the library uses which have both float and double versions.
 */

#include <tau/math/Scalar.hpp>
#include <tau/math/Vector3.hpp>
#include <tau/math/Matrix4.hpp>
#include <tau/compiler.hpp>


#include <GL/gl.h>


namespace tau
{
    namespace graphics
    {
        namespace opengl
        {
            /*!
             * Alias for glVertex(x,y,z).
             */
            inline void tglVertex(const math::Vector3& v)
            {
#if defined(TAU_SCALAR_DOUBLE)
                glVertex3d(v.getX(), v.getY(), v.getZ());
#else
                glVertex3f(v.getX(), v.getY(), v.getZ());
#endif
            }

            inline void tglVertex(math::Scalar x, math::Scalar y, math::Scalar z)
            {
#if defined(TAU_SCALAR_DOUBLE)
                glVertex3d(x, y, z);
#else
                glVertex3f(x, y, z);
#endif
            }

            inline void tglColor(const ColorF& color)
            {
                // Colors are floating-point values.
                glColor4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
            }

            inline void tglLoadMatrix(const math::Matrix4& matrix)
            {
#if defined(TAU_SCALAR_DOUBLE)
                glLoadTransposeMatrixd((const double*)matrix.getData());
#else
                glLoadTransposeMatrixf((const float*)matrix.getData());
#endif
            }

            inline void tglMultMatrix(const math::Matrix4& matrix)
            {
#if defined(TAU_SCALAR_DOUBLE)
                    glMultTransposeMatrixd((const double*)matrix.getData());
#else
                    glMultTransposeMatrixf((const float*)matrix.getData());
#endif
            }

            inline void tglLineWidth(math::Scalar s)
            {
                // no double version.
                glLineWidth(s);
            }
        }
    }
}
