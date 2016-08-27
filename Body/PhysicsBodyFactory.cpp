#include "PhysicsBodyFactory.h"

NewtonBody* PhysicsBodyFactory::createNullBody()
{
    return this->makeBody(this->physicsCollisionFramesFactory.createNullCollisionFrame());
}

NewtonBody* PhysicsBodyFactory::createBoxBody(float sizeX, float sizeY, float sizeZ)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createBoxCollisionFrame(sizeX, sizeY, sizeZ));
}

NewtonBody* PhysicsBodyFactory::createBoxBody(float sizeX, float sizeY, float sizeZ, irr::core::matrix4 offset)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createBoxCollisionFrame(sizeX, sizeY, sizeZ, offset));
}

NewtonBody* PhysicsBodyFactory::createSphereBody(float sizeX, float sizeY, float sizeZ)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createSphereCollisionFrame(sizeX, sizeY, sizeZ));
}

NewtonBody* PhysicsBodyFactory::createSphereBody(float sizeX, float sizeY, float sizeZ, irr::core::matrix4 offset)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createSphereCollisionFrame(sizeX, sizeY, sizeZ, offset));
}

NewtonBody* PhysicsBodyFactory::createConeBody(float radius, float height)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createConeCollisionFrame(radius, height));
}

NewtonBody* PhysicsBodyFactory::createConeBody(float radius, float height, irr::core::matrix4 offset)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createConeCollisionFrame(radius, height, offset));
}

NewtonBody* PhysicsBodyFactory::createCapsuleBody(float radius, float height)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createCapsuleCollisionFrame(radius, height));
}

NewtonBody* PhysicsBodyFactory::createCapsuleBody(float radius, float height, irr::core::matrix4 offset)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createCapsuleCollisionFrame(radius, height));
}

NewtonBody* PhysicsBodyFactory::createCylinderBody(float radius, float height)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createChampherCylinderCollisionFrame(radius, height));
}

NewtonBody* PhysicsBodyFactory::createCylinderBody(float radius, float height, irr::core::matrix4 offset)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createChampherCylinderCollisionFrame(radius, height, offset));
}

NewtonBody* PhysicsBodyFactory::createChampherCylinderBody(float radius, float height)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createChampherCylinderCollisionFrame(radius, height));
}

NewtonBody* PhysicsBodyFactory::createChampherCylinderBody(float radius, float height, irr::core::matrix4 offset)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createChampherCylinderCollisionFrame(radius, height, offset));
}

NewtonBody* PhysicsBodyFactory::createConvexHullBody(int vertexCount, float* vertexArray)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createConvexHullCollisionFrame(vertexCount, vertexArray));
}

NewtonBody* PhysicsBodyFactory::createConvexHullBody(const char* filename)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createConvexHullCollisionFrame(filename));
}

NewtonBody* PhysicsBodyFactory::createConvexHullBody(irr::scene::IMesh* pMesh)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createConvexHullCollisionFrame(pMesh));
}

// TODO: is there a convexhullbody offet matrix?

NewtonBody* PhysicsBodyFactory::createTreeBody(const char* filename)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createTreeCollisionFrame(filename));
}

NewtonBody* PhysicsBodyFactory::createTreeBody(irr::scene::IMesh* pMesh)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createTreeCollisionFrame(pMesh));
}

NewtonBody* PhysicsBodyFactory::createCompoundBody(NewtonCollision* array[], int numberOfHullsInArray)
{
    return this->makeBody(this->physicsCollisionFramesFactory.createCompoundCollisionFrame(array, numberOfHullsInArray));
}

NewtonBody* PhysicsBodyFactory::makeBody(NewtonCollision* pCollisionFrame)
{
    // create a Newton body using the null collision frame
    NewtonBody* pNewtonBody = NewtonCreateBody(this->pNewtonWorld, pCollisionFrame);
    // having created the Newton body we no longer require the collision frame
    NewtonReleaseCollision(pNewtonWorld, pCollisionFrame);
    // return the new NewtonBody
    return pNewtonBody;
}
