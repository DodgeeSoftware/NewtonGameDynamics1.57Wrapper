/**
  * @file   PhysicsRayImpactData.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsRayImpactData is a container for keeping track
  * of the impact between physics bodies and rays
**/

#ifndef PHYSICSRAYIMPACTDATA_H
#define PHYSICSRAYIMPACTDATA_H

// C++ Includes
#include <cstddef>

// NEWTON GAME DYNAMICS Includes
#include <newton.h>

// GAMEPYSICS Includes
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonGlobalScale.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"

/**
  * @brief this class is used to store information about where a ray has struck a physics body
  * @author Shem Taylor
  **/
class PhysicsRayImpactData
{
    public:
        //! Default constructor
        PhysicsRayImpactData()
        {
            this->pNewtonBody = 0;
            this->position = NewtonVector3(0.0f, 0.0f, 0.0f);
            this->normal = NewtonVector3(0.0f, 0.0f, 0.0f);
            this->collisionID = 0;
            this->intersetParam = 0;
        }
        //! Default destructor
        virtual ~PhysicsRayImpactData() {}

    // RAY IMPACT DATA ACCESSORS AND MUTATORS
    public:
        //! Get a pointer to the Newton body struck by this ray
        virtual const NewtonBody* getNewtonBody() const { return this->pNewtonBody; }
        //! Set the Newton body hit by this ray
        virtual void setNewtonBody(const NewtonBody* pNewtonBody) { this->pNewtonBody = pNewtonBody; }
        //! Get the position on the physics where this ray struck
        virtual const NewtonVector3 getPosition() const { return this->position; }
        //! Set the position on the physics body where the Ray struck
        virtual void setPosition(NewtonVector3 position) { this->position = position; }
        //! Get the normal at the position on the physics body where the Ray struck
        virtual const NewtonVector3& getNormal() const { return normal; }
        //! Set the normal at the position on the physics by the where the racetrack
        virtual void setNormal(NewtonVector3 normal) { this->normal = normal; }
        //! Get the collision ID
        virtual int getCollisionID() { return this->collisionID; }
        //! Set the collision ID
        virtual void setCollisionID(int collisionID) { this->collisionID = collisionID; }
        //! Get Distance between this point and the origin of the Ray
        virtual const float getIntersetParam() const { return this->intersetParam; }
        //! Set the distance between this point and the origin of the Ray
        virtual void setIntersetParam(float intersetParam) { this->intersetParam = intersetParam; }
        //! Get the RayVector
        NewtonVector3 getRayVector() { return this->rayVector; }
        //! Set the RayVector
        void setRayVector(NewtonVector3 rayVector) { this->rayVector = rayVector; }

    protected:
        //! Pointer to the Newton body struck by this ray
        const NewtonBody* pNewtonBody;
        //! Position that the ray struck on this Newton body
        NewtonVector3 position;
        //! The normal at the position this racetrack on this Newton body
        NewtonVector3 normal;
        //! convex primitive collision ID or face ID for collision trees
        int collisionID;
        //! the distance between the start of this ray and this point (used for sorting)
        float intersetParam;
        //! The ray vector
        NewtonVector3 rayVector;

    // IMPACT SORTING FUNCTIONS
    public:
        static bool closestToFurthest(const PhysicsRayImpactData& impact1, const PhysicsRayImpactData& impact2) { return (impact1.getIntersetParam() < impact2.getIntersetParam()); }
        static bool furthestToClosest(const PhysicsRayImpactData& impact1, const PhysicsRayImpactData& impact2) { return (impact1.getIntersetParam() > impact2.getIntersetParam()); }
};

#endif // PHYSICSRAYIMPACTDATA_H
