#pragma once

#include "../ReferenceCounted.hpp"

#include "../math/Vector3.hpp"
#include "forward.hpp"

#include <vector>

namespace tau
{
    namespace graphics
    {
        class Node : public ReferenceCounted
        {

        public:

            virtual ~Node();

            virtual void render() = 0;

            /*!
             * Reparents the node so that it is a child of the given node.
             */
            void setParent(Node* parent);

            virtual void setPosition(const math::Vector3& position);

            const math::Vector3& getPosition() const;

        protected:

            inline Node(SceneManager* smgr,
                        Node* parent = nullptr,
                        const math::Vector3& pos = math::Vector3(0,0,0)) :
                                              m_smgr(smgr),
                                              m_parent(parent),
                                              m_position(pos)
            {

            }

            void renderChildren();

        protected:

            SceneManager* m_smgr;

            Node* m_parent;
            std::vector<Node*> m_children;

            math::Vector3 m_position;

        };
    }
}
