#include "../../../include/tau/graphics/TauDevice.hpp"

#include "../../../include/tau/graphics/EventListener.hpp"
#include "../../../include/tau/graphics/input/Mouse.hpp"

using namespace tau;
using namespace tau::graphics;
using namespace tau::graphics::input;

TauDevice::TauDevice() : m_listener(nullptr)
{

}

void TauDevice::setListener(EventListener* listener)
{
    m_listener = listener;
}

bool TauDevice::dispatchEvent(const Event& event)
{
    if(m_listener)
        return m_listener->onEvent(this, event);
    else
        return false;
}
