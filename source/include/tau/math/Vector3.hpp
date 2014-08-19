#pragma once

#include "Scalar.hpp"

namespace tau
{
    namespace math
    {
        /*!
         * TODO: Possibly calculate length and stuff internally wit h a boolean dirty value.
         */
        class Vector3
        {

        public:

            static inline Vector3 FromDegrees(Scalar x, Scalar y, Scalar z)
            {
                return Vector3(x, y, z) * DegToRad;
            }

            static Scalar GetAngleBetween(Scalar x1, Scalar x2)
            {
                Scalar angle = arcTangent2(x1, x2);

                return angle;
            }

            /*!
             * Creates a new null vector.
             */
            inline Vector3() : m_x(0), m_y(0), m_z(0)
            {

            }


            inline Vector3(Scalar x, Scalar y, Scalar z) : m_x(x), m_y(y), m_z(z)
            {

            }

            inline Vector3(const Vector3& vec) : m_x(vec.m_x), m_y(vec.m_y), m_z(vec.m_z)
            {

            }

            /*!
             * Assignment operator.
             */
            inline Vector3& operator=(const Vector3& vec)
            {
                this->m_x = vec.m_x;
                this->m_y = vec.m_y;
                this->m_z = vec.m_z;

                return *this;
            }

            Scalar getLength() const
            {
                return squareRoot((m_x*m_x) + (m_y*m_y) + (m_z*m_z));
            }

            Scalar getLengthSquared() const
            {
                return (m_x*m_x) + (m_y*m_y) + (m_z*m_z);
            }

            void normalize()
            {
                Scalar invLen = inverseSquareRoot((m_x*m_x) + (m_y*m_y) + (m_z*m_z));

                m_x *= invLen;
                m_y *= invLen;
                m_z *= invLen;
            }

            Vector3 getNormalized() const
            {
                Scalar invLen = inverseSquareRoot((m_x*m_x) + (m_y*m_y) + (m_z*m_z));

                return (*this) * invLen;
            }

            Vector3 crossProduct(const Vector3& other) const
            {
                return Vector3(m_y * other.m_z - m_z * other.m_y,
                               m_z * other.m_x - m_x * other.m_z,
                               m_x * other.m_y - m_y * other.m_x);
            }

            Scalar dotProduct(const Vector3& vec) const
            {
                return (this->m_x*vec.m_x) + (this->m_y*vec.m_y) + (this->m_z*vec.m_z);
            }

            /*!
             * Calculates the distance between two vectors.
             */
            Scalar getDistanceBetween(const Vector3& vec) const
            {
                return ((*this) - vec).getLength();
            }

            /*!
             * Gets the angle between the vector and the horizontal x axis (in radians).
             */
            Scalar getVerticalAngle() const
            {
                return GetAngleBetween(m_y, m_x);
            }

            Vector3 rotationToDirection() const
            {
                Scalar x = sine(m_x);
                Scalar y = sine(m_y);
                Scalar z = sine(m_z);

                return Vector3(x,y,z);
            }

            Vector3 directionToRotation() const
            {
                Vector3 n(*this);
                n.normalize();

                Scalar angleX = arcSine(m_x);
                Scalar angleY = arcSine(m_y);
                Scalar angleZ = arcSine(m_z);


                return Vector3(angleX,angleY,angleZ);
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


            /*!
             * Gets the X component of the vector.
             */
            inline Scalar getX() const
            {
                return m_x;
            }

            /*!
             * Gets the Y component of the vector.
             */
            inline Scalar getY() const
            {
                return m_y;
            }

            /*!
             * Gets the Z component of the vector.
             */
            inline Scalar getZ() const
            {
                return m_z;
            }

            /*!
             * Vector addition operator.
             */
            inline Vector3 operator+(const Vector3& vec) const
            {
                return Vector3(this->m_x + vec.m_x,
                               this->m_y + vec.m_y,
                               this->m_z + vec.m_z);
            }

            /*!
             * Vector subtraction operator.
             */
            inline Vector3 operator-(const Vector3& vec) const
            {
                return Vector3(this->m_x - vec.m_x,
                               this->m_y - vec.m_y,
                               this->m_z - vec.m_z);
            }

            /*!
             * Vector multipication operator.
             */
            inline Vector3 operator*(const Vector3& vec) const
            {
                return Vector3(this->m_x * vec.m_x,
                               this->m_y * vec.m_y,
                               this->m_z * vec.m_z);
            }

            /*!
             * Vector + scalar addition operator.
             */
            inline Vector3 operator+(Scalar s) const
            {
                return Vector3(this->m_x + s,
                               this->m_y + s,
                               this->m_z + s);
            }

            /*!
             * Vector - scalar subtraction operator.
             */
            inline Vector3 operator-(Scalar s) const
            {
                return Vector3(this->m_x - s,
                               this->m_y - s,
                               this->m_z - s);
            }

            /*!
             * Vector * scalar multipication operator.
             */
            inline Vector3 operator*(Scalar s) const
            {
                return Vector3(this->m_x * s,
                               this->m_y * s,
                               this->m_z * s);
            }

            /*!
             * Vector / scalar division operator.
             */
            inline Vector3 operator/(Scalar s) const
            {
                return Vector3(this->m_x / s,
                               this->m_y / s,
                               this->m_z / s);
            }


            inline Vector3& operator+=(const Vector3& vec)
            {
                this->m_x += vec.m_x;
                this->m_y += vec.m_y;
                this->m_z += vec.m_z;

                return *this;
            }

            inline Vector3& operator-=(const Vector3& vec)
            {
                this->m_x -= vec.m_x;
                this->m_y -= vec.m_y;
                this->m_z -= vec.m_z;

                return *this;
            }

            inline Vector3& operator*=(const Vector3& vec)
            {
                this->m_x *= vec.m_x;
                this->m_y *= vec.m_y;
                this->m_z *= vec.m_z;

                return *this;
            }

            /*!
             * Vector plus scalar assignment operator.
             */
            inline Vector3& operator+=(Scalar s)
            {
                this->m_x += s;
                this->m_y += s;
                this->m_z += s;

                return *this;
            }

            /*!
             * Vector minus scalar assignment operator.
             */
            inline Vector3& operator-=(Scalar s)
            {
                this->m_x -= s;
                this->m_y -= s;
                this->m_z -= s;

                return *this;
            }

            /*!
             * Vector times scalar assignment operator.
             */
            inline Vector3& operator*=(Scalar s)
            {
                this->m_x *= s;
                this->m_y *= s;
                this->m_z *= s;

                return *this;
            }

            /*!
             * Vector divided by scalar assignment operator.
             */
            inline Vector3& operator/=(Scalar s)
            {
                this->m_x /= s;
                this->m_y /= s;
                this->m_z /= s;

                return *this;
            }



        private:

            Scalar m_x, m_y, m_z;
        };

    }

}

/*!
 * Adds a vector and a scalar.
 */
inline tau::math::Vector3 operator+(tau::math::Scalar s, const tau::math::Vector3& vec)
{
    return tau::math::Vector3(s + vec.getX(), s + vec.getY(), s + vec.getZ());
}

/*!
 * Multiplies a vector and a scalar.
 */
inline tau::math::Vector3 operator*(tau::math::Scalar s, const tau::math::Vector3& vec)
{
    return tau::math::Vector3(s*vec.getX(), s*vec.getY(), s*vec.getZ());
}
