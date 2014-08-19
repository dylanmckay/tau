#include "../../../include/tau/math/Matrix4.hpp"

#include "../../../include/tau/math/Quaternion.hpp"
#include "../../../include/tau/compiler.hpp"

#include <cstring> // memcpy, etc.


/*
 * POSSIBLE OPTIMIZATION. create matrix then directly use data[i], rather than make array and copy.
 */



using namespace tau;
using namespace tau::math;

namespace
{
    // Represents a 4x4 identity matrix.
    Scalar IdentityMatrix[] =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

const Matrix4 Matrix4::Identity = Matrix4();


Matrix4 Matrix4::FromScalarArray(const Scalar* data)
{
    return Matrix4(data);
}

Matrix4 Matrix4::BuildPerspectiveProjectionMatrix(Scalar fov, Scalar aspect, Scalar near, Scalar far)
{
    Scalar data[16];

    Scalar size = near * tangent(fov / 2);
    Scalar left = -size;
    Scalar right = size;
    Scalar bottom = -size / aspect;
    Scalar top = size / aspect;

    data[0] = 2 * near / (right - left);
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;

    data[4] = 0;
    data[5] = 2 * near / (top - bottom);
    data[6] = 0;
    data[7] = 0;

    data[8] = (right + left) / (right - left);
    data[9] = (top + bottom) / (top - bottom);
    data[10] = -(far + near) / (far - near);
    data[11] = -1;

    data[12] = 0;
    data[13] = 0;
    data[14] = -(2 * far * near) / (far - near);

    return Matrix4(data);
}

Matrix4 Matrix4::BuildOrthoProjectionMatrix(Scalar left, Scalar right, Scalar bottom, Scalar top, Scalar near, Scalar far)
{
    Scalar data[16];

    data[0] = 2 / (right - left);
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;

    data[4] = 0;
    data[5] = 2 / (top - bottom);
    data[6] = 0;
    data[7] = 0;

    data[8] = 0;
    data[9] = 0;
    data[10] = -1 / (far - near);
    data[11] = 0;

    data[12] = -(right + left) / (right - left);
    data[13] = -(top + bottom) / (top - bottom);
    data[14] = -near / (far - near);
    data[15] = 1;

    return Matrix4(data);
}

Matrix4 Matrix4::BuildCameraTransform(const Vector3& pos, const Vector3& dir, const Vector3& up)
{
    Vector3 right(0,0,1);

    Scalar data[16];

    Vector3 zaxis(dir);
    zaxis.normalize();

    Vector3 xaxis(up.crossProduct(zaxis));
    xaxis.normalize();

    Vector3 yaxis(zaxis.crossProduct(xaxis));

    data[0] = xaxis.getX();
    data[4] = yaxis.getX();
    data[8] = zaxis.getX();
    data[12] = 0;

    data[1] = xaxis.getY();
    data[5] = yaxis.getY();
    data[9] = zaxis.getY();
    data[13] = 0;

    data[2] = xaxis.getZ();
    data[6] = yaxis.getZ();
    data[10] = zaxis.getZ();
    data[14] = 0;

    data[3] = -(xaxis.dotProduct(pos));
    data[7] = -(yaxis.dotProduct(pos));
    data[11] = -(zaxis.dotProduct(pos));
    data[15] = 1;

    /*

    data[12] = data[13] = data[14] = 0;
    data[15] = 1;

    data[0] = right.getX();
    data[1] = right.getY();
    data[2] = right.getZ();
    data[3] = -(right.dotProduct(pos));

    data[4] = up.getX();
    data[5] = up.getY();
    data[6] = up.getZ();
    data[7] = -(up.dotProduct(pos));

    data[8] = dir.getX();
    data[9] = dir.getY();
    data[10] = dir.getZ();
    data[11] = -(dir.dotProduct(pos));*/

    return Matrix4(data);
}

Matrix4::Matrix4()
{
    std::memcpy(m_cells, IdentityMatrix, sizeof(m_cells));
}

/*
Matrix4::Matrix4(const Vector3& pos, const Quaternion& rot)
{
    setTranslation(pos);
}*/

void Matrix4::setTranslation(const Vector3& translation)
{
    // Set top-right three cells to translation.
    //m_cells[3]  = translation.getX();
    // m_cells[7]  = translation.getY();
    // m_cells[11] = translation.getZ();

    m_cells[3] = translation.getX();
    m_cells[7] = translation.getY();
    m_cells[11] = translation.getZ();
}

void Matrix4::setRotation(const Quaternion& quat)
{
    // OPT: is normalization necessary.
    Quaternion q = quat.getNormalized();

    Scalar qx = q.getX();
    Scalar qy = q.getY();
    Scalar qz = q.getZ();
    Scalar qw = q.getW();

    // First column.
    m_cells[0] = 1 - 2*qy*qy - 2*qz*qz;
    m_cells[4] = 2*qx*qy - 2*qz*qw;
    m_cells[8] = 2*qx*qz + 2*qy*qw;

    // Second column.
	m_cells[1] = 2*qx*qy + 2*qz*qw;
	m_cells[5] = 1 - 2*qx*qx - 2*qz*qz;
	m_cells[9] = 2*qy*qz - 2*qx*qw;

	// Third column.
	m_cells[2] = 2*qx*qz - 2*qy*qw;
	m_cells[6] = 2*qy*qz + 2*qx*qw;
	m_cells[10] = 1 - 2*qx*qx - 2*qy*qy;

}

void Matrix4::setScale(const Vector3& scale)
{
    m_cells[12]  = scale.getX();
    m_cells[13]  = scale.getY();
    m_cells[14] = scale.getZ();
}


Vector3 Matrix4::translateVector(const Vector3& vec) const
{
    return vec + Vector3(m_cells[3], m_cells[7], m_cells[11]);
}

Vector3 Matrix4::rotateVector(const Vector3& vec) const
{
    Scalar vecX = vec.getX();
    Scalar vecY = vec.getY();
    Scalar vecZ = vec.getZ();

    Scalar x = vecX*m_cells[0] + vecY*m_cells[4] + vecZ*m_cells[8];
    Scalar y = vecX*m_cells[1] + vecY*m_cells[5] + vecZ*m_cells[9];
    Scalar z = vecX*m_cells[2] + vecY*m_cells[6] + vecZ*m_cells[10];

    return Vector3(x, y, z);
}

Vector3 Matrix4::scaleVector(const Vector3& vec) const
{
    return vec * Vector3(m_cells[12], m_cells[13], m_cells[14]);
}

bool Matrix4::isIdentity() const
{
    // Iterate through the cells.
    for(unsigned int i=0; i<16; i++)
    {
        // Compare the cell to the identity matrix cell.
        if(m_cells[i] != IdentityMatrix[i])
            return false;
    }

    return true;
}

Matrix4 Matrix4::operator+(const Matrix4& mat) const
{
    Scalar data[16];

    data[0]  = this->m_cells[0]  + mat.m_cells[0];
    data[1]  = this->m_cells[1]  + mat.m_cells[1];
    data[2]  = this->m_cells[2]  + mat.m_cells[2];
    data[3]  = this->m_cells[3]  + mat.m_cells[3];
    data[4]  = this->m_cells[4]  + mat.m_cells[4];
    data[5]  = this->m_cells[5]  + mat.m_cells[5];
    data[6]  = this->m_cells[6]  + mat.m_cells[6];
    data[7]  = this->m_cells[7]  + mat.m_cells[7];
    data[8]  = this->m_cells[8]  + mat.m_cells[8];
    data[9]  = this->m_cells[9]  + mat.m_cells[9];
    data[10] = this->m_cells[10] + mat.m_cells[10];
    data[11] = this->m_cells[11] + mat.m_cells[11];
    data[12] = this->m_cells[12] + mat.m_cells[12];
    data[13] = this->m_cells[13] + mat.m_cells[13];
    data[14] = this->m_cells[14] + mat.m_cells[14];
    data[15] = this->m_cells[15] + mat.m_cells[15];

    return Matrix4(data);
}

Matrix4 Matrix4::operator-(const Matrix4& mat) const
{
    Scalar data[16];

    data[0]  = this->m_cells[0]  - mat.m_cells[0];
    data[1]  = this->m_cells[1]  - mat.m_cells[1];
    data[2]  = this->m_cells[2]  - mat.m_cells[2];
    data[3]  = this->m_cells[3]  - mat.m_cells[3];
    data[4]  = this->m_cells[4]  - mat.m_cells[4];
    data[5]  = this->m_cells[5]  - mat.m_cells[5];
    data[6]  = this->m_cells[6]  - mat.m_cells[6];
    data[7]  = this->m_cells[7]  - mat.m_cells[7];
    data[8]  = this->m_cells[8]  - mat.m_cells[8];
    data[9]  = this->m_cells[9]  - mat.m_cells[9];
    data[10] = this->m_cells[10] - mat.m_cells[10];
    data[11] = this->m_cells[11] - mat.m_cells[11];
    data[12] = this->m_cells[12] - mat.m_cells[12];
    data[13] = this->m_cells[13] - mat.m_cells[13];
    data[14] = this->m_cells[14] - mat.m_cells[14];
    data[15] = this->m_cells[15] - mat.m_cells[15];

    return Matrix4(data);
}

Matrix4 Matrix4::operator*(const Matrix4& mat) const
{
    Scalar data[16];

    const Scalar* m1 = this->m_cells;
    const Scalar* m2 = mat.m_cells;

    data[0] = m1[0]*m2[0] + m1[4]*m2[1] + m1[8]*m2[2] + m1[12]*m2[3];
    data[1] = m1[1]*m2[0] + m1[5]*m2[1] + m1[9]*m2[2] + m1[13]*m2[3];
    data[2] = m1[2]*m2[0] + m1[6]*m2[1] + m1[10]*m2[2] + m1[14]*m2[3];
    data[3] = m1[3]*m2[0] + m1[7]*m2[1] + m1[11]*m2[2] + m1[15]*m2[3];

    data[4] = m1[0]*m2[4] + m1[4]*m2[5] + m1[8]*m2[6] + m1[12]*m2[7];
    data[5] = m1[1]*m2[4] + m1[5]*m2[5] + m1[9]*m2[6] + m1[13]*m2[7];
    data[6] = m1[2]*m2[4] + m1[6]*m2[5] + m1[10]*m2[6] + m1[14]*m2[7];
    data[7] = m1[3]*m2[4] + m1[7]*m2[5] + m1[11]*m2[6] + m1[15]*m2[7];

    data[8] = m1[0]*m2[8] + m1[4]*m2[9] + m1[8]*m2[10] + m1[12]*m2[11];
    data[9] = m1[1]*m2[8] + m1[5]*m2[9] + m1[9]*m2[10] + m1[13]*m2[11];
    data[10] = m1[2]*m2[8] + m1[6]*m2[9] + m1[10]*m2[10] + m1[14]*m2[11];
    data[11] = m1[3]*m2[8] + m1[7]*m2[9] + m1[11]*m2[10] + m1[15]*m2[11];

    data[12] = m1[0]*m2[12] + m1[4]*m2[13] + m1[8]*m2[14] + m1[12]*m2[15];
    data[13] = m1[1]*m2[12] + m1[5]*m2[13] + m1[9]*m2[14] + m1[13]*m2[15];
    data[14] = m1[2]*m2[12] + m1[6]*m2[13] + m1[10]*m2[14] + m1[14]*m2[15];
    data[15] = m1[3]*m2[12] + m1[7]*m2[13] + m1[11]*m2[14] + m1[15]*m2[15];

    return Matrix4(data);
}

Matrix4& Matrix4::operator*=(const Matrix4& mat)
{
    Matrix4 temp(*this * mat);

    memcpy(this->m_cells, temp.m_cells, sizeof(this->m_cells));


    return *this;
}

Matrix4 Matrix4::operator*(Scalar s) const
{
    Scalar data[16];

    data[0]  = this->m_cells[0]  * s;
    data[1]  = this->m_cells[1]  * s;
    data[2]  = this->m_cells[2]  * s;
    data[3]  = this->m_cells[3]  * s;
    data[4]  = this->m_cells[4]  * s;
    data[5]  = this->m_cells[5]  * s;
    data[6]  = this->m_cells[6]  * s;
    data[7]  = this->m_cells[7]  * s;
    data[8]  = this->m_cells[8]  * s;
    data[9]  = this->m_cells[9]  * s;
    data[10] = this->m_cells[10] * s;
    data[11] = this->m_cells[11] * s;
    data[12] = this->m_cells[12] * s;
    data[13] = this->m_cells[13] * s;
    data[14] = this->m_cells[14] * s;
    data[15] = this->m_cells[15] * s;

    return Matrix4(data);
}

Matrix4::Matrix4(const Scalar* data)
{
    std::memcpy(m_cells, data, sizeof(m_cells));
}
