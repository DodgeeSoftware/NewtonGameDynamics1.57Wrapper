#include "PhysicsUpVectorJoint.h"

bool PhysicsUpVectorJoint::build(NewtonVector3 pin, NewtonBody* pNewtonBody)
{
    // make sure the body isn't null
    if (pNewtonBody == 0)
    {
        //std::cout << "NewtonBody nulll" << std::endl;
        return false;
    }

    // Declare some variable to check the mass matrix, the childbody cannot have infinite mass
    float mass = 0.0f, iX = 0.0f, iY = 0.0f, iZ = 0.0f;
    // Get the body's mass matrix
    NewtonBodyGetMassMatrix(pNewtonBody, &mass, &iX, &iY, &iZ);
    // If the mass is 0 then the body is invalid
    if (mass == 0)
    {
        //std::cout << "NewtonBody has no mass" << std::endl;
        return false;
    }

    // If there is already a joint then destroy it
    if (this->pNewtonJoint != 0)
        NewtonDestroyJoint(this->pNewtonWorld, this->pNewtonJoint);
    // Normalise the pin vector
    pin.normalise();
    // Create the Joint
    this->pNewtonJoint = NewtonConstraintCreateUpVector(pNewtonWorld, pin.getPointer(), pNewtonBody);
    // If making the joint failed then return false;
    if (this->pNewtonJoint == 0)
    {
        //std::cout << "this->pNewtonJoint = NewtonConstraintCreateUpVector(pNewtonWorld, pin.getPointer(), pNewtonBody); failed" << std::endl;
        return true;
    }
    // Set the User Data for the Joint
    this->setUserData(this);
    // Keep a local reference to the NewtonBody
    this->pNewtonBody = pNewtonBody;
    // Keep a local reference to the pin
    this->pin = pin;
    // Success
    return true;
}

NewtonVector3 PhysicsUpVectorJoint::getPin()
{
    // Create a NewtonVector for the pin
    NewtonVector3 pin;
    // Get the Pin
    NewtonUpVectorGetPin(this->pNewtonJoint, pin.getPointer());
    // Normalise the pin
    pin.normalise();
    // Return the pin
    return pin;
}

void PhysicsUpVectorJoint::setPin(NewtonVector3 pin)
{
    // Normalise the pin
    pin.normalise();
    // Set the pin
    NewtonUpVectorSetPin(this->pNewtonJoint, pin.getPointer());
}

void PhysicsUpVectorJoint::bindToLua(lua_State* pLuaState)
{
    // TODO: implement me
}
