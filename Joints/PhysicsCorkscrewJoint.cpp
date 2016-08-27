#include "PhysicsCorkscrewJoint.h"

bool PhysicsCorkscrewJoint::build(NewtonVector3 pivot, NewtonVector3 pin, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody)
{
    // validate incoming Newton body parameters. The child body cannot be null, but a joint doesn't need a parent to exist
    if (pChildNewtonBody == 0)
        return false;
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
    // We assume the pivot point given is in world space and at render scale so we scale it here
    pivot *= RenderScaleToNewton;
    // Create the Joint
    this->pNewtonJoint = NewtonConstraintCreateCorkscrew(this->pNewtonWorld, pivot.getPointer(), pin.getPointer(), pChildNewtonBody, pParentNewtonBody);
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

// 88888888888888888
// BIG PROBLEMS HERE, THE DOCUMENTATION IN THE LIBRARY MEANS MANY OF THESE FUNCTIONS DO EXACTLY THE SAME THING :(
float PhysicsCorkscrewJoint::getRotationRadians()
{
    return NewtonCorkscrewGetJointPosit(this->pNewtonJoint);
}

float PhysicsCorkscrewJoint::getRotationDegrees()
{
    return NewtonCorkscrewGetJointPosit(this->pNewtonJoint) * (180.0 / M_PI);
}

float PhysicsCorkscrewJoint::getJointAngle()
{
    return NewtonCorkscrewGetJointAngle(this->pNewtonJoint);
}

//float PhysicsCorkscrewJoint::getJointVeloc()
//{
//    return NewtonCorkscrewGetJointVeloc(this->pNewtonJoint);
//}
//
//float PhysicsCorkscrewJoint::getJointOmega()
//{
//    return NewtonCorkscrewGetJointOmega(this->pNewtonJoint);
//}
//
//NewtonVector3 PhysicsCorkscrewJoint::getJointForce()
//{
//    float forceArray[3] = {0.0f, 0.0f, 0.0f};
//    NewtonCorkscrewGetJointForce(this->pNewtonJoint, forceArray);
//    return NewtonVector3(forceArray[0], forceArray[1], forceArray[2]);
//}
// 88888888888888888

//unsigned int PhysicsCorkscrewJoint::corkscrewCallBack(const NewtonJoint* corkscrew, NewtonHingeSliderUpdateDesc* desc)
//{
//    return 0;
//}

void PhysicsCorkscrewJoint::bindToLua(lua_State* pLuaState)
{
    // TODO: implement me
}
