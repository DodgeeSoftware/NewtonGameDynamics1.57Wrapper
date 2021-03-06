/**
  * @file   PhysicsRagDoll.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsRagDoll is a wrapper for functions relating to a
  * PhysicsRagDoll
**/

#ifndef PHYSICSRAGDOLL_H
#define PHYSICSRAGDOLL_H

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

// NEWTON WRAPPER INCLUDES
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"
#include "PhysicsRagDollBone.h"

/** @class PhysicsRagDoll
  * @brief Implement the PhysicsRagDoll to create a PhysicsRagDoll. To use this you'll want to either
  * create a custom scene node that has one of these as a member or alternatively this will form a base
  * for your custom scenenode **/
class PhysicsRagDoll
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        PhysicsRagDoll()
        {
            this->pNewtonRagDoll = 0;
            this->pTransformCallBack = 0;
            this->pForceAndTorqueCallBack = 0;
        }
        //! Destructor
        virtual ~PhysicsRagDoll() {}

    protected:
         // members and methods

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
          * @return NewtonWorld pointer **/
        virtual const NewtonWorld* getNewtonWorld() const { return this->pNewtonWorld; }
        /** @brief Set NewtonWorld
          * @param NewtonWorld **/
        virtual void setNewtonWorld(NewtonWorld* pNewtonWorld) { this->pNewtonWorld = pNewtonWorld; }

    protected:
        // Pointer to the Physics World
        NewtonWorld* pNewtonWorld;

    // *****************************
    // * GENERAL RAGDOLL FUNCTIONS *
    // *****************************
    public:
        /** @brief build the Ragdoll
          * @return true on success failse on failure**/
        virtual bool build()
        {
            // Validate required parameters
            if (this->pNewtonWorld == 0)
                return false;
            // Create the Rag Doll
            this->pNewtonRagDoll = NewtonCreateRagDoll(this->pNewtonWorld);
            // If the Doll was made then set the Transform CallBack for it (can be 0 and set later using the setTransformCallBack method)
            if (pNewtonRagDoll != 0 && this->pTransformCallBack != 0)
                NewtonRagDollSetTransformCallback(this->pNewtonRagDoll, this->pTransformCallBack);
            // If the doll was made return true otherwise return falase
            return (this->pNewtonRagDoll != 0);
        }
        /** @brief clear */
        virtual void clear()
        {
            // Destroy the rag doll
            NewtonDestroyRagDoll(this->pNewtonWorld, this->pNewtonRagDoll);
        }
        /** @brief Must call this function before adding joints to the Rag doll **/
        virtual void beginRagDoll()
        {
            // Begin the rag doll (allow joints to be added)
            NewtonRagDollBegin(this->pNewtonRagDoll);
        }
        /** @brief addBone
          * @param pParentRagDollBone parentragdollbone
          * @param matrix matrix4 transformation
          * @param pCollision Collision frame to use for the joint
          * @param size size of the bone (newton scale)**/ // TODO: document this better relative to parent?
        virtual PhysicsRagDollBone* addBone(NewtonRagDollBone* pParentRagDollBone, dFloat mass, NewtonMatrix4 matrix, NewtonCollision* pCollision, NewtonVector3 size)
        {
            // Validate required parameters
            if (this->pNewtonWorld == 0 || this->pNewtonRagDoll == 0)
                return 0;
            // Create a new PhysicsRagDollBone
            PhysicsRagDollBone* pPhysicsRagDollBone = new PhysicsRagDollBone();
            // Create a new NewtonRagDollBone
            NewtonRagDollBone* pNewtonRagDollBone = NewtonRagDollAddBone(this->pNewtonRagDoll, pParentRagDollBone, pPhysicsRagDollBone, mass, matrix.getPointer(), pCollision, size.getPointer());
            // Set the Newton World for the PhysicsRagDollBone
            pPhysicsRagDollBone->setNewtonWorld(this->pNewtonWorld);
            // Set the NewtonRagDoll for the PhysicsRagDollBone
            pPhysicsRagDollBone->setRagDoll(this->pNewtonRagDoll);
            // Set the NewtonRagDollBone for the PhysicsRagDollBone
            pPhysicsRagDollBone->setRagDollBone(pNewtonRagDollBone);
            // Return the new PhysicsRagDollBone
            return pPhysicsRagDollBone;
            /* TODO: Need to add Bones to an STL Vector
                or possibly a map by ID if we force all bones to have an ID (I think having an ID should be mandatory)*/
        }
        /** @brief Must call this function after you are finished adding joints to the Rag doll **/
        virtual void endRagDoll()
        {
            // End the rag doll (no more joints to submit)
            NewtonRagDollEnd(this->pNewtonRagDoll);
        }
        /** @brief Find a bone by ID
          * @param id **/
        virtual NewtonRagDollBone* findBone(int id)
        {
            // Validate required parameters
            if (this->pNewtonWorld == 0 || this->pNewtonRagDoll == 0)
                return 0;
            // Return either the NewtonRagDollBone if a bone with the ID was found or return 0
            return NewtonRagDollFindBone(this->pNewtonRagDoll, id);
        }

    protected:
        // Local reference to the NewtonRagDoll
        NewtonRagDoll* pNewtonRagDoll;

    // *************
    // * CALLBACKS *
    // *************
    public:
        /** @brief Get the transform Callback
          * @return the transform callback for the ragdoll **/
        virtual NewtonSetRagDollTransform getTransformCallBack() { return this->pTransformCallBack; }
        /** @brief Set the transform Callback
          * @param pCallback the transform callback for the ragdoll **/
        virtual void setTransformCallBack(NewtonSetRagDollTransform pCallBack)
        {
            // Set the local reference of the
            this->pTransformCallBack = pCallBack;
            // If there is a doll then set the transform callback for it
            if (pNewtonRagDoll != 0)
                NewtonRagDollSetTransformCallback(this->pNewtonRagDoll, this->pTransformCallBack);
        }
        /** @brief Get the ApplyForceAndTorque CallBack
          * @return the force and torque callback **/
        virtual NewtonApplyForceAndTorque getForceAndTorqueCallBack() { return this->pForceAndTorqueCallBack; }
        /** @brief Set ApplyForceAndTorque CallBack
          * @param pCallback the force and torque callback **/
        virtual void setForceAndTorqueCallBack(NewtonApplyForceAndTorque pCallBack)
        {
            // Set the local reference to the Fore and Torque Callback
            this->pForceAndTorqueCallBack = pCallBack;
            // If there is a doll then set the force and torque callback for it
            if (pNewtonRagDoll != 0)
                NewtonRagDollSetForceAndTorqueCallback(this->pNewtonRagDoll, this->pForceAndTorqueCallBack);
        }

    protected:
        // Rag Doll Transform CallBack
        NewtonSetRagDollTransform pTransformCallBack;
        // Apply force and torque CallBack
        NewtonApplyForceAndTorque pForceAndTorqueCallBack;

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

#endif // PHYSICSRAGDOLL_H
