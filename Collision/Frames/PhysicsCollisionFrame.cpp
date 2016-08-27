#include "PhysicsCollisionFrame.h"

NewtonCollision* PhysicsCollisionFrame::getNewtonCollision()
{
    return this->pNewtonCollision;
}

void PhysicsCollisionFrame::setNewtonCollision(NewtonCollision* pNewtonCollision)
{
    if (pNewtonCollision == 0)
        return;
    // Make the local pointer to the collision frame point to the incoming collision frame
    this->pNewtonCollision = pNewtonCollision;
    /* Get the type of Object this is (The collision Frames Factory adds a type
        of collision frame to the NewtonCollision with the function
        NewtonConvexCollisionSetUserID(pNewtonCollision, unsigned int x);*/
    this->newtonCollisionType = (E_PHYSICS_COLLISIONFRAME_TYPE)NewtonConvexCollisionGetUserID(this->pNewtonCollision);
    // Reset previous instance information
    this->newtonCollisionModifiable = false;
    this->newtonCollisionMatrix.makeIdentity();
    this->newtonCollisionVelocity.setPosition(0.0f, 0.0f, 0.0f);
    this->newtonCollisionAngularVelocity.setPosition(0.0f, 0.0f, 0.0f);
}

E_PHYSICS_COLLISIONFRAME_TYPE PhysicsCollisionFrame::getNewtonCollisionType()
{
    return newtonCollisionType;
}

dFloat PhysicsCollisionFrame::getNewtonCollisionVolume()
{
    return NewtonConvexCollisionCalculateVolume(this->pNewtonCollision);
}

NewtonAABB PhysicsCollisionFrame::getNewtonCollisionAABB()
{
    NewtonAABB box;
    NewtonCollisionCalculateAABB(this->pNewtonCollision, this->getNewtonCollisionMatrix()->getPointer(), box.getMinEdge(), box.getMaxEdge());
    box.fix();
    return box;
}

void PhysicsCollisionFrame::makeNewtonCollisionUnique()
{
    // Note: Note sure what this function does entirely
    NewtonCollisionMakeUnique(this->pNewtonWorld, this->pNewtonCollision);
}

void PhysicsCollisionFrame::clear()
{
    // If there is a newton world set for this object and a collision frame then delete the collision frame
    if (this->pNewtonWorld != 0 &&  this->pNewtonCollision != 0)
        NewtonReleaseCollision(this->pNewtonWorld, this->pNewtonCollision);
    this->pNewtonWorld = 0;
    this->pNewtonCollision = 0;
    this->newtonCollisionType = PCFT_NOT_SET;
    //this->newtonCollisionMatrix.makeIdentity();
    //this->newtonCollisionVelocity.setPosition(0.0f, 0.0f, 0.0f);
    //this->newtonCollisionAngularVelocity.setPosition(0.0f, 0.0f, 0.0f);
    this->newtonCollisionModifiable = false;
}

bool PhysicsCollisionFrame::makeNewtonCollisionConvexHullModifiable()
{
    // If this isn't a convex hull then return false
    if (this->newtonCollisionType != PCFT_CONVEX_HULL)
        return false;
    // If this model isn't modifiable then convert the ConvexHull's collision frame into a modifiable form
    if (this->newtonCollisionModifiable == false)
    {
        // Make this convex hull modifiable
        this->pNewtonCollision =  NewtonCreateConvexHullModifier(this->pNewtonWorld, this->pNewtonCollision);
    }
}

bool PhysicsCollisionFrame::isNewtonCollisionModifiable()
{
    // Automatically return false if this collision frame isn't a convex hull
    if (this->newtonCollisionType != PCFT_CONVEX_HULL)
        return false;
    // Return if this is a modifiable convex hull
    return this->newtonCollisionModifiable;
}

NewtonMatrix4 PhysicsCollisionFrame::getNewtonCollisionConvexHullMatrix()
{
    // If this isn't a convex hull then return an indentity matrix
    if (this->newtonCollisionType != PCFT_CONVEX_HULL)
        return NewtonMatrix4();
    // Create a local matrix for the convexHUll modifier
    NewtonMatrix4 convexHullMatrix;
    // Get the Convex Hull Modifier
    NewtonConvexHullModifierGetMatrix(this->pNewtonCollision, convexHullMatrix.getPointer());
    // Return a copy of the ConvexHull Matrix
    return convexHullMatrix;
}

void PhysicsCollisionFrame::setNewtonCollisionConvexHullMatrix(NewtonMatrix4& matrix)
{
    // Make sure this function is only performed on convex hulls
    if (this->getNewtonCollisionType() != PCFT_CONVEX_HULL)
        return;
    // Apply a matrix to the NewtonCollisionFrame (this function will only works on convex hulls)
    NewtonConvexHullModifierSetMatrix(this->pNewtonCollision, newtonCollisionMatrix.getPointer());
}

void PhysicsCollisionFrame::bindToLua(lua_State* pLuaState)
{
    // TODO: implement me
}
