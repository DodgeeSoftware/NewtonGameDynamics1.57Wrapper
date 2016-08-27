#include "IPhysicsRay.h"

// Example of how to fire a ray through the scene
//bool IPhysicsRay::execute()
//{
//    float p1[3] = {this->startPosition.getX() * RenderScaleToNewton, this->startPosition.getY() * RenderScaleToNewton, this->startPosition.getZ() * RenderScaleToNewton };
//    float p2[3] = {this->endPosition.getX() * RenderScaleToNewton, this->endPosition.getY() * RenderScaleToNewton, this->endPosition.getZ() * RenderScaleToNewton };
//    NewtonWorldRayCast(this->pNewtonWorld, p1, p2, rayFilterCallback, this, rayPrefilterCallback);
//}

unsigned IPhysicsRay::rayPrefilterCallback(const NewtonBody* pNewtonBody, const NewtonCollision* pNewtonCollision, void* pUserData)
{
    // typecast the use of data
    IPhysicsRay* pRay = (IPhysicsRay*)pUserData;
    // send incoming traffic to the appropriate Ray instance
    return pRay->userRayPrefilterCallback(pNewtonBody, pNewtonCollision, pUserData);
}

float IPhysicsRay::rayFilterCallback(const NewtonBody* pNewtonBody, const dFloat* hitNormal, int collisionID, void* pUserData, dFloat intersetParam)
{
    // typecast the use of data
    IPhysicsRay* pRay = (IPhysicsRay*)pUserData;
    // send incoming traffic to the appropriate Ray instance
    return pRay->userRayFilterCallback(pNewtonBody, hitNormal, collisionID, pUserData, intersetParam);

}
