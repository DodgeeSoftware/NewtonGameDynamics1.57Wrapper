/**
  * @file   IPhysicsVehicle.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  IPhysicsVehicle is an interface class for our PhysicsVehicle
*/

#ifndef IPHYSICSVEHICLE_H
#define IPHYSICSVEHICLE_H

// LUA BIND INCLUDES
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

// TODO: implement this class por get rid of it
// TODO: Comment me
class IPhysicsVehicle
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constuctor
        IPhysicsVehicle()
        {

        }
        //! Destructor
        virtual ~IPhysicsVehicle() {}

    protected:
        // methods and members

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // methods and members

    protected:
        // methods and members

    // ***********
    // * GENERAL *
    // ***********
    public:
        //! Clone this vehicle
        virtual IPhysicsVehicle* clone() = 0;

    protected:
        // methods and members

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // IPHYSICSVEHICLE_H
