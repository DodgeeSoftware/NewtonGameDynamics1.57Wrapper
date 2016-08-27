/**
  * @file   PhysicsCustomJoint.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsCustomJoint implements an IPhysicsJoint and
  * should be used as a Base Class when you are trying to implement
  * your own custom joint. Custom Joints can be things such as 'motors'
**/

#ifndef PHYSICSCUSTOMJOINT_H
#define PHYSICSCUSTOMJOINT_H

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
  * @brief A PhysicsCumstomJoint restricts the movement two newton bodies with a joint.
  * This is a special joint with user defined parameters. Its important to know when using
  * this joint that you must set the callback before you build the joint. This is because
  * the underlying function in NewtonGameDynamics sets the callback at time of constructor
  * of the joint
  * @author Shem Taylor
  **/
class PhysicsCustomJoint : public IPhysicsJoint
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default constructor
        PhysicsCustomJoint()
        {
            this->pParentNewtonBody = 0;
            this->pChildNewtonBody = 0;
            this->pCustomJointCallBack = 0;
        }
        //! Destructor
        virtual ~PhysicsCustomJoint() {}

    protected:
        // members and methods

    // ********
    // * TYPE *
    // ********
    public:
        //! Get Joint type
        virtual E_JOINT_TYPE getType() { return JT_CUSTOM; }

    protected:
        // members and methods

    // ************
    // * CREATION *
    // ************
    public:
        //! Build the joint
        virtual bool build(int degreesOfFreedom, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody);

    protected:
        // members and methods

    // **************
    // * PROPERTIES *
    // **************
    public:
        //! Function only effective when called from userBilateralCallBack. Add linear row
        virtual void addLinearRow(NewtonVector3 pivot0, NewtonVector3 pivot1, NewtonVector3 direction);
        //! Function only effective when called from userBilateralCallBack. Add angular row
        virtual void addAngularRow(float relativeAngleError, NewtonVector3 pin);
        //! Function only effective when called from userBilateralCallBack. Add general row
        virtual void addGeneralRow(NewtonVector3 jacobian0, NewtonVector3 jacobian1);
        //! Set the minimum friction value the solver is allow to apply to the joint row
        virtual void setRowMinimumFriction(float friction);
        //! Set the maximum friction value the solver is allow to apply to the joint row
        virtual void setRowMaximumFriction(float friction);
        //! Set the value for the desired acceleration for the current constraint row
        virtual void setRowAcceleration(float acceleration);
        //! Set the maximum percentage of the constraint force that will be applied to the constraint row
        virtual void setRowStiffness(float stiffness);
        //! Calculates the row acceleration to satisfy the specified the spring damper system
        virtual void setRowSpringDamperAcceleration(float springK, float springD);
        //! Return the magnitude previews force or torque value calculated by the solver for this contraint row.
        virtual float getRowForce(int row);
        //! Get the Degrees of Freedom
        int getDegreesOfFreedom() { return this->degreesOfFreedom; }

    protected:
        // Comment me
        int degreesOfFreedom;

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
        //! Get the Ball And Socket CallBack
        NewtonUserBilateralCallBack  getUserBilateralCallBack() { return this->pCustomJointCallBack; }
        //! Set the Ball And Socket CallBack (this function doesn't set the callback, the creation function does so call this before creating the joint)
        void setUserBilateralCallBack(NewtonUserBilateralCallBack pCustomJointCallBack)
        {
            this->pCustomJointCallBack = pCustomJointCallBack;
        }

    protected:
        // Local Reference to the Ball and Socket CallBack
        NewtonUserBilateralCallBack  pCustomJointCallBack;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // PHYSICSCUSTOMJOINT_H
