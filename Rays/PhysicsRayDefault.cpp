#include "PhysicsRayDefault.h"

unsigned PhysicsRayDefault::userRayPrefilterCallback(const NewtonBody* pNewtonBody, const NewtonCollision* collision, void* userData)
{
    /* Returning 1 means process this in the userRayFilterCallback callback
        returning 0 means don't process this in the userRayFilterCallback callback */
    return 1;
}

float PhysicsRayDefault::userRayFilterCallback(const NewtonBody* pNewtonBody, const dFloat* hitNormal, int collisionID, void* pUserData, dFloat intersetParam)
{
    // instantiate an impact data class to contain information about this collision of the Ray
    PhysicsRayImpactData impactData;
    // set the Newton body that this ray has struck
    impactData.setNewtonBody(pNewtonBody);
    // calculate the exact position of impact
    NewtonVector3 impactPosition = (this->start + (this->end - this->start) * intersetParam);
    // set the position of impact of this ray
    impactData.setPosition(impactPosition);
    // Create a container for the normal
    NewtonVector3 normal = NewtonVector3(hitNormal[0], hitNormal[1], hitNormal[2]);
    // Make the normal a unit vector
    normal.normalise();
    // set the coordinates of the normal at the point this ray has struck
    impactData.setNormal(normal);
    // set the distance between the start of the ray and this point
    impactData.setIntersetParam(intersetParam);
    // set the collision ID for the convex Hull or tree collision the Ray has struck
    impactData.setCollisionID(collisionID);
    // Grab the instance of the ray
    PhysicsRayDefault* pPhysicsRayDefault = (PhysicsRayDefault*)(pUserData);
    // save the ray vector
    impactData.setRayVector(pPhysicsRayDefault->getRayVector());
    // save the impact data
    impactDataVector.push_back(impactData);
    /* if this function returns a zero then it will not process any further collisions for this ray.
        it is common practice to use the collision ID and a switch statement to terminate a ray */
    return 1.0;
}
