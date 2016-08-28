#include "PhysicsBodyMeshSceneNode.h"
#include "CMeshSceneNode.cpp"

namespace irr
{
    namespace scene
    {
        void PhysicsBodyMeshSceneNode::OnRegisterSceneNode()
        {
//            NewtonMatrix4 bodyMatrix = this->getBodyMatrix();
//            NewtonVector3 position = bodyMatrix.getTranslation();
//            NewtonVector3 rotation = bodyMatrix.getRotationDegrees();
//            this->setSceneNodePosition(irr::core::vector3df(position.getX() * NewtonToRenderScale, position.getY() * NewtonToRenderScale, position.getZ() * NewtonToRenderScale));
//            this->setSceneNodeRotation(irr::core::vector3df(rotation.getX(), rotation.getY(), rotation.getZ()));
            irr::scene::CMeshSceneNode::OnRegisterSceneNode();
            //this->updateAbsolutePosition();
        }
        void PhysicsBodyMeshSceneNode::OnAnimate(u32 timeMs)
        {
            irr::scene::CMeshSceneNode::OnAnimate(timeMs);
        }
        void PhysicsBodyMeshSceneNode::render()
        {
            irr::scene::CMeshSceneNode::render();
        }
        void PhysicsBodyMeshSceneNode::bindToLua(lua_State* pLuaState)
        {
            // TODO: Implement me
        }

    }
}
