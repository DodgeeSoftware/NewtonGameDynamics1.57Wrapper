/**
  * @file   NewtonFreezeThreshold.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  NewtonFreezeThreshold is a simple class defining
  * parametres for the FreezeThreshold of physics bodies. When
  * a NewtonBody / PhysicsBody has autofreeze turned on, these
  * thresholds are used to 'freeze' an object haulting calculations
  * until some kind of force disturbs the Body to unfreeze it
*/

#ifndef NEWTONFREEZETHRESHOLD_H
#define NEWTONFREEZETHRESHOLD_H

// LUA BIND INCLUDES
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

// C++ INCLUDES
#include <cmath>

// NEWTON INCLUDES
#include <cstddef>
#include <newton.h>

// TODO: comment me
class NewtonFreezeThreshold
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        NewtonFreezeThreshold()
        {
            velocityThreshold = 0.0f;
            angularVelocityThreshold = 0.0f;
        }
        //! Constructor
        NewtonFreezeThreshold(dFloat velocityThreshold, dFloat angularVelocityThreshold)
        {
            this->velocityThreshold = velocityThreshold;
            this->angularVelocityThreshold = angularVelocityThreshold;
        }

        //! Destructor
        virtual ~NewtonFreezeThreshold() {}

    protected:
        // methods and members

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Methods and Members

    protected:
        // Methods and Members

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Get Velocity Threshold
        virtual dFloat getVelocityThreshold() { return this->velocityThreshold; }
        //! Set Velocity Threshold
        virtual void setVelocityThreshold(dFloat angularVelocityThreshold) { this->velocityThreshold = velocityThreshold; }
        //! Get Angular Velocity Threshold
        virtual dFloat getAngularVelocityThreshold() { return this->angularVelocityThreshold; }
        //! Set Angular Velocity Threshold
        virtual void setAngularVelocityThreshold(dFloat angularVelocityThreshold) { this->angularVelocityThreshold = angularVelocityThreshold; }

    protected:
        // Velocity threshHold
        dFloat velocityThreshold;
        // Angular Velocity Threshold
        dFloat angularVelocityThreshold;

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

#endif // NEWTONFREEZETHRESHOLD_H
