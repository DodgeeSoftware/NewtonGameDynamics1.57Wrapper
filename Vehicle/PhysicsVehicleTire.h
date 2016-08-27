/**
  * @file   PhysicsVehicleTire.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsVehicleTire is a wrapper for a special type of NewtonJoint
  * vehicles are build up heirachially of tires attached to a body
*/

#ifndef PHYSICSVEHICLETIRE_H
#define PHYSICSVEHICLETIRE_H

// C++ Includes
#include <cstddef>
// NEWTON GAME DYNAMICS Includes
#include <newton.h>

// LUA BIND INCLUDES
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

/**
// TODO: Comment me
**/
class PhysicsVehicleTire
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        PhysicsVehicleTire()
        {
            this->pVehicleJoint = 0;
        }
        //! Destructor
        virtual ~PhysicsVehicleTire() {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // methods and members

    protected:
        // methods and members

    // ****************
    // * NEWTON WORLD *
    // ****************
    public:
        //! Get World
        virtual const NewtonWorld* getNewtonWorld() const
        {
            return this->pNewtonWorld;
        }
        //! Set NewtonWorld
        virtual void setNewtonWorld(NewtonWorld* pNewtonWorld) { this->pNewtonWorld = pNewtonWorld; }

    protected:
        //! Pointer to the Physics World
        NewtonWorld* pNewtonWorld;

    protected:
        NewtonJoint* pVehicleJoint;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // PHYSICSVEHICLETIRE_H
