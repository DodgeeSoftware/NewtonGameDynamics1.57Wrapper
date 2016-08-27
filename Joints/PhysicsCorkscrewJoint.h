/**
  * @file   PhysicsCorkScrewJoint.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsCorkScrewJoint implements an IPhysicsJoint and
  * implements a simple corkscrew joint. Such a joint creates a rail
  * a body may slide along and that also forms an axis for the body to
  * rotate around
**/

#ifndef PHYSICSCORKSCREWJOINT_H
#define PHYSICSCORKSCREWJOINT_H

// LUA BIND
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

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
#include "IPhysicsJoint.h"

// TODO: The Properties methods are poorly implemented because of bad documentation. This needs attension asap

/**
  * @brief A PhysicsCorkscrewJoint restricts the movement two newton bodies with a joint.
  * @author Shem Taylor
  **/
class PhysicsCorkscrewJoint : public IPhysicsJoint
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default constructor
        PhysicsCorkscrewJoint()
        {
            this->pParentNewtonBody = 0;
            this->pChildNewtonBody = 0;
            this->pCorkScrewCallBack = 0;
        }
        //! Destructor
        virtual ~PhysicsCorkscrewJoint() {}

    protected:
        // Methods and members

    // ********
    // * TYPE *
    // ********
    public:
        //! Get Joint type
        virtual E_JOINT_TYPE getType() { return JT_CORK_SCREW; }

    protected:
        // Methods and members

    // ************
    // * CREATION *
    // ************
    public:
        //! Build the Joint
        virtual bool build(NewtonVector3 pivot, NewtonVector3 pin, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody);

    protected:
        // Methods and members

    // **************
    // * PROPERTIES *
    // **************
    public:
        /* TODO: need work out these functions the documentation is terrible :(
            Most of them seem to do exactly the same thing :(
            the documentation is really really bad*/
        // 888888888888888888
        virtual float getRotationRadians();
        virtual float getRotationDegrees();
        virtual float getJointAngle();
//        virtual float getJointVeloc();
//        virtual float getJointOmega();
//        virtual NewtonVector3 getJointForce();
        // 888888888888888888
        //! Get the origing of the joint in world space
        virtual NewtonVector3 getPivot() { return this->pivot * NewtonToRenderScale; }
        //! Get the Pin used by this slider
        virtual NewtonVector3 getPin() { return this->pin; }

    protected:
        // The origin of the joint in world space
        NewtonVector3 pivot;
        // Local reference to the pin
        NewtonVector3 pin;

    // *************************
    // * NEWTON BODY ACCESSORS *
    // *************************
    public:
        //! Get the Parent NewtonBody
        virtual NewtonBody* getParentNewtonBody() { return this->pParentNewtonBody; }
        //! Get the Child NewtonBody
        virtual NewtonBody* getChildNewtonBody() { return this->pChildNewtonBody; }

    protected:
        // The Parent NewtonBody this joint is connected to
        NewtonBody* pParentNewtonBody;
        // The Child NewtonBody this joint is connected to
        NewtonBody* pChildNewtonBody;

    // *************
    // * CALLBACKS *
    // *************
    public:
        //! Get the CorkScrewCallBack
        virtual NewtonCorkscrewCallBack getCorkScrewCallBack() { return this->pCorkScrewCallBack; }
        //! Set the CorkScrewCallBack
        virtual void setCorkScrewCallBack(NewtonCorkscrewCallBack pCorkScrewCallBack)
        {
            this->pCorkScrewCallBack = pCorkScrewCallBack;
            // Set the Update Callback
            NewtonCorkscrewSetUserCallback(this->pNewtonJoint, pCorkScrewCallBack);
        }

    protected:
        // Local Reference to the CorkScrewCallback
        NewtonCorkscrewCallBack pCorkScrewCallBack;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // PHYSICSCORKSCREWJOINT_H
