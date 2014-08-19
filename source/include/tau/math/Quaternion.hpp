#pragma once

#include "Scalar.hpp"
#include "Vector3.hpp"

namespace tau
{
    namespace math
    {

        class Quaternion
        {

        public:

            /*!
             * Creates a new quaternion from the given euler rotation vector in radians.
             */
            static Quaternion FromEulerRadians(const Vector3& rot);

            static inline Quaternion FromEulerDegrees(const Vector3& rot)
            {
                return FromEulerRadians(rot * RadToDeg);
            }

            Quaternion(Scalar x=0, Scalar y=0, Scalar z=0, Scalar w = 1) : m_x(x), m_y(y), m_z(z), m_w(w)
            {

            }

            /*!
             * Converts the quaternion to a rotation matrix.
             */
            //Matrix4 toRotationMatrix();

            void normalize();

            inline Quaternion getNormalized() const
            {
                Quaternion copy(*this);

                copy.normalize();

                return copy;
            }

            Vector3 rotateVector(const Vector3& vec);

            Quaternion getConjugate() const
            {
                return Quaternion(-m_x, -m_y, -m_z, m_w);
            }

            void setX(Scalar x)
            {
                m_x = x;
            }

            void setY(Scalar y)
            {
                m_y = y;
            }

            void setZ(Scalar z)
            {
                m_z = z;
            }

            void setW(Scalar w)
            {
                m_w = w;
            }


            inline Scalar getX() const
            {
                return m_x;
            }

            inline Scalar getY() const
            {
                return m_y;
            }

            inline Scalar getZ() const
            {
                return m_z;
            }

            inline Scalar getW() const
            {
                return m_w;
            }

            Quaternion operator*(const Quaternion& quat) const
            {
                Quaternion result;

                result.m_x = this->m_w*quat.m_x + this->m_x*quat.m_w + this->m_y*quat.m_z - this->m_z*quat.m_y;
                result.m_y = this->m_w*quat.m_y - this->m_x*quat.m_z + this->m_y*quat.m_w + this->m_z*quat.m_x;
                result.m_z = this->m_w*quat.m_z + this->m_x*quat.m_y - this->m_y*quat.m_x + this->m_z*quat.m_w;
                result.m_w = this->m_w*quat.m_w - this->m_x*quat.m_x - this->m_y*quat.m_y - this->m_z*quat.m_z;

                return result;
            }

        private:

            Scalar m_x, m_y, m_z, m_w;
        };
    }
}
