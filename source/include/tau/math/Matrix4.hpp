#pragma once

#include "Scalar.hpp"
#include "Vector3.hpp"
#include "forward.hpp"

namespace tau
{
    namespace math
    {
        /*!
         * Represents a 4x4 transformation matrix. Column-major.
         */
        class Matrix4
        {

        public:

            static Matrix4 FromScalarArray(const Scalar* data);

            static Matrix4 BuildPerspectiveProjectionMatrix(Scalar fov, Scalar aspect, Scalar near, Scalar far);

            static Matrix4 BuildOrthoProjectionMatrix(Scalar left, Scalar right, Scalar bottom, Scalar top, Scalar near, Scalar far);

            static Matrix4 BuildCameraTransform(const Vector3& pos, const Vector3& direction, const Vector3& up);

            static const Matrix4 Identity;

            /*!
             * Creates a new identity matrix.
             */
            Matrix4();

            //Matrix4(const Vector3& pos, const Quaternion& rot);

            /*!
             * Sets the translation of the tramsformation matrix.
             */
            void setTranslation(const Vector3& translation);

            /*!
             * Sets the rotation of the transformation matrix.
             */
            void setRotation(const Quaternion& quat);

            /*!
             * Sets the scale of the transformation matrix.
             */
            void setScale(const Vector3& scale);

            /*!
             * Apply the translation to the given vector.
             * \param vec The vector to translate.
             * \return The result.
             */
            Vector3 translateVector(const Vector3& vec) const;

            /*!
             * Rotates the given vector.
             */
            Vector3 rotateVector(const Vector3& vec) const;

            /*!
             * Scales the given vector by the transformation.
             */
            Vector3 scaleVector(const Vector3& vec) const;

            /*!
             * Checks if this matrix is an identity matrix.
             */
            bool isIdentity() const;

            Matrix4 operator+(const Matrix4& mat) const;

            Matrix4 operator-(const Matrix4& mat) const;

            Matrix4 operator*(const Matrix4& mat) const;

            Matrix4& operator*=(const Matrix4& mat);

            Matrix4 operator*(Scalar s) const;

            inline const Scalar* getData() const
            {
                return m_cells;
            }


        private:

            /*!
             * Creates a matrix from an internal scalar table.
             */
            Matrix4(const Scalar* data);

            /*
             * The matrix data, in the format.
             * ----------------------------------------------
             * | cells[0]   cells[1]   cells[2]   cells[3]  |
             * | cells[4]   cells[5]   cells[6]   cells[7]  |
             * | cells[8]   cells[9]   cells[10]  cells[11] |
             * | cells[12]  cells[13]  cells[14]  cells[15] |
             * ----------------------------------------------
             *
             * ----------------------------------------------
             * |                                  trans.X   |
             * |                                  trans.Y   |
             * |                                  trans.Z   |
             * | scale.X    scale.Y    scale.Z       1      |
             * ----------------------------------------------
             */
            Scalar m_cells[16];


        };

    }

}
