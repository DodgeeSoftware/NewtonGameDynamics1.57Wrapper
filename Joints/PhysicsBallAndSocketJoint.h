/**
  * @file   PhysicsBallAndSocketJoint.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsBallAndSocketJoint implements an IPhysicsJoint and
  * implements a simple ball and socket joint. An example is a shoulder joint
  * on a human.
**/

#ifndef PHYSICSBALLANDSOCKETJOINT_H
#define PHYSICSBALLANDSOCKETJOINT_H

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
  * @brief A PhysicsBallAndSocketJoint restricts the movement two newton bodies with a joint.
  * an example would be a shoulder joint on a human
  * @author Shem Taylor
  **/
class PhysicsBallAndSocketJoint : public IPhysicsJoint
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default constructor
        PhysicsBallAndSocketJoint()
        {
            this->pParentNewtonBody = 0;
            this->pChildNewtonBody = 0;
            this->pBallAndSocketCallBack = 0;
        }
        //! Destructor
        virtual ~PhysicsBallAndSocketJoint() {}

    protected:
        // Methods and members

    // ********
    // * TYPE *
    // ********
    public:
        //! Get Joint type
        virtual E_JOINT_TYPE getType() { return JT_BALL_AND_SOCKET; }

    protected:
        // Methods and members

    // ************
    // * CREATION *
    // ************
    public:
        //! Build the Joint
        virtual bool build(NewtonVector3 pivot, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody);

    protected:
        // Methods and members

    // **************
    // * PROPERTIES *
    // **************
    public:
        //! Set the ball and socket cone and twist limits (passing 0 into maxConeAngle and maxTwistAngle will disable the limits)
        /**
          * @param pin The restraint pin on the joint
          * @param maxConeAngle The maximum angle the joint can swing from the pin
          * @param maxTwistAngle The maximum angle the joint can twist around the pin
          **/
        virtual void setConeLimitsDegrees(NewtonVector3 pin, dFloat maxConeAngle, dFloat maxTwistAngle);
        //! Set the ball and socket cone and twist limits (passing 0 into maxConeAngle and maxTwistAngle will disable the limits)
        /**
          * @param pin The restraint pin on the joint
          * @param maxConeAngle The maximum angle the joint can swing from the pin
          * @param maxTwistAngle The maximum angle the joint can twist around the pin
          **/
        virtual void setConeLimitsRadians(NewtonVector3 pin, dFloat maxConeAngle, dFloat maxTwistAngle);
        //! Get the rotation of the join in Radians
        virtual NewtonVector3 getRotationRadians();
        //! Get the rotation of the join in Degrees
        virtual NewtonVector3 getRotationDegrees();
        //! Get the Angular Velocity Between the Bodies
        virtual NewtonVector3 getAnglularVelocityBetweenTheBodies();
        /* NOTE: THIS FUNCTION DOESN'T SET THE VELOCITY OF THE JOINT IT IS ONLY USED BY THE CALLBACK SO
            THAT WE CAN USE THE getAnglularVelocityBetweenTheBodies TO GET THE ANGULAR VELOCITY BETWEEN
            THE JOINTS*/
        //! Set the Angular Velocity Between the Bodies
        virtual void setAnglularVelocityBetweenTheBodies(NewtonVector3 omega);
        //! Get the total force asserted over the joint pivot point, to maintain the constraint
        /**
          * @return The total force asserted over the joint pivot point
          **/
        virtual NewtonVector3 getForceBetweenTheBodies();
        /* NOTE: THIS FUNCTION DOESN'T SET THE FORCE BETWEEN THE BODIES IT IS ONLY USED BY THE CALLBACK SO
            THAT WE CAN USE THE getForceBetweenTheBodies TO GET THE FORCE BETWEEN THE BODIES*/
        //! Set the Force Between the Bodies
        virtual void setForceBetweenTheBodies(NewtonVector3 force);
        //! Get the origing of the joint in world space
        virtual NewtonVector3 getPivot() { return this->pivot * NewtonToRenderScale; }

    protected:
        // The origin of the joint in world space
        NewtonVector3 pivot;
        // The angular velocity between the bodies
        NewtonVector3 omega;
        // The force between the bodies
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
        //! Get the Ball And Socket CallBack
        virtual NewtonBallCallBack getBallAndSocketCallBack() { return this->pBallAndSocketCallBack; }
        //! Set the Ball And Socket CallBack
        virtual void setBallAndSocketCallBack(NewtonBallCallBack pBallAndSocketCallBack)
        {
            this->pBallAndSocketCallBack = pBallAndSocketCallBack;
            // Set the update callback for this joint
            NewtonBallSetUserCallback(this->pNewtonJoint, pBallAndSocketCallBack);
        }

    protected:
        // Local Reference to the Ball and Socket CallBack (This callback is triggered when either of the bodies that are part of the joint are moving)
        NewtonBallCallBack pBallAndSocketCallBack;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // PHYSICSBALLANDSOCKETJOINT_H
