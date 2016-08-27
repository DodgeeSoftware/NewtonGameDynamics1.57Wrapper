#include "PhysicsHingeJoint.h"

bool PhysicsHingeJoint::build(NewtonVector3 pivot, NewtonVector3 pin, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody)
{
    // validate incoming Newton body parameters
    if (pChildNewtonBody == 0)
        return true;
    // If there is already a joint then destroy it
    if (this->pNewtonJoint != 0)
        NewtonDestroyJoint(this->pNewtonWorld, this->pNewtonJoint);
    // We assume the pivot point given is in world space and at render scale so we scale it here
    pivot *= RenderScaleToNewton;
    // Create the Joint
    this->pNewtonJoint = NewtonConstraintCreateHinge(this->pNewtonWorld, pivot.getPointer(), pin.getPointer(), pChildNewtonBody, pParentNewtonBody);
    // If making the joint failed then return false;
    if (this->pNewtonJoint == 0)
        return false;
    // Set the User Data for the Joint
    this->setUserData(this);
    // Keep a local reference to the parent NewtonBody
    this->pParentNewtonBody = pParentNewtonBody;
    // Keep a local reference to the child NewtonBody
    this->pChildNewtonBody = pChildNewtonBody;
    // Keep a local reference to the pivot
    this->pivot = pivot;
    // Keep a local reference to the pin
    this->pin = pin;
    // Success
    return true;
}

float PhysicsHingeJoint::getAngleRadiansBetweenTheBodies()
{
    return NewtonHingeGetJointAngle(this->pNewtonJoint);
}

float PhysicsHingeJoint::getAngleDegreesBetweenTheBodies()
{
    return NewtonHingeGetJointAngle(this->pNewtonJoint) * (180.0f / M_PI);
}

float PhysicsHingeJoint::getAnglularVelocityBetweenTheBodies()
{
    //// TODO - test this function
    //return NewtonHingeGetJointOmega(this->pNewtonJoint) * (180.0f / M_PI);
    return this->omega;
}

void PhysicsHingeJoint::setAnglularVelocityBetweenTheBodies(float omega)
{
    this->omega = omega;
}

NewtonVector3 PhysicsHingeJoint::getForceBetweenTheBodies()
{
//    /* TODO - test this function. I am not sure if the return value is being handled correctly
//        also not sure if force is scaled to render scale or not ...
//        I am also not sure if this function is only available in the update callback*/
//    NewtonVector3 force;
//    NewtonHingeGetJointForce(this->pNewtonJoint, force.getPointer());
//    return force;
    return this->force;
}

void PhysicsHingeJoint::setForceBetweenTheBodies(NewtonVector3 force)
{
    this->force = force;
}

void PhysicsHingeJoint::bindToLua(lua_State* pLuaState)
{
    // TODO: implement me
}
