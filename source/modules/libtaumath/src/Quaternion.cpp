#include "../../../include/tau/math/Quaternion.hpp"

#include "../../../include/tau/math/Vector3.hpp"

using namespace tau;
using namespace tau::math;

Quaternion Quaternion::FromEulerRadians(const Vector3& rot)
{
    Scalar retX;
    Scalar retY;
    Scalar retZ;
    Scalar retW;


    Scalar x = rot.getX(); // Geading.
    Scalar y = rot.getY(); // Altitude.
    Scalar z = rot.getZ(); // Bank.

    Scalar c1 = cosine(x / 2);
    Scalar c2 = cosine(y / 2);
    Scalar c3 = cosine(z / 2);
    Scalar s1 = sine(x / 2);
    Scalar s2 = sine(y / 2);
    Scalar s3 = sine(z / 2);
    Scalar c1c2 = c1 * c2;
    Scalar s1s2 = s1 * s2;


    retX = (c1c2*s3) + (s1s2*c3);
    retY = (s1*c2*c3) + (c1*s2*s3);
    retZ = (c1*s2*c3) - (s1*c2*s3);
    retW = (c1c2*c3) - (s1s2 * s3);

    return Quaternion(retX, retY, retZ, retW);
}

/*

Matrix4 Quaternion::toRotationMatrix()
{
    Scalar data[16];

    // Normalize the quaternion.
    normalize();

    // Calculate powers of variables.
    Scalar xP2 = power(m_x, 2);
    Scalar yP2 = power(m_y, 2);
    Scalar zP2 = power(m_z, 2);

    // First row.
    data[0]  = 1 - (2 * yP2) - (2 * zP2);
    data[1]  = 2 * m_x * m_y - 2 * m_w * m_z;
    data[2]  = 2 * m_x * m_z + 2 * m_w * m_y;
    data[3]  = 0;

    // Second row.
    data[4]  = 2 * m_x * m_y + 2 * m_w * m_z;
    data[5]  = 1 - 2 * xP2 - 2 * zP2;
    data[6]  = 2 * m_y * m_z + 2 * m_w * m_x;
    data[7]  = 0;

    // Third row.
    data[8]  = 2 * m_x * m_z - 2 * m_w * m_y;
    data[9]  = 2 * m_y * m_z - 2 * m_w * m_x;
    data[10] = 1 - 2 * xP2 - 2 * yP2;
    data[11] = 0;

    // Fourth row.
    data[12] = 0;
    data[13] = 0;
    data[14] = 0;
    data[15] = 1;

    return Matrix4::FromScalarArray(data);
}*/

void Quaternion::normalize()
{
    Scalar xP2 = square(m_x);
    Scalar yP2 = square(m_y);
    Scalar zP2 = square(m_z);
    Scalar wP2 = square(m_w);

    Scalar magnitudeInv = inverseSquareRoot(xP2 + yP2 + zP2 + wP2);

    // Divide each scalar by the magnitude.
    this->m_x *= magnitudeInv;
    this->m_y *= magnitudeInv;
    this->m_z *= magnitudeInv;
    this->m_w *= magnitudeInv;
}

Vector3 Quaternion::rotateVector(const Vector3& vec)
{
    Scalar vX = vec.getX();
    Scalar vY = vec.getY();
    Scalar vZ = vec.getZ();

    Scalar x1 = m_y*vZ - m_z*vY;
    Scalar y1 = m_z*vX - m_x*vZ;
    Scalar z1 = m_x*vY - m_y*vX;

    Scalar x2 = m_w*x1 + m_y*z1 - m_z*y1;
    Scalar y2 = m_w*y1 + m_z*x1 - m_x*z1;
    Scalar z2 = m_w*z1 + m_x*y1 - m_y*x1;

    Scalar resX = vX + 2.0 * x2;
    Scalar resY = vY + 2.0 * y2;
    Scalar resZ = vZ + 2.0 * z2;

    return Vector3(resX, resY, resZ);
}
