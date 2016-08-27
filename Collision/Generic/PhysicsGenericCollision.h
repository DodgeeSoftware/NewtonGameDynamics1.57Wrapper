/**
  * @file   PhysicsGenericCollision.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsGenericCollision is an implementation of the
  * Generic Collision System of Newton Game Dynamics. It allows you
  * to simple use NewtonCollision / PhysicsCollision objects as
  * collidable objects and to perform your own calculations on them
**/

#ifndef PHYSICSGENERICCOLLISION_H
#define PHYSICSGENERICCOLLISION_H

// C++ Includes
#include <cstddef>
// LUA Includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
// LUA BIND Includes
#include <luabind/luabind.hpp>
// NEWTON GAME DYNAMICS Includes
#include <newton.h>
// GAMEPHYSICS Includes
#include "NewtonUtils.h"
#include "PhysicsCollisionFrame.h"
#include "PhysicsCollisionFrameRayImpactData.h"
#include "PhysicsCollisionFrameCollide.h"
#include "PhysicsCollisionFrameClosestPoint.h"
#include "PhysicsCollisionFrameClosestPoints.h"

// /** The PhysicsGenericCollision is a class which implements the generic collision interface of the newton library. This aspect of the library
//    enables you to use NewtonCollision Objects independently of physics bodies and be able to perform limited collision testing with them**/
//class PhysicsGenericCollision
//{
//    public:
//        //! Default Constructor
//        PhysicsGenericCollision()
//        {
//            this->pNewtonWorld = 0;
//        }
//        //! Destructor
//        ~PhysicsGenericCollision() {}
//
//    public:
//        //! Get the NewtonWorld
//        NewtonWorld* getNewtonWorld() { return this->pNewtonWorld; }
//        //! Set the NewtonWorld
//        void setNewtonWorld(NewtonWorld* pNewtonWorld) { this->pNewtonWorld = pNewtonWorld; }
//    public:
//        //! Collide this Collision Frame with another collision frame
//        /** collisionData is an array of size maxContacts to hold the contact data
//            and pPhysicsCollision frame is the other collision primitive to test against
//            (returns the number of contacts; sample limited by maxContacts) **/
//        int collide(PhysicsCollisionFrame* pPhysicsCollisionFrame1, PhysicsCollisionFrame* pPhysicsCollisionFrame2, int maxContacts, std::vector<PhysicsCollisionFrameCollide>& collisionData);
//        //! RayCast (fires a ray at a collision frame, the co-ordinates are in local space rather than world space)
//        bool rayCast(PhysicsCollisionFrame* pPhysicsCollisionFrame, float x0, float y0, float z0, float x1, float y1, float z1, PhysicsCollisionFrameRayImpactData& rayCastData);
//        //! Find the closest point (returns the closest point to object 1 and object 2 and the vector which would seperate the two
//        bool closestPointQuery(PhysicsCollisionFrame* pPhysicsCollisionFrame1, PhysicsCollisionFrame* pPhysicsCollisionFrame2, PhysicsCollisionFrameClosestPoints* closestPointsData);
//        //! Find the closest point
//        bool closestPointQuery(PhysicsCollisionFrame* pPhysicsCollisionFrame, float x, float y, float z, PhysicsCollisionFrameClosestPoint* closestPointData);
//        //! Calculate the time of impact and contact points between this PhysicsCollisionFrame and another PhysicsCollisionFrame
//        float collideContinue(int maxContacts, float timeStep, PhysicsCollisionFrame* pPhysicsCollisionFrame, PhysicsCollisionFrameClosestPoint* closestPointData);
//
//    private:
//        NewtonWorld* pNewtonWorld;
//};

#endif // PHYSICSGENERICCOLLISION_H
