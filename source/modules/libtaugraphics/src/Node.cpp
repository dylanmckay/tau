#include <tau/graphics/Node.hpp>

#include <algorithm>

using namespace tau;
using namespace tau::graphics;

Node::~Node()
{
    if(m_parent)
        m_parent->drop();
}

void Node::setPosition(const math::Vector3& position)
{
    m_position = position;
}

const math::Vector3& Node::getPosition() const
{
    return m_position;
}

void Node::setParent(Node* parent)
{
    parent->grab();

    // Check if the node is already a child node.
    if(m_parent)
    {
        std::vector<Node*>::iterator it;

        // Find us in the parent list.
        it = std::find(m_parent->m_children.begin(), m_parent->m_children.end(), this);

        // It should always be found.
        TauAssert(it != m_parent->m_children.end());

        // Remove us from the parents' list.
        m_parent->m_children.erase(it);

        m_parent->drop();
    }

    // Put us into the parent list.
    parent->m_children.push_back(this);

    m_parent = parent;
}

void Node::renderChildren()
{
    for(auto node : m_children)
    {
        node->render();
    }
}
