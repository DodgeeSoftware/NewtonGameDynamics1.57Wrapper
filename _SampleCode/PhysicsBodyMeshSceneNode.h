#ifndef PHYSICSBODYMESHSCENENODE_H
#define PHYSICSBODYMESHSCENENODE_H

#include <cstddef>
#include <irrlicht.h>
#include <CMeshSceneNode.h>

// LUA SCRIPT LIBRARIES
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
// LUABIND
#include <luabind/luabind.hpp>

#include <newton.h>
/* NOTE:
            "os.h"

            The above files come directly from the Irrlicht Library and
            I am including them from the '$(#Irrlicht.base)\source\irrlicht'
            global compiler variable.

            The CPP file also includes the CPP files which implement each respective
            class. The reason that these files are taken from the irrlicht library and not
            reimplemented is because doing so replicates already defined code, and so that
            the PhysicsBodyMeshSceneNode has and identical behaviour and interface to the
            native IMeshSceneNode and can simply be added to Irrlicht's scenemanager.
            This allows us to use the scene manager to search for the scenenode and treat
            it in a completly ordinary manner. In the physics callbacks we can also typecast
            directly to a ISceneNode */
#include <os.h>

#include "GamePhysics.h"
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonMassMatrix.h"
#include "NewtonVector3.h"

#include "PhysicsUtils.h"


namespace irr
{
    namespace scene
    {
        class PhysicsBodyMeshSceneNode : public irr::scene::CMeshSceneNode, public PhysicsBody
        {
            // ******************************
            // * CONSTRUCTORS / DESTRUCTORS *
            // ******************************
            public:
                //! Default Constructor
                PhysicsBodyMeshSceneNode(irr::scene::IMesh* pMesh, irr::scene::ISceneNode* pParentSceneNode, irr::scene::ISceneManager* pSceneManager, NewtonWorld* pNewtonWorld, irr::s32 id, const irr::core::vector3df& position = irr::core::vector3df(0.0f, 0.0f, 0.0f), const irr::core::vector3df& rotation = irr::core::vector3df(0.0f, 0.0f, 0.0f), const irr::core::vector3df& scale = irr::core::vector3df(1.0f, 1.0f, 1.0f))
                    : irr::scene::CMeshSceneNode(pMesh, pParentSceneNode, pSceneManager, id, position, rotation, scale)
                {
                    // Set the NewtonWorld
                    this->setNewtonWorld(pNewtonWorld);
                }
                //! Destructor
                virtual ~PhysicsBodyMeshSceneNode() {}

            // ***********************************************
            // * PHYSICSBODYMESHSCENENODE SPECIFIC FUNCTIONS *
            // ***********************************************
            public:
                //! Create the Physics Body
                virtual void setBodyCollisionFrame(NewtonCollision* pCollisionFrame)
                {
                    PhysicsBody::setBodyCollisionFrame(pCollisionFrame);
                    PhysicsBody::setBodyUserData(this);
                }

            protected:

            // ***********************
            // * SCENENODE FUNCTIONS *
            // ***********************
            public:
                //! Set the position of the PhysicsBodySceneNode (if no body is set then the function set's the scenenode's position otherwise the body's position)
                virtual void setPosition(const irr::core::vector3df& newpos)
                {
                    if (this->getNewtonBody() != 0)
                    {
                        NewtonVector3 position(newpos.X, newpos.Y, newpos.Z);
                        position *= RenderScaleToNewton;
                        this->setBodyPosition(position);
                        return;
                    }
                    this->RelativeTranslation = newpos;
                }
                //! Set the SceneNode's Position
                virtual void setSceneNodePosition(const irr::core::vector3df& newpos) { irr::scene::ISceneNode::setPosition(newpos); }
                //!  Set the rotation in degrees of the PhysicsBodySceneNode (if no body is set then the function sets the scenenode's rotation otherwise the body's rotation)
                virtual void setRotation(const core::vector3df& newRotation)
                {
                    if (this->getNewtonBody() != 0)
                    {
                        NewtonVector3 rotation(newRotation.X, newRotation.Y, newRotation.Z);
                        this->setBodyRotationDegrees(rotation);
                        return;
                    }
                    this->RelativeRotation = newRotation;
                }
                //! Set the SceneNode's Rotation
                virtual void setSceneNodeRotation(const irr::core::vector3df& newRotation) { irr::scene::ISceneNode::setRotation(newRotation); }
                //! Set the Mesh for this SceneNode
                virtual void setMesh(irr::scene::IMesh* pMesh)
                {
                    // Call the parent class's setMesh function
                    irr::scene::CMeshSceneNode::setMesh(pMesh);
                    // This ensures textures with an alpha channel are drawn correctly, if there is no alpha channel then material type has no effect
                    this->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
                    this->setMaterialFlag(irr::video::EMF_USE_MIP_MAPS, false);
                }
                //! Register the SceneNode for rendering
                virtual void OnRegisterSceneNode();
                //! Called When the SceneNodeAnimation has to advance a frame
                virtual void OnAnimate(u32 timeMs);
                //! renders the node.
                virtual void render();

            // *******************
            // * SCRIPT BINDINGS *
            // *******************
            public:
                //! Bind Trigger to a luaState
                static void bindToLua(lua_State* pLuaState);
        };
    }
}

#endif // PHYSICSBODYMESHSCENENODE_H
