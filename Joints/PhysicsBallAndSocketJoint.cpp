#include "PhysicsBallAndSocketJoint.h"

bool PhysicsBallAndSocketJoint::build(NewtonVector3 pivot, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody)
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
    // Create the BallAndSocketJoint
    this->pNewtonJoint = NewtonConstraintCreateBall(this->pNewtonWorld, pivot.getPointer(), pChildNewtonBody, pParentNewtonBody);
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
    // Success
    return true;
}

void PhysicsBallAndSocketJoint::setConeLimitsDegrees(NewtonVector3 pin, dFloat maxConeAngle, dFloat maxTwistAngle)
{
    // Normalise the incoming pin
    pin.normalise();
    // Bring the maxConeAngle into the range +/-180 degrees
    maxConeAngle -= 180.0;
    // Convert maxConeAngle into radians
    maxConeAngle *= (M_PI / 180.0);
    // Bring the maxTwistAngle into the range +/-180 degrees
    maxTwistAngle -= 180.0;
    // Convert maxTwistAngle into radians
    maxTwistAngle *= (M_PI / 180.0);
    // Set the Constraint on the ball and socket
    NewtonBallSetConeLimits(this->pNewtonJoint, pin.getPointer(), maxConeAngle, maxTwistAngle);
}

void PhysicsBallAndSocketJoint::setConeLimitsRadians(NewtonVector3 pin, dFloat maxConeAngle, dFloat maxTwistAngle)
{
    // Normalise the incoming pin
    pin.normalise();
    // Bring the maxConeAngle into the range +/-M_PI degrees
    maxConeAngle -= (M_PI);
    // Bring the maxTwistAngle into the range +/-M_PI degrees
    maxTwistAngle -= (M_PI);
    // Set the Constraint on the ball and socket
    NewtonBallSetConeLimits(this->pNewtonJoint, pin.getPointer(), maxConeAngle, maxTwistAngle);
}

NewtonVector3 PhysicsBallAndSocketJoint::getRotationRadians()
{
    // Make a NewtonVector3 to contain the Euler angles
    NewtonVector3 rotation;
    // Get the Angles between the two bodies connected to this joint (euler angles so x, y, z)
    NewtonBallGetJointAngle(this->pNewtonJoint, rotation.getPointer());
    // Return rotation
    return rotation;
}

NewtonVector3 PhysicsBallAndSocketJoint::getRotationDegrees()
{
    // Make a NewtonVector3 to contain the Euler angles
    NewtonVector3 rotation;
    // Get the Angles between the two bodies connected to this joint (euler angles so x, y, z)
    NewtonBallGetJointAngle(this->pNewtonJoint, rotation.getPointer());
    // Convert Euler angle from radians to degrees
    rotation *= (180.0f / M_PI);
    // Return rotation
    return rotation;
}

NewtonVector3 PhysicsBallAndSocketJoint::getAnglularVelocityBetweenTheBodies()
{
    //// Make a NewtonVector3 to contain the angular velocity between the bodies
    //NewtonVector3 angle;
    //// Get the Angular velocity between the bodies
    //NewtonBallGetJointOmega(this->pNewtonJoint, angle.getPointer());
    // /* TODO: I think have to convert this into render scale i.e.
    //    angle *= NewtonToRenderScale; */
    //// Return the Angular Velocity between the bodies
    //return angle;
    return this->omega;
}

void PhysicsBallAndSocketJoint::setAnglularVelocityBetweenTheBodies(NewtonVector3 omega)
{
    this->omega = omega;
}

NewtonVector3 PhysicsBallAndSocketJoint::getForceBetweenTheBodies()
{
    //// Make a NewtonVector3 to contain the force between the bodies
    //NewtonVector3 force;
    //// Get the force between the bodies
    //NewtonBallGetJointForce(this->pNewtonJoint, force.getPointer());
    // Return the force between the two bodies
    return this->force;
}

void PhysicsBallAndSocketJoint::setForceBetweenTheBodies(NewtonVector3 force)
{
    this->force = force;
}

void PhysicsBallAndSocketJoint::bindToLua(lua_State* pLuaState)
{
    // TODO: implemnet me
}
