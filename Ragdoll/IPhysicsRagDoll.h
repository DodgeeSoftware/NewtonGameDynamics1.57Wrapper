/**
  * @file   IPhysicsRagDoll.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  IPhysicsRagDoll is base interface for Rag Dolls
**/

#ifndef IPHYSICSRAGDOLL_H
#define IPHYSICSRAGDOLL_H

// LUA BIND INCLUDES
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

// TODO: Consider Getting Rid of This
// TODO: implement me
/** @class IPhysicsRagDoll
  * @brief Implement the IPhysicsRagDoll to create a PhysicsRagDoll.**/
class IPhysicsRagDoll
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Constructor
        IPhysicsRagDoll();
        //! Destructor
        virtual ~IPhysicsRagDoll();

    protected:
        // Methods and members

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Methods and members

    protected:
        // Methods and members

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // IPHYSICSRAGDOLL_H
