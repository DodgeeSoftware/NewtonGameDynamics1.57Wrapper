/**
  * @file   PhysicsUniversalJoint.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsUniversalJoint implements an IPhysicsJoint and
  * functions to create a sort of double hinge joint where attached
  * bodies may rotate around a pin or around a perpendicular axis
  * to that pin
**/

#ifndef PHYSICSUNIVERSALJOINT_H
#define PHYSICSUNIVERSALJOINT_H

// LUA BIND
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

// NEWTON Includes
#include <cstddef>
#include <newton.h>

// GAMEPHYSICS Includes
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonGlobalScale.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"
#include "IPhysicsJoint.h"

// TODO - implement Newton joint accessors. Documentation is poor
/** The PhysicsUniversalJoint is a wrapper around the Newton UniversalJoint **/
class PhysicsUniversalJoint : public IPhysicsJoint
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default constructor
        PhysicsUniversalJoint()
        {
            this->pParentNewtonBody = 0;
            this->pChildNewtonBody = 0;
            this->pUniversalCallBack = 0;
            this->omegaPin0 = 0;
            this->omegaPin1 = 0;
        }
        //! Destructor
        virtual ~PhysicsUniversalJoint() {}

    // ********
    // * TYPE *
    // ********
    public:
        //! Get Joint type
        virtual E_JOINT_TYPE getType() { return JT_UNIVERSAL; }

    protected:
        // members and methods

    // ************
    // * CREATION *
    // ************
    public:
        //! Build the universal joint
        virtual bool build(NewtonVector3 pivot, NewtonVector3 pin1, NewtonVector3 pin2, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody);

    protected:
        // members and methods

    // **************
    // * PROPERTIES *
    // **************
    public:
        //! Get the Angle between the the bodies relative to Pin0
        virtual float getJointAngle0();
        //! Get the Angle between the the bodies relative to Pin1
        virtual float getJointAngle1();
        //! Get the AnglularVelocity between the the bodies relative to Pin0
        virtual float getAngularVelocityBetweenBodiesPin0();
        /* NOTE: THIS FUNCTION DOESN'T SET THE ANGULAR VELOCITY BETWEEN THE BODYS AND PIN0
            RATHER THIS FUNCTION IS USED BY THE CALLBACK TO STORE A LOCAL REFERENCE
            THE THE ANGULAR VELOCITY BETWEEN THE BODIES*/
        //! Set the AnglularVelocity between the the bodies and Pin0
        virtual void setAngularVelocityBetweenBodiesPin0(float omega);
        //! Get the AnglularVelocity between the the bodies relative to Pin1
        virtual float getAngularVelocityBetweenBodiesPin1();
        /* NOTE: THIS FUNCTION DOESN'T SET THE ANGULAR VELOCITY BETWEEN THE BODYS AND PIN1
            RATHER THIS FUNCTION IS USED BY THE CALLBACK TO STORE A LOCAL REFERENCE
            THE THE ANGULAR VELOCITY BETWEEN THE BODIES*/
        //! Set the AnglularVelocity between the the bodies relative to Pin1
        virtual void setAngularVelocityBetweenBodiesPin1(float omega);
        //! Get the total force asserted over the joint pivot point, to maintain the constraint.
        virtual NewtonVector3 getJointForce();
        /* NOTE: THIS FUNCTION DOESN'T SET THE FORCE BETWEEN THE JOINTS, IT IS USED BY THE
            CALLBACK TO STORE A LOCAL REFERENCE TO THE FORCE BETWEEN THE JOINTS */
        //! Set the Joint Force
        virtual void setJointForce(NewtonVector3 force);
        //! Get the origin of the joint in world space
        NewtonVector3 getPivot() { return this->pivot * NewtonToRenderScale; }
        //! Get the pin0 for this joint
        virtual NewtonVector3 getPin0();
        //! Get the pin1 for this joint
        virtual NewtonVector3 getPin1();

    protected:
        // The origin of the joint in world space
        NewtonVector3 pivot;
        // Vector for pin0
        NewtonVector3 pin0;
        // Vector for pin1
        NewtonVector3 pin1;
        // Angular velocity relative to pin0
        float omegaPin0;
        // Angular velocity relative to pin0
        float omegaPin1;
        // Force holding the joint together
        NewtonVector3 force;

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
        //! Get the Slider CallBack
        virtual NewtonUniversalCallBack  getUniversalCallBack () { return this->pUniversalCallBack; }
        //! Set the Slider CallBack
        virtual void setUniversalCallBack (NewtonUniversalCallBack pUniversalCallBack)
        {
            this->pUniversalCallBack = pUniversalCallBack;
            // Set the update callback for this joint
            NewtonUniversalSetUserCallback(this->pNewtonJoint, pUniversalCallBack);
        }

    protected:
        // Local Reference to the Slider CallBack (This callback is triggered when either of the bodies that are part of the joint are moving)
        NewtonUniversalCallBack  pUniversalCallBack;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // PHYSICSUNIVERSALJOINT_H
