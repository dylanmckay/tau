
#include <tau/math/Matrix4.hpp>
#include <tau/math/Quaternion.hpp>

#include <iostream>

using namespace tau;
using namespace tau::math;


void DumpVector(const Vector3& vec)
{
    std::cout << "Vector3(" << vec.getX() << "," << vec.getY() << "," << vec.getZ() << ")";
}

void DumpQuaternion(const Quaternion& quat)
{
    std::cout << "Quaternion(" << quat.getX() << "," << quat.getY() << "," << quat.getZ() << "," << quat.getW() << ")";
}

void DumpMatrix(const Matrix4& mat)
{
    const Scalar* data = mat.getData();

    std::cout << "matrix:" << std::endl;

    for(unsigned int i=0; i<16; i+=4)
    {
        std::cout << data[i]   << " ";
        std::cout << data[i+1] << " ";
        std::cout << data[i+2] << " ";
        std::cout << data[i+3] << std::endl;
    }

    std::cout << std::endl;
}

int main()
{
    Vector3 inputRot = Vector3::FromDegrees(0,38.544,0);

    std::cout << "Rotation vector (degrees): ";
    DumpVector(inputRot*RadToDeg);
    std::cout << std::endl;

    Quaternion quat = Quaternion::FromEuler(inputRot);

    std::cout << "Rotation quaternion: ";
    DumpQuaternion(quat);
    std::cout << std::endl;
    Matrix4 mat;

    mat.setRotation(quat);

    std::cout << "Rotated matrix: \n";
    DumpMatrix(mat);

    Vector3 input(10,100, 500);

    std::cout << "input: ";
    DumpVector(input);
    std::cout << std::endl;

    Vector3 output = quat.rotateVector(input);

    std::cout << "quaternion output: ";
    DumpVector(output);
    std::cout << std::endl;

    output = mat.rotateVector(input);
    std::cout << "matrix output: ";
    DumpVector(output);
    std::cout << std::endl;

    return 0;
}
