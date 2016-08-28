/**
  * @file   PhysicsSliderJoint.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsSliderJoint implements an IPhysicsJoint and
  * functions to create a rail vector upon which an object may slide
  * but not rotate
**/

#ifndef PHYSICSSLIDERJOINT_H
#define PHYSICSSLIDERJOINT_H

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

// TODO - check the accessors I am not sure if they are correct
/** @class PhysicsSliderJoint
  * @brief An wrapper around A NewtonSliderJoint
  * @detail PhysicsSliderJoint implements an IPhysicsJoint and
  * functions to create a rail vector upon which an object may slide
  * but not rotate **/
class PhysicsSliderJoint : public IPhysicsJoint
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default constructor
        PhysicsSliderJoint()
        {
            this->pParentNewtonBody = 0;
            this->pChildNewtonBody = 0;
            this->pSliderJointCallBack = 0;
        }
        //! Destructor
        virtual ~PhysicsSliderJoint() {}

    protected:
        // members and methods

    // ********
    // * TYPE *
    // ********
    public:
        //! Get Joint type
        virtual E_JOINT_TYPE getType() { return JT_SLIDER; }

    protected:
        // members and methods

    // ************
    // * CREATION *
    // ************
    public:
        //! Build the slider joint
        virtual bool build(NewtonVector3 pivot, NewtonVector3 pin, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody);

    protected:
        // members and methods

    // **************
    // * PROPERTIES *
    // **************
    public:
        /* TODO: need work out these functions the documentation is terrible :(
            Most of them seem to do exactly the same thing :(
            the documentation is really really bad*/
//        // 888888888888888888
//        //! Get the displacement between the two bodies
//        virtual float getJointPosit();
//        //! Get the relative velocity between the bodies
//        virtual float getJointVeloc();
//        //! Get the total force asserted over the joint pivot point, to maintain the constraint
//        virtual NewtonVector3 getJointForce();
//        // 888888888888888888
        //! Get the origin of the joint in world space
        NewtonVector3 getPivot() { return this->pivot * NewtonToRenderScale; }
        //! Get the Pin used by this slider
        NewtonVector3 getPin() { return this->pin; }

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
        //! Get the Slider CallBack
        NewtonSliderCallBack getSliderCallBack() { return this->pSliderJointCallBack; }
        //! Set the Slider CallBack
        void setSliderCallBack(NewtonSliderCallBack pSliderJointCallBack)
        {
            this->pSliderJointCallBack = pSliderJointCallBack;
            // Set the update callback
            NewtonSliderSetUserCallback(this->pNewtonJoint, pSliderJointCallBack);
        }

    protected:
        // Local Reference to the Slider CallBack
        NewtonSliderCallBack pSliderJointCallBack;
//    public:
//        //! This callback is triggered when either of the bodies that are part of the joint are moving
//        static unsigned int sliderCallBack(const NewtonJoint* slider, NewtonHingeSliderUpdateDesc* desc);

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // PHYSICSSLIDERJOINT_H
