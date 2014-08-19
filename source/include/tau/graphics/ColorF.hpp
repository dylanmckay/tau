#pragma once

#include "../types.hpp"

namespace tau
{
    namespace graphics
    {
        class ColorF
        {

        public:

            /*!
             * Creates a new floating point color object from the given red, green and blue components given in bytes.
             */
            static inline ColorF FromRGB(byte r, byte g, byte b)
            {
                return ColorF((float)r/255, (float)g/255, (float)b/255, 1.0);
            }

            /*!
             * Creates a new floating point color object from the given red, green, blue and alpha components given in bytes.
             */
            static inline ColorF FromRGBA(byte r, byte g, byte b, byte a)
            {
                return ColorF((float)r/255, (float)g/255, (float)b/255, (float)a/255);
            }


            /*!
             * Creates a new color from the given intensity values.
             * \param r The intensity of the red component [0-1].
             * \param g The intensity of the green component [0-1].
             * \param b The intensity of the blue component [0-1].
             * \param a The intensity of the alpha component [0-1], defaults to 1 for fully opaque.
             */
            ColorF(float r, float g, float b, float a = 1.0) : m_r(r), m_g(g), m_b(b), m_a(a)
            {

            }

            inline float getRed() const
            {
                return m_r;
            }

            inline float getGreen() const
            {
                return m_g;
            }

            inline float getBlue() const
            {
                return m_b;
            }

            inline float getAlpha() const
            {
                return m_a;
            }

        private:

            float m_r, m_g, m_b, m_a;
        };

        namespace
        {
            const ColorF White =     ColorF::FromRGB(0xFF,0xFF,0xFF);
            const ColorF Black =     ColorF::FromRGB(0x00,0x00,0x00);

            const ColorF Red   =     ColorF::FromRGB(0xFF,0x00,0x00);
            const ColorF Green =     ColorF::FromRGB(0x00,0xFF,0x00);
            const ColorF Blue  =     ColorF::FromRGB(0x00,0x00,0xFF);
        }
    }
}
