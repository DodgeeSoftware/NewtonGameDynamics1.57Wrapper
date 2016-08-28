/**
  * @file   PhysicsRayDefault.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsRayDefault is an implementation of the base IPhysicsRay class.
  * This ray will fire through a scene between specified co-ordinates and will
  * produce information about all collisions between
**/

#ifndef PHYSICSRAYDEFAULT_H
#define PHYSICSRAYDEFAULT_H

// C++ Includes
#include <algorithm>
#include <iostream>
#include <vector>

// GAMEPHYSICS Includes
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonGlobalScale.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"
#include "IPhysicsRay.h"

/** @class PhysicsRayDefault
  * @brief The PhysicsDefaultRayCast is a wrapper around a basic physics ray
  * @detail The PhysicsDefaultRayCast is a ray which goes through the scene striking everything it can. It stores
    all the data in a list sorted from the closest to the furthest **/
class PhysicsRayDefault : public IPhysicsRay
{
    public:
        //! Default Contructor
        PhysicsRayDefault()
        {
            this->impactDataVector.clear();
        }
        //! Copy Constructor
        PhysicsRayDefault(PhysicsRayDefault& other)
        {
            this->pNewtonWorld = other.pNewtonWorld;
            this->start = other.start;
            this->end = other.end;
            this->impactDataVector = other.impactDataVector;
        }
        //! Default Destructor
        virtual ~PhysicsRayDefault() {}

    // CLONE
    public:
        //! Clone this ray (used by the physics debugger)
        virtual IPhysicsRay* clone() { return new PhysicsRayDefault(*this); }

    public:
        //! Execute the RayCast
        /**
          * @brief This function will fire the ray from the start position to the end position
          **/
        virtual bool execute(float x0, float y0, float z0, float x1, float y1, float z1, NewtonWorld* pNewtonWorld)
        {
            // If there is any information in the impact data vector then clear it
            this->impactDataVector.clear();
            // Set NewtonWorld
            this->pNewtonWorld = pNewtonWorld;
            // Build start vector
            this->start = NewtonVector3(x0, y0, z0);
            // Build end vector
            this->end = NewtonVector3(x1, y1, z1);
            //// Build the ray vector
            //this->rayVector = this->end - this->start;
            // Create the starting point for the ray
            float p1[3] = {this->start.getX(), this->start.getY(), this->start.getZ()};
            // Create the ending point for the ray
            float p2[3] = {this->end.getX(), this->end.getY(), this->end.getZ()};
            // Fire the Ray through the physics world
            NewtonWorldRayCast(this->pNewtonWorld, p1, p2, rayFilterCallback, this, rayPrefilterCallback);
            // If the impact data has any impact data in it then we hit something
            if (impactDataVector.size() == 0)
                return false;
            // An interset of 1.0 is the furthest object along the ray
            float interset = 1.0f;
            // Find the closest object by comparing interset, the smallest value is the closest object in the list
            std::sort(this->impactDataVector.begin(), this->impactDataVector.end(), PhysicsRayImpactData::closestToFurthest);
            // We Hit something
            return true;
        }

    public:
        //! This Callback is used to exclude certain geometry from being hit by a ray, return 1 to process 0 to stop
        virtual unsigned userRayPrefilterCallback(const NewtonBody* body, const NewtonCollision* collision, void* userData);
        //! In this callback we grab information about the ray's impact with world geometry
        virtual float userRayFilterCallback(const NewtonBody* pNewtonBody, const dFloat* hitNormal, int collisionID, void* pUserData, dFloat intersetParam);
};

#endif // PHYSICSRAYDEFAULT_H
