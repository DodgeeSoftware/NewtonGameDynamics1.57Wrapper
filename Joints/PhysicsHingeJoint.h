/**
  * @file   PhysicsHingeJoint.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsHingeJoint implements an IPhysicsJoint and
  * functions like a opening or closing door on a hinge. There
  * is a pin around which attached Bodies may rotate but they are
  * not permitted to slide along the pin axis (in a corkscrew joint
  * the body is free to slide along the pin axis
**/

#ifndef PHYSICSHINGEJOINT_H
#define PHYSICSHINGEJOINT_H

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

/**
  * @brief The PhysicsHingeJoint is a class which acts as a wrapper around the Newton hinge joint. A hinge joint
  * is a joint similar to a door.
  **/
class PhysicsHingeJoint : public IPhysicsJoint
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default constructor
        PhysicsHingeJoint()
        {
            this->pParentNewtonBody = 0;
            this->pChildNewtonBody = 0;
            this->pHingeJointCallBack = 0;
            this->omega = 0;
        }
        //! Destructor
        virtual ~PhysicsHingeJoint() {}

    protected:
        // members and methods

    // ********
    // * TYPE *
    // ********
    public:
        //! Get Joint type
        virtual E_JOINT_TYPE getType() { return JT_HINGE; }

    protected:
        // members and methods

    // ************
    // * CREATION *
    // ************
    public:
        //! Setup the hinge joint
        virtual bool build(NewtonVector3 pivot, NewtonVector3 pin, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody);

    protected:
        // members and methods

    // **************
    // * PROPERTIES *
    // **************
    public:
        //! Get angle between the two Newton bodies that form this joint
        virtual float getAngleRadiansBetweenTheBodies();
        //! Get angle between the two Newton bodies that form this joint
        virtual float getAngleDegreesBetweenTheBodies();
        //! Get the angular velocity between the two Newton bodies that form this joint
        virtual float getAnglularVelocityBetweenTheBodies();
        /* NOTE: THIS FUNCTION DOESN'T SET THE ANGULAR VELOCITY IT IS SIMPLY USED
            BY THE CALLBACK SO THAT WE CAN QUERY THE ANGULAR VELOCITY*/
        //! Set the angular velocity between the two Newton bodies that form this joint
        virtual void setAnglularVelocityBetweenTheBodies(float omega);
        //! Get the total force asserted over the joint pivot point, to maintain the constraint
        virtual NewtonVector3 getForceBetweenTheBodies();
        /* NOTE: THIS FUNCTION DOESN'T SET THE FORCE BETWEEN THE BODIES IT IS SIMPLY
            USED BY THE CALLBACK SO THAT WE CAN QUERY THE FORCE BETWEEN THE BODIES*/
        //! Set the total force asserted over the joint pivot point, to maintain the constraint
        virtual void setForceBetweenTheBodies(NewtonVector3 force);
        //! Get the origing of the joint in world space
        NewtonVector3 getPivot() { return this->pivot * NewtonToRenderScale; }
        //! Get the Pin used by this slider
        NewtonVector3 getPin() { return this->pin; }

    protected:
        // The origin of the joint in world space
        NewtonVector3 pivot;
        // Keep reference to the pin
        NewtonVector3 pin;
        // Keep a reference to the Angular velocity
        float omega;
        // Keep a reference to the force between the bodies
        NewtonVector3 force;

    // *************************
    // * NEWTON BODY ACCESSORS *
    // *************************
    public:
        //! Get the Parent NewtonBody
        NewtonBody* getParentNewtonBody() { return this->pParentNewtonBody; }
        //! Get the Child NewtonBody
        NewtonBody* getChildNewtonBody() { return this->pChildNewtonBody; }

    protected:
        // The Parent NewtonBody this joint is connected to
        NewtonBody* pParentNewtonBody;
        // The Child NewtonBody this joint is connected to
        NewtonBody* pChildNewtonBody;

    // *************
    // * CALLBACKS *
    // *************
    public:
        //! Get the HingeCallBack
        NewtonHingeCallBack getHingeCallBack() { return this->pHingeJointCallBack; }
        //! Set the HingeCallBack
        void setHingeCallBack(NewtonHingeCallBack pHingeJointCallBack)
        {
            this->pHingeJointCallBack = pHingeJointCallBack;
            // Set the Update Callback
            NewtonHingeSetUserCallback(this->pNewtonJoint, pHingeJointCallBack);
        }

    protected:
        // Local Reference to the HingeCallBack (This callback is triggered when either of the bodies that are part of the joint are moving)
        NewtonHingeCallBack pHingeJointCallBack;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // PHYSICSHINGEJOINT_H
