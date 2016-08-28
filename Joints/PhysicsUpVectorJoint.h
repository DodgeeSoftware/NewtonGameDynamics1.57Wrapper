/**
  * @file   PhysicsUpVectorJoint.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsUpVectorJoint implements an IPhysicsJoint and
  * functions as if a sharp pin was push into an object and on the other
  * side was a corkboard. Objects are free to rotate on the pin axis but
  * movements or rotations that will affect its alignment will be nullified
**/

#ifndef PHYSICSUPVECTORJOINT_H
#define PHYSICSUPVECTORJOINT_H

// C++ Includes
#include <iostream>

// LUA BIND Includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
// LUABIND Includes
#include <luabind/luabind.hpp>

// NEWTON Includes
#include <cstddef>
#include <Newton.h>

// GAMEPHYSICS Includes
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonGlobalScale.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"
#include "IPhysicsJoint.h"

/** @class PhysicsUpVectorJoint
  * @brief The PhysicsUpVectorJoint is a wrapper around the Newton UniversalJoint
  * @detail The PhysicsUpVectorJoint is a container for a joint that places a pin
    constraint on a physics body **/
class PhysicsUpVectorJoint : public IPhysicsJoint
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default constructor
        PhysicsUpVectorJoint()
        {
            this->pNewtonBody = 0;
        }
        //! Destructor
        virtual ~PhysicsUpVectorJoint() {}

    // ********
    // * TYPE *
    // ********
    public:
        //! Get Joint type
        virtual E_JOINT_TYPE getType() { return JT_UP; }

    protected:
        // members and methods

    // ******************
    // * JOINT CREATION *
    // ******************
    public:
        //! Setup up vector joint
        virtual bool build(NewtonVector3 pin, NewtonBody* pParentNewtonBody);

    protected:
        // members and methods

    // ********************
    // * JOINT PROPERTIES *
    // ********************
    public:
        //! Get the pin for this joint
        virtual NewtonVector3 getPin();
        //! Set the pin for this joint
        virtual void setPin(NewtonVector3 pin);

    protected:
        // Keep a local reference to the pin
        NewtonVector3 pin;

    // *************************
    // * NEWTON BODY ACCESSORS *
    // *************************
    public:
        //! Get the NewtonBody
        virtual NewtonBody* getNewtonBody() { return this->pNewtonBody; }

    protected:
        // The Parent NewtonBody this joint is connected to
        NewtonBody* pNewtonBody;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // PHYSICSUPVECTORJOINT_H
