#include <tau/graphics/TauDevice.hpp>
#include <tau/graphics/VideoDriver.hpp>
#include <tau/graphics/SceneManager.hpp>
#include <tau/graphics/EventListener.hpp>
#include <tau/graphics/input/Mouse.hpp>
#include <tau/graphics/input/MouseMoveEvent.hpp>
#include <tau/graphics/input/KeyboardEvent.hpp>
#include <tau/graphics/CameraNode.hpp>
#include <tau/math/Matrix4.hpp>
#include <tau/math/LineSegment3.hpp>
#include <tau/math/Position2.hpp>
#include <tau/math/Quaternion.hpp>
#include <tau/String.hpp>
#include <tau/debug.hpp>
#include <tau/Timer.hpp>

#include<GL/glx.h>
#include<GL/glu.h>

#include <iostream>

using namespace tau;
using namespace tau::graphics;
using namespace tau::graphics::input;
using namespace tau::math;


CameraNode* camera;

Timer timer;
Scalar delta;

class Listener : public EventListener
{

public:



    bool onEvent(TauDevice* device, const Event& ev) override
    {

        switch(ev.getEventType())
        {
            case Event::Type::MouseMove:
            {
                const input::MouseMoveEvent& event = (const input::MouseMoveEvent&)ev;

                device->getMouse()->setPosition(Vector2(0,0));


                //Vector3 delta(-event.getDelta().getX(), event.getDelta().getY(),0);

                //camera->setTarget(camera->getTarget()+delta);

                Vector2 deltaMouse(event.getDelta()*0.1);

                Vector3 axis(camera->getDirection().crossProduct(camera->getUpVector()));
                axis.normalize();

                camera->rotateCamera(-deltaMouse.getY(), axis.getX(), axis.getY(), axis.getZ());
                camera->rotateCamera(deltaMouse.getX(), 0, 1, 0);

                return true;
            }
            case Event::Type::Keyboard:
            {
                const KeyboardEvent& event((const KeyboardEvent&)ev);

                if(event.wasReleased())
                    return false;

                switch(event.getKey())
                {
                    case Key::Up:
                    {
                        camera->moveForward(delta);


                        break;

                    }
                    case Key::Down:
                    {
                        camera->moveBackward(delta);

                        break;
                    }
                    case Key::Left:
                    {
                        camera->moveLeft(delta);

                        break;
                    }
                    case Key::Right:
                    {
                        camera->moveRight(delta);

                        break;
                    }
                    default:
                    {
                        return false;
                    }
                }

            }
            default:
            {
                return false;
            }
        }
    }
};

void DumpVector(const Vector3& vec);

int main()
{
    Listener listener;
    TauDevice* device = TauDevice::Create();

    device->setListener(&listener);

    VideoDriver* driver = device->getVideoDriver();
    SceneManager* smgr = new SceneManager(device);

    driver->setBackgroundColor(ColorF::FromRGB(100,150,180));

    timer.mark();
    delta = 0;

    Vector3 rotation;

    camera = smgr->addCameraNode();


    while(device->isRunning())
    {
        device->run();

        driver->beginScene(true, true);


        smgr->renderAll();
/*
        rotation += Vector3(0,0.01,0)*delta;
*/


        driver->drawLineSegment3(Vector3(0,0,0), Vector3(100,0,0), Red);
        driver->drawLineSegment3(Vector3(0,0,0), Vector3(0,100,0), Green);
        driver->drawLineSegment3(Vector3(0,0,0), Vector3(0,0,100), Blue);
/*
        Matrix4 plane;
        plane.setRotation(Quaternion::FromEulerDegrees(rotation));
        driver->setViewMatrix(plane);

*/


        glBegin(GL_QUADS);
          glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0);
          glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0);
          glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0);
          glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0);
        glEnd();



        driver->endScene();

        delta = timer.mark();
    }

    delete device;

    return 0;


    return 0;
}




void DumpVector(const Vector3& vec)
{
    std::cout << "Vector3(" << vec.getX() << "," << vec.getY() << "," << vec.getZ() << ")";
}
/*
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
*/
