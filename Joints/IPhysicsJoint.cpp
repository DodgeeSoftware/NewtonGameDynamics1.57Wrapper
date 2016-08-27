#include "IPhysicsJoint.h"

void IPhysicsJoint::clear()
{
    // free the joint
    if (this->pNewtonJoint != 0 && this->pNewtonWorld != 0)
    {
        // if the joint is still exists then destroy it.
        if (NewtonJointGetUserData(this->pNewtonJoint) != 0)
        {
            // reset the destructor callback for this joint
            NewtonJointSetDestructor(this->pNewtonJoint, 0);
            // destroy this joint
            NewtonDestroyJoint(this->pNewtonWorld, this->pNewtonJoint);
            // set to pointer to this joint to 0
            this->pNewtonJoint = 0;
        }
    }
}

bool IPhysicsJoint::isCollidable()
{
    // if the NewtonJointGetCollisionState function returns nonzero then these joints can collide otherwise they can't
    return (NewtonJointGetCollisionState(this->pNewtonJoint) != 0) ? true : false;
}

void IPhysicsJoint::enableCollision()
{
    NewtonJointSetCollisionState(this->pNewtonJoint, 1);
}

void IPhysicsJoint::disableCollision()
{
    NewtonJointSetCollisionState(this->pNewtonJoint, 0);
}

float IPhysicsJoint::getStiffness()
{
    // query the stiffness coefficient between these two joints
    return NewtonJointGetStiffness(this->pNewtonJoint);
}

void IPhysicsJoint::setStiffness(float coefficient)
{
    // set the stiffness between these two joints
    NewtonJointSetStiffness(this->pNewtonJoint, coefficient);
}

void IPhysicsJoint::bindToLua(lua_State* pLuaState)
{
    // TODO: implement me
}
