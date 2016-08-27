#include "PhysicsCustomJoint.h"

// TODO: Replace degreesOfFreedom with an Enumeration
bool PhysicsCustomJoint::build(int degreesOfFreedom, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody)
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
    // validate the incoming parameters
    if (degreesOfFreedom == 0 || degreesOfFreedom > 5)
        return false;
    // If there is already a joint then destroy it
    if (this->pNewtonJoint != 0)
        NewtonDestroyJoint(this->pNewtonWorld, this->pNewtonJoint);
    // Create the Joint
    this->pNewtonJoint = NewtonConstraintCreateUserJoint(this->pNewtonWorld, degreesOfFreedom, pCustomJointCallBack, pChildNewtonBody, pParentNewtonBody);
    // If making the joint failed then return false;
    if (this->pNewtonJoint == 0)
        return false;
    // Set the User Data for the Joint
    this->setUserData(this);
    // Keep a local reference to the parent NewtonBody
    this->pParentNewtonBody = pParentNewtonBody;
    // Keep a local reference to the child NewtonBody
    this->pChildNewtonBody = pChildNewtonBody;
    // Keep a local reference to the degrees of freedom
    this->degreesOfFreedom = degreesOfFreedom;
    // Success
    return true;
}

void PhysicsCustomJoint::addLinearRow(NewtonVector3 pivot0, NewtonVector3 pivot1, NewtonVector3 direction)
{
    float pivot0Array[3] = {pivot0.getX() * RenderScaleToNewton, pivot0.getY() * RenderScaleToNewton, pivot0.getZ() * RenderScaleToNewton};
    float pivot1Array[3] = {pivot1.getX() * RenderScaleToNewton, pivot1.getY() * RenderScaleToNewton, pivot1.getZ() * RenderScaleToNewton};
    float directionArray[3] = {direction.getX(), direction.getY(), direction.getZ()};
    NewtonUserJointAddLinearRow(this->pNewtonJoint, pivot0Array, pivot1Array, directionArray);
}

void PhysicsCustomJoint::addAngularRow(float relativeAngleError, NewtonVector3 pin)
{
    pin.normalise();
    float pinArray[3] = {pin.getX(), pin.getY(), pin.getZ()};
    NewtonUserJointAddAngularRow(this->pNewtonJoint, relativeAngleError, pinArray);
}

void PhysicsCustomJoint::addGeneralRow(NewtonVector3 jacobian0, NewtonVector3 jacobian1)
{
    float jacobian0Array[3] = {jacobian0.getX(), jacobian0.getY(), jacobian0.getZ()};
    float jacobian1Array[3] = {jacobian1.getX(), jacobian1.getY(), jacobian1.getZ()};
    NewtonUserJointAddGeneralRow(this->pNewtonJoint, jacobian0Array, jacobian1Array);
}

void PhysicsCustomJoint::setRowMinimumFriction(float friction)
{
    NewtonUserJointSetRowMinimumFriction(this->pNewtonJoint, friction);
}

void PhysicsCustomJoint::setRowMaximumFriction(float friction)
{
    NewtonUserJointSetRowMaximumFriction(this->pNewtonJoint, friction);
}

void PhysicsCustomJoint::setRowAcceleration(float acceleration)
{
    NewtonUserJointSetRowAcceleration(this->pNewtonJoint, acceleration);
}

void PhysicsCustomJoint::setRowStiffness(float stiffness)
{
    NewtonUserJointSetRowStiffness(this->pNewtonJoint, stiffness);
}

void PhysicsCustomJoint::setRowSpringDamperAcceleration(float springK, float springD)
{
    NewtonUserJointSetRowSpringDamperAcceleration(this->pNewtonJoint, springK, springD);
}

float PhysicsCustomJoint::getRowForce(int row)
{
    return NewtonUserJointGetRowForce(this->pNewtonJoint, row);
}

//void PhysicsCustomJoint::userBilateralCallBack(const NewtonJoint* userJoint)
//{
//
//}

void PhysicsCustomJoint::bindToLua(lua_State* pLuaState)
{
    // TODO: implement me
}
