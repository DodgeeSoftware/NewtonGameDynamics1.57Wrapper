#include "PhysicsUniversalJoint.h"

bool PhysicsUniversalJoint::build(NewtonVector3 pivot, NewtonVector3 pin0, NewtonVector3 pin1, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody)
{
    // validate incoming Newton body parameters. The child body cannot be null, but a joint doesn't need a parent to exist
    if (pChildNewtonBody == 0)
        return 0;
    // Declare some variable to check the mass matrix, the childbody cannot have infinite mass
    float mass = 0.0f, iX = 0.0f, iY = 0.0f, iZ = 0.0f;
    // Get the ChildBody's mass matrix
    NewtonBodyGetMassMatrix(pChildNewtonBody, &mass, &iX, &iY, &iZ);
    // If the mass is 0 then the body is invalid
    if (mass == 0)
        return false;
    // If there is already a joint then destroy it
    if (this->pNewtonJoint != 0)
        NewtonDestroyJoint(this->pNewtonWorld, this->pNewtonJoint);
    // Scale the pivot point from Render Scale to Newton Scale
    pivot *= RenderScaleToNewton;
    // Normalise pin0
    pin0.normalise();
    // Normalise pin1
    pin1.normalise();
    // Create the Joint
    this->pNewtonJoint = NewtonConstraintCreateUniversal(this->pNewtonWorld, pivot.getPointer(), pin0.getPointer(), pin1.getPointer(), pChildNewtonBody, pParentNewtonBody);
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
    // Keep a local refernce to pin0
    this->pin0 = pin0;
    // Keep a local refernce to pin1
    this->pin1 = pin1;
    // Success
    return true;
}

float PhysicsUniversalJoint::getJointAngle0()
{
    return NewtonUniversalGetJointAngle0(this->pNewtonJoint);
}

float PhysicsUniversalJoint::getJointAngle1()
{
    return NewtonUniversalGetJointAngle1(this->pNewtonJoint);
}

float PhysicsUniversalJoint::getAngularVelocityBetweenBodiesPin0()
{
    //return NewtonUniversalGetJointOmega0(this->pNewtonJoint);
    return this->omegaPin0;
}

void PhysicsUniversalJoint::setAngularVelocityBetweenBodiesPin0(float omega)
{
    this->omegaPin0 = omega;
}

float PhysicsUniversalJoint::getAngularVelocityBetweenBodiesPin1()
{
    //return NewtonUniversalGetJointOmega1(this->pNewtonJoint);
    return this->omegaPin1;
}

void PhysicsUniversalJoint::setAngularVelocityBetweenBodiesPin1(float omega)
{
    this->omegaPin1 = omega;
}

NewtonVector3 PhysicsUniversalJoint::getJointForce()
{
//    // Create a NewtonVector3 to contain the force
//    NewtonVector3 force;
//    // Get the Force
//    NewtonUniversalGetJointForce(this->pNewtonJoint, force.getPointer());
//    // Return the force
//    return force;
    return this->force;
}

void PhysicsUniversalJoint::setJointForce(NewtonVector3 force)
{
    this->force = force;
}

NewtonVector3 PhysicsUniversalJoint::getPin0()
{
    // return the normalised pin
    return this->pin0 * NewtonToRenderScale;
}

NewtonVector3 PhysicsUniversalJoint::getPin1()
{
    // return the normalised pin
    return this->pin1 * NewtonToRenderScale;
}

void PhysicsUniversalJoint::bindToLua(lua_State* pLuaState)
{
    // TODO: implement me
}
