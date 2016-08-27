#include "PhysicsSliderJoint.h"

bool PhysicsSliderJoint::build(NewtonVector3 pivot, NewtonVector3 pin, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody)
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
    this->pNewtonJoint = NewtonConstraintCreateSlider(this->pNewtonWorld, pivot.getPointer(), pin.getPointer(), pChildNewtonBody, pParentNewtonBody);
    // If making the joint failed then return false;
    if (this->pNewtonJoint == 0)
        return false;
    // Set the User Data for the Joint
    this->setUserData(this);
    // Keep a local reference to the parent NewtonBody
    this->pParentNewtonBody = pParentNewtonBody;
    // Keep a local reference to the child NewtonBody
    this->pChildNewtonBody = pChildNewtonBody;
    // Keep a local reference to the pivot of the slider
    this->pivot = pivot;
    // Keep a local reference to the pin of the slider
    this->pin = pin;
    // Success
    return true;
}

//float PhysicsSliderJoint::getJointPosit()
//{
//    return NewtonSliderGetJointPosit(this->pNewtonJoint);
//}
//
//float PhysicsSliderJoint::getJointVeloc()
//{
//    return NewtonSliderGetJointVeloc(this->pNewtonJoint);
//}
//
//NewtonVector3 PhysicsSliderJoint::getJointForce()
//{
//    float forceArray[3] = {0.0f, 0.0f, 0.0f};
//    NewtonSliderGetJointForce(this->pNewtonJoint, forceArray);
//    return NewtonVector3(forceArray[0], forceArray[1], forceArray[2]);
//}

//unsigned int PhysicsSliderJoint::sliderCallBack(const NewtonJoint* slider, NewtonHingeSliderUpdateDesc* desc)
//{
//    return 0;
//}

void PhysicsSliderJoint::bindToLua(lua_State* pLuaState)
{
    // TODO: implement me
}
