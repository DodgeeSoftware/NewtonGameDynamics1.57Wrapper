/**
  * @file   PhysicsRayDefault.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsRayDefault is an implementation of the base IPhysicsRay class.
  * This ray will fire through a scene between specified co-ordinates and will
  * stop scanning on the the first collision from the ending and will contain
  * impact data on the one impact only
**/

#ifndef PHYSICSRAYFURTHEST_H
#define PHYSICSRAYFURTHEST_H

#include <algorithm>
#include <iostream>
#include <vector>
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonGlobalScale.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"
#include "IPhysicsRay.h"

/** The PhysicsRayFurthest is a ray which goes through the scene striking everything it can. It stores
    only the furthest object hit in its impact data vector **/
class PhysicsRayFurthest : public IPhysicsRay
{
    // *****************************
    // * CONSTRUCTORs / DESRUCTORS *
    // *****************************
    public:
        //! Default Contructor
        PhysicsRayFurthest()
        {
            this->impactDataVector.clear();
        }
        //! Copy Constructor
        PhysicsRayFurthest(PhysicsRayFurthest& other)
        {
            this->pNewtonWorld = other.pNewtonWorld;
            this->start = other.start;
            this->end = other.end;
            this->impactDataVector = other.impactDataVector;
        }
        //! Default Destructor
        virtual ~PhysicsRayFurthest() {}

    protected:
        // methods and members

    // *********************
    // * RAYCAST FUNCTIONS *
    // *********************
    public:
        //! Execute the RayCast
        /** @brief This function will fire the ray from the start position to the end position
          * @param x0 starting x
          * @param y0 starting y
          * @param z0 starting z
          * @param x1 finishing x
          * @param z1 finished z
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
            if (impactDataVector.size() == 0) return false;
            // An interset of 1.0 is the furthest object along the ray
            float interset = 1.0f;
            // Find the closest object by comparing interset, the smallest value is the closest object in the list
            std::sort(this->impactDataVector.begin(), this->impactDataVector.end(), PhysicsRayImpactData::furthestToClosest);
            // Delete all but the furthest object hit
            if (this->impactDataVector.size() > 1) this->impactDataVector.erase(this->impactDataVector.begin() + 1, this->impactDataVector.end());
            // We Hit something
            return true;
        }

    // *********
    // * CLONE *
    // *********
    public:
        /** @brief Clone this ray (used by the physics debugger) **/
        virtual IPhysicsRay* clone() { return new PhysicsRayFurthest(*this); }

    // *************
    // * CALLBACKS *
    // *************
    public:
        /** @brief This Callback is used to exclude certain geometry from being hit by a ray,
          * @param body TODO: Comment me
          * @param hitNormal TODO: Comment me
          * @param collision TODO: Comment me
          * @param userData TODO: Comment me
          * @return return 1 to process 0 to stop **/
        virtual unsigned userRayPrefilterCallback(const NewtonBody* body, const NewtonCollision* collision, void* userData);
        /** @brief In this callback we grab information about the ray's impact with world geometry
          * @param pNewtonBody TODO: Comment me
          * @param hitNormal TODO: Comment me
          * @param collisionID TODO: Comment me
          * @param pUserData TODO: Comment me
          * @param intersetParam TODO: Comment me **/
        virtual float userRayFilterCallback(const NewtonBody* pNewtonBody, const dFloat* hitNormal, int collisionID, void* pUserData, dFloat intersetParam);
};

#endif // PHYSICSRAYFURTHEST_H
