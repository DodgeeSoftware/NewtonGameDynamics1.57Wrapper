/**
  * @file   IPhysicsRay.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  IPhysicsRay is an inteface class which contains
  * the basic interface for a physics ray in Newton Game Dynamics
**/

#ifndef IPHYSICSRAY_H
#define IPHYSICSRAY_H

// C++ Includes
#include <vector>
#include <cstddef>

// NEWTON GAME DYNAMICS Includes
#include <newton.h>

// GAME PHYSICS INCLUDES
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonGlobalScale.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"
#include "PhysicsRayImpactData.h"

/**
  * @brief The base physics raycast class - provides basic functionality for firing rays in 3d space
  * @author Shem Taylor
  **/
class IPhysicsRay
{
    public:
        //! Default Constructor
        IPhysicsRay()
        {
            this->pNewtonWorld = 0;
            this->start = NewtonVector3(0.0, 0.0, 0.0);
            this->end = NewtonVector3(0.0, 0.0, 0.0);
        }
        //! Destructor
        virtual ~IPhysicsRay() {}

    // EXECUTE THE RAY
    public:
        //! Fire the ray through the NewtonWorld
        virtual bool execute(float x0, float y0, float z0, float x1, float y1, float z1, NewtonWorld* pNewtonWorld) = 0;

    // NEWTON WORLD
    public:
        //! Get the NewtonWorld
        virtual const NewtonWorld* getNewtonWorld() { return this->pNewtonWorld; }

    protected:
        //! Maintain a pointer to the Newton world
        NewtonWorld* pNewtonWorld;

    // RAY START AND END
    public:
        //! Get the start of the ray in renderscale
        virtual const NewtonVector3& getStart() const { return this->start; }
        //! Get the end of the ray in renderscale
        virtual const NewtonVector3& getEnd() const { return this->end; }
        //! Get the ray vector
        NewtonVector3 getRayVector()
        {
            NewtonVector3 rayVector = (this->end - this->start);
            return rayVector;
        }
        //! Get the ray vector
        NewtonVector3 getNormalisedRayVector()
        {
            NewtonVector3 normalisedRayVector = this->start - this->end;
            normalisedRayVector.normalise();
            return normalisedRayVector;
        }

    protected:
        //! Vector for the starting coordinate of this ray
        NewtonVector3 start;
        //! Vector for the ending coordinate of this ray
        NewtonVector3 end;
        ////! vector for the ray
        //NewtonVector3 rayVector;

    // IMPACT DATA
    public:
        //! Get a reference to the impactDataVector
        virtual std::vector<PhysicsRayImpactData>& getImpactDataVector() { return this->impactDataVector; }

    protected:
        std::vector<PhysicsRayImpactData> impactDataVector;
    // PURE VIRTUAL CALLBACK MUST BE IMPLEMENTED IN CHILD CLASSES
    public:
        //! The user ray prefilter callback
        /**
          * @brief Derived classes must implement a userRayPrefilterCallback. This function is used to exclude Newton Bodies from being included in the ray cast
          * @param body A pointer to the newton body
          * @param collision A pointer to the collision data
          * @param userData A pointer to the user data
          * @return the result of the routed function
          **/
        virtual unsigned userRayPrefilterCallback(const NewtonBody* body, const NewtonCollision* collision, void* userData) = 0;

        //! The user ray filter callback
        /**
          * @brief Derived classes must implement a userRayFilterCallback. This function is used to collect information on a ray which is intersecting a Newton Body
          * @param body A pointer to the newton body
          * @param hitNormal An array of floats that make up the normal of impact
          * @param collisionID The ID of the collision
          * @param userData A pointer to the user data
          * @param intersetParam An array of floats that make up the intersect parameters
          * @return the result of the routed function
          **/
        virtual float userRayFilterCallback(const NewtonBody* pNewtonBody, const dFloat* hitNormal, int collisionID, void* pUserData, dFloat intersetParam) = 0;

    public:
        //! Clone this ray (used by the physics debugger)
        virtual IPhysicsRay* clone() = 0;

    /* These static callbacks function to route traffic from the IPhysicsRayCast scope to the Implemented Ray class
        the implemented ray determines behaviour like when the ray should stop and also builds the PhysicsRayImpactData
        information so we have data to query about this ray*/
    // STATIC CALL BACK ROUTERS
    public:
        //! The ray prefilter callback
        /**
          * @brief This call back is triggered when the ray collides with an axis aligned bounding box of an physics body
          * @param body A pointer to the newton body
          * @param collision A pointer to the collision data
          * @param userData A pointer to the user data
          * @return the result of the routed function
          **/
        static unsigned rayPrefilterCallback(const NewtonBody* pNewtonBody, const NewtonCollision* pNetwonCollision, void* pUserData);

        //! The ray filter callback
        /**
          * @brief This callback is triggered when they ray has collided with a physics body
          * @param body A pointer to the newton body
          * @param hitNormal An array of floats that make up the normal of impact
          * @param collisionID The ID of the collision
          * @param userData A pointer to the user data
          * @param intersetParam An array of floats that make up the intersect parameters
          * @return the result of the routed function
          **/
        static float rayFilterCallback(const NewtonBody* pNewtonBody, const dFloat* hitNormal, int collisionID, void* pUserData, dFloat intersetParam);
};

#endif // IPHYSICSRAY_H
