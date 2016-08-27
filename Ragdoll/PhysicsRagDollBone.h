/**
  * @file   PhysicsRagDollBone.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsRagDollBone is a wrapper for functions relating to a
  * bone of a PhysicsRagDoll
**/

#ifndef PHYSICSRAGDOLLBONE_H
#define PHYSICSRAGDOLLBONE_H

// LUA BIND INCLUDES
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

// NEWTON WRAPPERS INCLUDES
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"

class PhysicsRagDollBone
{
    public:
        PhysicsRagDollBone()
        {
            this->pNewtonWorld = 0;
            this->pNewtonRagDoll = 0;
            this->pRagDollBone = 0;
            this->id = -1;
        }
        virtual ~PhysicsRagDollBone() {}

    // NEWTON WORLD
    public:
        //! Get World
        virtual const NewtonWorld* getNewtonWorld() const { return this->pNewtonWorld; }
        //! Set NewtonWorld
        virtual void setNewtonWorld(NewtonWorld* pNewtonWorld) { this->pNewtonWorld = pNewtonWorld; }

    protected:
        //! Pointer to the Physics World
        NewtonWorld* pNewtonWorld;

    // RAGDOLL
    public:
        //! Get the RagDoll associated with this bone
        NewtonRagDoll* getRagDoll() { return this->pNewtonRagDoll; }
        //! Set the RagDoll associated with this bone
        void setRagDoll(NewtonRagDoll* pNewtonRagDoll) { this->pNewtonRagDoll = pNewtonRagDoll; }

    protected:
        //! Local Reference to the RagDoll
        NewtonRagDoll* pNewtonRagDoll;

    // BONE
    public:
        //! Get the RagDoll Bone
        NewtonRagDollBone* getRagDollBone() { return this->pRagDollBone; }
        //! Set the RagDoll Bone
        void setRagDollBone(NewtonRagDollBone* pRagDollBone) { this->pRagDollBone; }
        //! Get UserData
        void* getUserData()
        {
            // return the user data for the bone
            return NewtonRagDollBoneGetUserData(this->pRagDollBone);
        }
        //! Get the NewtonBody for this Joint
        NewtonBody* pGetNewtonBody()
        {
            // Validate RagDollBone
            if (this->pRagDollBone == 0)
                return 0;
            // Return the NewtonBody Associated with this Joint
            return NewtonRagDollBoneGetBody(this->pRagDollBone);
        }
        //! Set Limits for the bone
        void setLimits(NewtonVector3 conDir, dFloat minConeAngle, dFloat maxConeAngle, dFloat maxTwistAngle)
        {
            // Validate RagDollBone
            if (this->pRagDollBone == 0)
                return;
            // Set the limits for the bone
            NewtonRagDollBoneSetLimits(this->pRagDollBone, conDir.getPointer(), minConeAngle, maxConeAngle, maxTwistAngle, (dFloat*)0, 0, 0);
        }
        //! Get the Bone's Local Matrix
        NewtonMatrix4 getLocalMatrix()
        {
            // Make a container for the local matrix
            NewtonMatrix4 matrix;
            // Validate RagDollBone
            if (this->pRagDollBone == 0)
                return matrix;
            // Get the local matrix
            NewtonRagDollBoneGetLocalMatrix(this->pRagDollBone, matrix.getPointer());
            // Return the local matrix
            return matrix;
        }
        //! Get the Bone's World Matrix
        NewtonMatrix4 getWorldMatrix()
        {
            // Make a container for the world matrix
            NewtonMatrix4 matrix;
            // Validate RagDollBone
            if (this->pRagDollBone == 0)
                return matrix;
            // Get the local matrix
            NewtonRagDollBoneGetGlobalMatrix(this->pRagDollBone, matrix.getPointer());
            // Return the world matrix
            return matrix;
        }
        //! Get the Bone's ID
        int getBoneID() { return this->id; }
        //! Set the Bone's ID
        void setBoneID(int id)
        {
            NewtonRagDollBoneSetID (this->pRagDollBone, id);
            this->id = id;
        }

    protected:
        //! Local Reference tot he RagDollBone
        NewtonRagDollBone* pRagDollBone;
        //! ID for the Bone
        int id;

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

#endif // PHYSICSRAGDOLLBONE_H
