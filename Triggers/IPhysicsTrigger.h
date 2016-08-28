/**
  * @file   IPhysicsTrigger.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  IPhysicsTrigger is an abstract class which contains
  * behaviour required to implement Volume Triggers
**/

#ifndef IPHYSICSTRIGGER_H
#define IPHYSICSTRIGGER_H

// C++ Includes
#include <iostream>

// NEWTON INCLUDES
#include <cstddef>
#include <newton.h>

// NEWTON WRAPPER INCLUDES
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"
#include "PhysicsCollisionFrame.h"

/* TODO: Get and set Mesh as void* (NOTE: IMeshSceneNodes and IAnimatedMeshSceneNodes will not inherit this class, so no problems with prototype conflicts)
    in the inheritance hierarchies */

/** @class IPhysicsTrigger
  * @brief An interface definition for a IPhysicsTrigger
  * @detail This class defines all the basic and mandatory
  * functions to implement for a PhysicsTrigger **/
class IPhysicsTrigger : public PhysicsCollisionFrame
{
    public:
        //! Default Contructor
        IPhysicsTrigger()
        {
            this->enterFlag = false;
            this->insideFlag = false;
            this->exitFlag = false;
            this->enabled = true;
            this->pMesh = 0;
        }
        //! Destructor
        virtual ~IPhysicsTrigger() {}

    // GENERAL FUNCTIONS
    public:
        //! Initialise Trigger
        virtual bool init() = 0;
        //! Clean up the trigger
        virtual void free() = 0;
        //! Reset the trigger
        virtual void reset()
        {
            this->enterFlag = false;
            this->insideFlag = false;
            this->exitFlag = false;
            this->enabled = true;
        }

        //! Test this trigger against a NewtonCollisionFrame
        virtual void test(NewtonCollision* pOtherNewtonCollision, NewtonMatrix4 otherMatrix) = 0;

    // TRIGGER CALLBACKS
    public:
        //! CallBack for when the Player first enters the trigger volume
        virtual void onEnter() = 0;
        //! CallBack for when the Player is inside the trigger volume
        virtual void onInside() = 0;
        //! CallBack for when the Player has just left the trigger volume
        virtual void onExit() = 0;

    // STATE FLAGS
    public:
        //! Get the status of the enter flag
        virtual bool getEnterFlag() { return enterFlag; }
        //! Set the state of the enter flag
        virtual void setEnterFlag(bool enterFlag) { this->enterFlag = enterFlag; }
        //! Get the status of the inside flag
        virtual bool getInsideFlag() { return insideFlag; }
        //! Set the state of the inside flag
        virtual void setInsideFlag(bool insideFlag) { this->insideFlag = insideFlag; }
        //! Get the status of the exit flag
        virtual bool getExitFlag() { return exitFlag; }
        //! Set the status of the exit flag
        virtual void setExitFlag(bool exitFlag) { this->exitFlag = exitFlag; }
        //! Check to see if this trigger is Enabled
        virtual bool isEnabled() { return this->enabled; }
        //! Enable/Disable this tigger
        void setEnabled(bool enabled) { this->enabled = enabled; }
        //! Enable this tigger
        virtual void enable() { this->enabled = true; }
        //! Disable this tigger
        virtual void disable() { this->enabled = false; }

    protected:
        // Flag to keep track of onEnter events
        bool enterFlag;
        // Flag to keep track of onInside events
        bool insideFlag;
        // Flag to keep track of onExit events
        bool exitFlag;
        // Keep track of the triggers enabled/disabled status
        bool enabled;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState)
        {
            // TODO: implement me
        }
};

#endif // IPHYSICSTRIGGER_H
