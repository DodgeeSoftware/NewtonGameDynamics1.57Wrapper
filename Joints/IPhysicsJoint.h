#ifndef IPHYSICSJOINT_H
#define IPHYSICSJOINT_H

// LUA BIND
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

// C++ Includes
#include <string>

// NEWTON INCLUDES
#include <cstddef>
#include <newton.h>

// NEWTON WRAPPER INCLUDES
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonGlobalScale.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"
#include "PhysicsWorld.h"
#include "PhysicsJointTypes.h"

/**
  * @brief The PhysicsJoint class is the base class from which all joints must derive
  **/
class IPhysicsJoint
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default constructor
        IPhysicsJoint()
        {
            this->pNewtonJoint = 0;
        }
        //! Default destructor
        virtual ~IPhysicsJoint()
        {
            // free the joint
            if (this->pNewtonJoint != 0 && this->pNewtonWorld != 0)
            {
                // if the joint is still exists then destroy it.
                if (NewtonJointGetUserData(this->pNewtonJoint) != 0)
                {
                    // reset the destructor callback for this joint
                    NewtonJointSetDestructor(this->pNewtonJoint, 0);
                    // destroy this joint
                    NewtonDestroyJoint(this->pNewtonWorld, this->pNewtonJoint);
                    // set to pointer to this joint to 0
                    this->pNewtonJoint = 0;
                }
            }
        }

    protected:
        // methods and members

    // ****************
    // * NEWTON WORLD *
    // ****************
    public:
        //! Get the Newton World being used by the Debugger
        virtual NewtonWorld* getNewtonWorld() { return this->pNewtonWorld; }
        //! Set the Newton World for the Debugger
        virtual void setNewtonWorld(NewtonWorld* pNewtonWorld) { this->pNewtonWorld = pNewtonWorld; }

    protected:
        // Local reference to the newton World
        NewtonWorld* pNewtonWorld;

    // *******************
    // * JOINT USER DATA *
    // *******************
    public:
        //! Get the User Data for the Joint
        virtual void* getUserData() { return NewtonJointGetUserData(this->pNewtonJoint); }
        //! Set the User Data for the Joint
        virtual void setUserData(void* pUserData) { NewtonJointSetUserData(this->pNewtonJoint, pUserData); }

    protected:
        // methods and members

    // ******************
    // * CORE FUNCTIONS *
    // ******************
    public:
        //! Removes the joint disconnecting it from NewtonBodies
        virtual void clear();

    protected:
        // methods and members

    // ******************
    // * TYPE FUNCTIONS *
    // ******************
    public:
        //! Get Joint type
        virtual E_JOINT_TYPE getType() = 0;

    protected:
        // methods and members

    // **************
    // * PROPERTIES *
    // **************
    public:
        //! query if the two bodies that form this joint are allowed to collide
        virtual bool isCollidable();
        //! Enable the two bodies that make up this joint to collide
        virtual void enableCollision();
        //! Disable the two bodies that make up this joint from colliding
        virtual void disableCollision();
        //! Get the stiffness coefficient between these two joints
        virtual float getStiffness();
        //! Set the stiffness coefficient between these two joints
        virtual void setStiffness(float coefficient);
        //! Get the newton joint
        virtual NewtonJoint* getNewtonJoint() { return this->pNewtonJoint; }

    protected:
        // Pointer to the Newton joint
        NewtonJoint* pNewtonJoint;

    // *************
    // * CALLBACKS *
    // *************
    public:
        //! Get the Destructor CallBack
        virtual NewtonConstraintDestructor getJointDestructorCallBack() { return this->pJointDestructorCallBack; }
        //! Set the Destructor CallBack
        virtual void setJointDestructorCallback(NewtonConstraintDestructor pJointDestructorCallBack)
        {
            this->pJointDestructorCallBack = pJointDestructorCallBack;
            // Set the destructor callback for this joint
            NewtonJointSetDestructor(this->pNewtonJoint, pJointDestructorCallBack);
        }

    protected:
        // Local Reference to the Destructor CallBack
        NewtonConstraintDestructor pJointDestructorCallBack;

    // ********
    // * MESH * (used by the debugger)
    // ********
    public:
        //! Get Mesh
        virtual void* getMesh() { return this->pMesh; }
        //! Set Mesh
        virtual void setMesh(void* pMesh) { this->pMesh = pMesh; }

    protected:
        // Pointer to the mesh
        void* pMesh;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // IPHYSICSJOINT_H
