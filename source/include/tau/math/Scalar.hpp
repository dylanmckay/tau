#pragma once

#include <cmath>
#include <cfloat> //epsilon constant.
#include "../compiler.hpp"


// The precision of the scalar.
// Uncomment the next line for double precision.
// #define TAU_SCALAR_DOUBLE


// Define the TAU_SCALAR_VAL macro which is used to create
// a float or double.
#if defined(TAU_SCALAR_DOUBLE) // check if we're using double precision.
#define TAU_SCALAR_VAL(val) val // - regular double ctor.
#else // Single precision.
#define TAU_SCALAR_VAL(val) ((Scalar)val)// float ctor.
#endif


namespace tau
{
    namespace math
    {

#if defined(TAU_SCALAR_DOUBLE)
        const double ScalarEpsilon = DBL_EPSILON; // double precision.
#else
        const double ScalarEpsilon = FLT_EPSILON; // single precision.
#endif

        /*!
         * A class representing a scalar.
         * This class is a simple wrapper class over float or double, depending on the definition of TAU_SCALAR_VAL.
         * It is intended to be 'nicer' in the fact it has its own '==' and '!=' operators, so it is more intuitive than
         * some variant of IsEqual(Scalar,Scalar). This may not be suitable on certain compilers, however on GCC 4.8, with
         * any optimization level enabled (>= level 1), it is optimized as a float and has no overhead. Testing needs to be done
         * on other compilers.
         */
        class tau_packed Scalar
        {

        public:

            /*!
             * Creates a scalar from the given floating point number.
             */
#if defined(TAU_SCALAR_DOUBLE)
            tau_forceinline Scalar(double val) : m_value(val)
#else
            tau_forceinline Scalar(float val) : m_value(val)
#endif
            {

            }

            /*!
             * Creates a new, uninitialized scalar.
             */
            tau_forceinline Scalar()
            {

            }

            /*!
             * Sets the value of the scalar to the given value.
             */
#if defined(TAU_SCALAR_DOUBLE)
            tau_forceinline Scalar operator=(double val)
#else
            tau_forceinline Scalar operator=(float val)
#endif
            {
                m_value = val;

                return *this;
            }

            /*!
             * Sets the value of the scalar to the given scalar.
             */
            tau_forceinline Scalar operator=(Scalar s)
            {
                m_value = s.m_value;

                return *this;
            }

            /*!
             * Checks if the scalar is approximately equal (using an epsilon value) to the given scalar.
             */
            tau_forceinline bool operator==(Scalar s) const
            {
                return std::abs(this->m_value - s.m_value) <= ScalarEpsilon * std::abs(this->m_value);
            }

            /*!
             * Generic function to check if the scalar is approximately equal (using an epsilon value) to the given value.
             */
            template<typename T>
            tau_forceinline bool operator==(T val) const
            {
#if defined(TAU_SCALAR_DOUBLE)
                return std::abs(this->m_value - ((double)val)) <= ScalarEpsilon * std::abs(this->m_value);
#else
                return std::abs(this->m_value - ((float)val)) <= ScalarEpsilon * std::abs(this->m_value);
#endif
            }

            /*!
             * Checks if the scalar is approximately not equal (using an epsilon value) to the given value.
             */
            tau_forceinline bool operator!=(Scalar s) const
            {
                return std::abs(this->m_value - s.m_value) > ScalarEpsilon * std::abs(this->m_value);
            }

            /*!
             * Generic function to check if the scalar is approximately not equal (using an epsilon value) to the given value.
             */
            template<typename T>
            tau_forceinline bool operator!=(T val) const
            {
#if defined(TAU_SCALAR_DOUBLE)
                return std::abs(this->m_value - ((double)val)) > ScalarEpsilon * std::abs(this->m_value);
#else
                return std::abs(this->m_value - ((float)val)) > ScalarEpsilon * std::abs(this->m_value);
#endif
            }

            tau_forceinline Scalar operator+(Scalar s) const
            {
                return this->m_value + s.m_value;
            }

            tau_forceinline Scalar operator-(Scalar s) const
            {
                return this->m_value - s.m_value;
            }

            tau_forceinline Scalar operator*(Scalar s) const
            {
                return this->m_value * s.m_value;
            }

            tau_forceinline Scalar operator/(Scalar s) const
            {
                return this->m_value / s.m_value;
            }

            template<typename T>
            tau_forceinline Scalar operator+(T val) const
            {
                return this->m_value + val;
            }

            template<typename T>
            tau_forceinline Scalar operator-(T val) const
            {
                return this->m_value - val;
            }

            template<typename T>
            tau_forceinline Scalar operator*(T val) const
            {
                return this->m_value * val;
            }

            template<typename T>
            tau_forceinline Scalar operator/(T val) const
            {
                return this->m_value / val;
            }

            tau_forceinline Scalar operator+=(Scalar s)
            {
                return this->m_value += s.m_value;
            }

            tau_forceinline Scalar operator-=(Scalar s)
            {
                return this->m_value -= s.m_value;
            }

            tau_forceinline Scalar operator*=(Scalar s)
            {
                return this->m_value *= s.m_value;
            }

            tau_forceinline Scalar operator/=(Scalar s)
            {
                return this->m_value /= s.m_value;
            }

            template<typename T>
            tau_forceinline Scalar operator+=(T val)
            {
                return this->m_value += val;
            }

            template<typename T>
            tau_forceinline Scalar operator-=(T val)
            {
                return this->m_value -= val;
            }

            template<typename T>
            tau_forceinline Scalar operator*=(T val)
            {
                return this->m_value *= val;
            }

            template<typename T>
            tau_forceinline Scalar operator/=(T val)
            {
                return this->m_value /= val;
            }

#if defined(TAU_SCALAR_DOUBLE)
            tau_forceinline operator double() const
#else
            tau_forceinline operator float() const
#endif
            {
                return m_value;
            }


        public:

#if defined(TAU_SCALAR_DOUBLE)
            double m_value;
#else
            float m_value;
#endif
        };

        /*!
         * The constant Pi; the ratio of the circumference to the diameter of a circle.
         */
        const Scalar Pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

        /*!
         * A constant which can be multiplied with an angle in degrees to produce the given angle in radians.
         */
        const Scalar DegToRad = Pi/180;

        /*!
         * A constant which can be multiplied with an angle in radians to produce the given angle in degrees.
         */
        const Scalar RadToDeg = 180/Pi;

        inline Scalar ConvertFromLibcAngle(Scalar angle)
        {
            if(angle < 0)
            {
                angle = std::abs(angle);
            }
            else if(angle > 0)
            {
                angle += Pi;
            }

            return angle;
        }

        inline Scalar ConvertToLibcAngle(Scalar angle)
        {
            if(angle < Pi)
            {
                if(angle != 0)
                    angle *= -1;
            }
            else
            {
                angle -= Pi;
            }

            return angle;
        }


        /*!
         * Raises base to the specified power and returns the result.
         */
        inline Scalar power(Scalar base, Scalar exponent)
        {
            return std::pow(base, exponent);
        }

        /*!
         * Raises x to the second power and returns the result.
         */
        inline Scalar square(Scalar x)
        {
            return std::pow(x, TAU_SCALAR_VAL(2));
        }

        /*!
         * Raises x to the third power and returns the result.
         */
        inline Scalar cube(Scalar x)
        {
            return std::pow(x, TAU_SCALAR_VAL(3));
        }

        /*!
         * Gets the n'th root of base.
         */
        inline Scalar root(Scalar base, Scalar n)
        {
            return std::pow(base, TAU_SCALAR_VAL(1)/n);
        }

        /*!
         * Calculates the square root of base.
         */
        inline Scalar squareRoot(Scalar x)
        {
            return std::sqrt(x);
        }

        /*!
         * Calculates the square root of x and returns the reciprocal of the result.
         */
        inline Scalar inverseSquareRoot(Scalar x)
        {
            return TAU_SCALAR_VAL(1)/std::sqrt(x);
        }

        /*!
         * Calculates the cubic root of base/
         */
        inline Scalar cubeRoot(Scalar x)
        {
            return std::cbrt(x);
        }

        /*!
         * Gets the absolute value of x.
         */
        inline Scalar absolute(Scalar x)
        {
            return std::abs(x);
        }

        /*!
         * Rounds x to the nearest integer.
         */
        inline Scalar round(Scalar x)
        {
            return std::round(x);
        }

        /*!
         * Rounds x to the nearest integer that is greater than x.
         */
        inline Scalar ceiling(Scalar x)
        {
            return std::ceil(x);
        }

        /*!
         * Rounds x to the nearest integer that is lower than x.
         */
        inline Scalar floor(Scalar x)
        {
            return std::floor(x);
        }

        /*!
         * Calculates the sine of x (in radians).
         */
        inline Scalar sine(Scalar x)
        {
            return std::sin(ConvertToLibcAngle(x));
        }

        /*!
         * Calculates the cosine of angle x (in radians).
         */
        inline Scalar cosine(Scalar x)
        {
            return std::cos(ConvertToLibcAngle(x));
        }

        /*!
         * Calculates the tangent of angle x (in radians).
         */
        inline Scalar tangent(Scalar x)
        {
            return std::tan(ConvertToLibcAngle(x));
        }

        /*!
         * Calculates the arc sine of x, also known as the inverse sine.
         */
        inline Scalar arcSine(Scalar x)
        {
            return ConvertFromLibcAngle(std::asin(x));
        }

        /*!
         * Calculates the arc cosine of x, also known as the inverse cosine.
         */
        inline Scalar arcCosine(Scalar x)
        {
            return ConvertFromLibcAngle(std::acos(x));
        }

        /*!
         * Calculates the arc tangent of x, also known as the inverse tangent.
         */
        inline Scalar arcTangent(Scalar x)
        {
            return ConvertFromLibcAngle(std::atan(x));
        }

        inline Scalar arcTangent2(Scalar y, Scalar x)
        {
            return ConvertFromLibcAngle(std::atan2(y, x));
        }

    };
}

