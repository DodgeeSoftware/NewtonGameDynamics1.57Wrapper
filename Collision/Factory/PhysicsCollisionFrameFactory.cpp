#include "PhysicsCollisionFrameFactory.h"

//bool PhysicsCollisionFrameFactory::init()
//{
//    // success
//    return true;
//}
//
//void PhysicsCollisionFrameFactory::free()
//{
//    this->pNewtonWorld = 0;
//}

NewtonCollision* PhysicsCollisionFrameFactory::createNullCollisionFrame()
{
    NewtonCollision* pNewtonCollision = NewtonCreateNull(this->pNewtonWorld);
    NewtonConvexCollisionSetUserID(pNewtonCollision, PCFT_NULL);
    return pNewtonCollision;
}


NewtonCollision* PhysicsCollisionFrameFactory::createBoxCollisionFrame(float sizeX, float sizeY, float sizeZ)
{
    NewtonMatrix4 offset;
    offset.makeIdentity();
    return this->createBoxCollisionFrame(sizeX, sizeY, sizeZ, offset);
}

NewtonCollision* PhysicsCollisionFrameFactory::createBoxCollisionFrame(float sizeX, float sizeY, float sizeZ, NewtonMatrix4 offset)
{
    NewtonCollision* pNewtonCollision = NewtonCreateBox(this->pNewtonWorld, sizeX * RenderScaleToNewton, sizeY * RenderScaleToNewton, sizeZ * RenderScaleToNewton, offset.getPointer());
    NewtonConvexCollisionSetUserID(pNewtonCollision, PCFT_BOX);
    return pNewtonCollision;
}

NewtonCollision* PhysicsCollisionFrameFactory::createSphereCollisionFrame(float size)
{
    NewtonMatrix4 offset;
    offset.makeIdentity();
    return this->createSphereCollisionFrame(size, size, size, offset);
}

NewtonCollision* PhysicsCollisionFrameFactory::createSphereCollisionFrame(float sizeX, float sizeY, float sizeZ)
{
    NewtonMatrix4 offset;
    offset.makeIdentity();
    return this->createSphereCollisionFrame(sizeX, sizeY, sizeZ, offset);
}

NewtonCollision* PhysicsCollisionFrameFactory::createSphereCollisionFrame(float sizeX, float sizeY, float sizeZ, NewtonMatrix4 offset)
{
    NewtonCollision* pNewtonCollision = NewtonCreateSphere(this->pNewtonWorld, sizeX * RenderScaleToNewton, sizeY * RenderScaleToNewton, sizeZ * RenderScaleToNewton, offset.getPointer());
    NewtonConvexCollisionSetUserID(pNewtonCollision, PCFT_SPHERE);
    return pNewtonCollision;
}

NewtonCollision* PhysicsCollisionFrameFactory::createConeCollisionFrame(float radius, float height)
{
    NewtonMatrix4 offset;
    offset.makeIdentity();
    return this->createConeCollisionFrame(radius, height, offset);
}

NewtonCollision* PhysicsCollisionFrameFactory::createConeCollisionFrame(float radius, float height, NewtonMatrix4 offset)
{
    NewtonCollision* pNewtonCollision = NewtonCreateCone(this->pNewtonWorld, radius * RenderScaleToNewton, height * RenderScaleToNewton, offset.getPointer());
    NewtonConvexCollisionSetUserID(pNewtonCollision, PCFT_CONE);
    return pNewtonCollision;
}

NewtonCollision* PhysicsCollisionFrameFactory::createCapsuleCollisionFrame(float radius, float height)//, matrix4 offset)
{
    NewtonMatrix4 offset;
    offset.makeIdentity();
    return this->createCapsuleCollisionFrame(radius, height, offset);
}

NewtonCollision* PhysicsCollisionFrameFactory::createCapsuleCollisionFrame(float radius, float height, NewtonMatrix4 offset)
{
    NewtonCollision* pNewtonCollision = NewtonCreateCapsule(this->pNewtonWorld, radius * RenderScaleToNewton, height * RenderScaleToNewton, offset.getPointer());
    NewtonConvexCollisionSetUserID(pNewtonCollision, PCFT_CAPSULE);

// NOTE: Doesn't recalculate the AABB for the capsule :(
//    NewtonAABB aabb;
//    NewtonCollisionCalculateAABB(pNewtonCollision, offset.getPointer(), aabb.getMinEdge(), aabb.getMaxEdge());

//// NOTE: Doesn't recalculate the AABB for the capsule :(
//    float junk[16];
//    NewtonConvexHullModifierGetMatrix(pNewtonCollision, junk);
//    NewtonConvexHullModifierSetMatrix(pNewtonCollision, offset.getPointer());
    return pNewtonCollision;
}

NewtonCollision* PhysicsCollisionFrameFactory::createCylinderCollisionFrame(float radius, float height)//, matrix4 offset)
{
    NewtonMatrix4 offset;
    offset.makeIdentity();
    return this->createCylinderCollisionFrame(radius, height, offset);
}

NewtonCollision* PhysicsCollisionFrameFactory::createCylinderCollisionFrame(float radius, float height, NewtonMatrix4 offset)
{
    NewtonCollision* pNewtonCollision = NewtonCreateCylinder(this->pNewtonWorld, radius * RenderScaleToNewton, height * RenderScaleToNewton, offset.getPointer());
    NewtonConvexCollisionSetUserID(pNewtonCollision, PCFT_CYLINDER);
    return pNewtonCollision;
}

NewtonCollision* PhysicsCollisionFrameFactory::createChampherCylinderCollisionFrame(float radius, float height)//, matrix4 offset)
{
    NewtonMatrix4 offset;
    offset.makeIdentity();
    return this->createChampherCylinderCollisionFrame(radius, height, offset);
}

NewtonCollision* PhysicsCollisionFrameFactory::createChampherCylinderCollisionFrame(float radius, float height, NewtonMatrix4 offset)
{
    NewtonCollision* pNewtonCollision = NewtonCreateChamferCylinder(this->pNewtonWorld, radius * RenderScaleToNewton, height * RenderScaleToNewton, offset.getPointer());
    NewtonConvexCollisionSetUserID(pNewtonCollision, PCFT_CHAMPHER_CYLINDER);
    return pNewtonCollision;
}

NewtonCollision* PhysicsCollisionFrameFactory::createConvexHullCollisionFrame(int vertexCount, float* vertexArray)
{
    NewtonMatrix4 offset;
    offset.makeIdentity();
    return this->createConvexHullCollisionFrame(vertexCount, vertexArray, offset);
}

NewtonCollision* PhysicsCollisionFrameFactory::createConvexHullCollisionFrame(int vertexCount, float* vertexArray, NewtonMatrix4 offset)
{
    NewtonCollision* pNewtonCollision = NewtonCreateConvexHull(this->pNewtonWorld, vertexCount, vertexArray, sizeof(float) * 3, offset.getPointer());
    NewtonConvexCollisionSetUserID(pNewtonCollision, PCFT_CONVEX_HULL);
    return pNewtonCollision;
}


NewtonCollision* PhysicsCollisionFrameFactory::createCompoundCollisionFrame(NewtonCollision* array[], int numberOfHullsInArray)
{
    if (array != 0 && numberOfHullsInArray > 0)
    {
        NewtonCollision* pNewtonCollision = NewtonCreateCompoundCollision(this->pNewtonWorld, numberOfHullsInArray, array);
        NewtonConvexCollisionSetUserID(pNewtonCollision, PCFT_COMPOUND);
        return pNewtonCollision;
    }
    return 0;
}

NewtonCollision* PhysicsCollisionFrameFactory::convertToConvexHullCollisionFrame(NewtonCollision* pCollisionFrame)
{
    // Convert the collision frame to a Convex Hull
    if (pCollisionFrame != 0)
    {
        NewtonCollision* pNewtonCollision = NewtonCreateConvexHullModifier(this->pNewtonWorld, pCollisionFrame);
        NewtonConvexCollisionSetUserID(pNewtonCollision, PCFT_CONVEX_HULL);
        return pNewtonCollision;
    }
    return 0;
}

void PhysicsCollisionFrameFactory::realeaseCollisionFrame(NewtonCollision* pNewtonCollision)
{
    // Release a NewtonCollision Frame
    NewtonReleaseCollision(this->pNewtonWorld, pNewtonCollision);
}
