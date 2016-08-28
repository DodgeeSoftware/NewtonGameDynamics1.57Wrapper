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

/** @class PhysicsRagDollBone
  * @brief The PhysicsRagDollBone is a wrapper around the NewtonRagDollBone
  * @detail Implement the PhysicsRagDollBone to create a PhysicsRagDollBone. To use this you'll want to either
  * create a custom scene node that has one of these as a member or alternatively this will form a base
  * for your custom scenenode **/
class PhysicsRagDollBone
{
    // ****************
    // * CONSTRUCTORS *
    // ****************
    public:
        //! Constructor
        PhysicsRagDollBone()
        {
            this->pNewtonWorld = 0;
            this->pNewtonRagDoll = 0;
            this->pRagDollBone = 0;
            this->id = -1;
        }
        //! Destructor
        virtual ~PhysicsRagDollBone() {}

    protected:
        //! Copy Constructor
        PhysicsRagDollBone(PhysicsRagDollBone* other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // members and methods

    protected:
        // members and methods

    // ****************
    // * NEWTON WORLD *
    // ****************
    public:
        /** @brief Get World
          * @return NewtonWorld **/
        virtual const NewtonWorld* getNewtonWorld() const { return this->pNewtonWorld; }
        /** @brief Set NewtonWorld
          * @param pNewtonWorld NewtonWorld **/
        virtual void setNewtonWorld(NewtonWorld* pNewtonWorld) { this->pNewtonWorld = pNewtonWorld; }

    protected:
        // Pointer to the Physics World
        NewtonWorld* pNewtonWorld;

    // ***********
    // * RAGDOLL *
    // ***********
    public:
        /** @brief Get the RagDoll associated with this bone
          * @return NewtonRagDoll **/
        NewtonRagDoll* getRagDoll() { return this->pNewtonRagDoll; }
        /** @brief Set the RagDoll associated with this bone
          * @param pNewtonRagDoll **/
        void setRagDoll(NewtonRagDoll* pNewtonRagDoll) { this->pNewtonRagDoll = pNewtonRagDoll; }

    protected:
        // Local Reference to the RagDoll
        NewtonRagDoll* pNewtonRagDoll;

    // ********
    // * BONE *
    // ********
    public:
        /** @brief Get the RagDoll Bone
          * @return NewtonRagDollBone pointer **/
        NewtonRagDollBone* getRagDollBone() { return this->pRagDollBone; }
        /** @brief Set the RagDoll Bone
          * @param pRagDollBone **/
        void setRagDollBone(NewtonRagDollBone* pRagDollBone) { this->pRagDollBone; }
        /** @brief Get UserData
          * @return void* userData **/
        void* getUserData()
        {
            // return the user data for the bone
            return NewtonRagDollBoneGetUserData(this->pRagDollBone);
        }
        /** @brief Get the NewtonBody for this Joint
          * @return The NewtonBody **/
        NewtonBody* pGetNewtonBody()
        {
            // Validate RagDollBone
            if (this->pRagDollBone == 0)
                return 0;
            // Return the NewtonBody Associated with this Joint
            return NewtonRagDollBoneGetBody(this->pRagDollBone);
        }
        /** @brief Set Limits for the bone
          * @param conDir cone direction
          * @param minConeAngle minimum cone angle
          * @param maxConeAngle max cone angle
          * @param maxTwistAngle **/
        void setLimits(NewtonVector3 conDir, dFloat minConeAngle, dFloat maxConeAngle, dFloat maxTwistAngle)
        {
            // Validate RagDollBone
            if (this->pRagDollBone == 0)
                return;
            // Set the limits for the bone
            NewtonRagDollBoneSetLimits(this->pRagDollBone, conDir.getPointer(), minConeAngle, maxConeAngle, maxTwistAngle, (dFloat*)0, 0, 0);
        }
        /** @brief Get the Bone's Local Matrix
          * @return NewtonMatrix4 representing the bone's local matrix **/
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
        /** @brief Get the Bone's World Matrix
          * @return NewtonMatrix4 representing the bones transform in world coordinates **/
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
        /** @brief Set the Bone's ID
          * @param id the bone's ID **/
        void setBoneID(int id)
        {
            NewtonRagDollBoneSetID (this->pRagDollBone, id);
            this->id = id;
        }

    protected:
        // Local Reference tot he RagDollBone
        NewtonRagDollBone* pRagDollBone;
        // ID for the Bone
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
