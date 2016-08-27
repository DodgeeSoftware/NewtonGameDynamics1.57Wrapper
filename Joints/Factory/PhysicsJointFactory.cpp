#include "PhysicsJointFactory.h"

PhysicsBallAndSocketJoint* PhysicsJointFactory::createBallAndSocketJoint(NewtonVector3 pivotPoint, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody)
{
    // create a ball and socket joint
    PhysicsBallAndSocketJoint* pPhysicsBallAndSocketJoint = new PhysicsBallAndSocketJoint();
    // set the newton world for the joint
    pPhysicsBallAndSocketJoint->setNewtonWorld(this->pNewtonWorld);
    // set up the joint
    if (pPhysicsBallAndSocketJoint->build(pivotPoint, pParentNewtonBody, pChildNewtonBody) == 0)
    {
        // delete the joint
        delete pPhysicsBallAndSocketJoint;
        // return null
        return 0;
    }
    // set the update callback for the joint
    pPhysicsBallAndSocketJoint->setBallAndSocketCallBack(this->pBallAndSocketCallBack);
    // set the joint destructor callback
    pPhysicsBallAndSocketJoint->setJointDestructorCallback(this->pDestructorCallBack);
    // return a pointer to the newly created joint
    return pPhysicsBallAndSocketJoint;
}

PhysicsHingeJoint* PhysicsJointFactory::createHingeJoint(NewtonVector3 pivotPoint, NewtonVector3 pin, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody)
{
    // create a ball and socket joint
    PhysicsHingeJoint* pPhysicsHingeJoint = new PhysicsHingeJoint();
    // set the newton world for the joint
    pPhysicsHingeJoint->setNewtonWorld(this->pNewtonWorld);
    // set up the joint
    if (pPhysicsHingeJoint->build(pivotPoint, pin, pParentNewtonBody, pChildNewtonBody) == 0)
    {
        // delete the joint
        delete pPhysicsHingeJoint;
        // return null
        return 0;
    }
    // set the update callback for the joint
    pPhysicsHingeJoint->setHingeCallBack(this->pHingeCallBack);
    // set the joint destructor callback
    pPhysicsHingeJoint->setJointDestructorCallback(this->pDestructorCallBack);
    // return a pointer to the newly created joint
    return pPhysicsHingeJoint;
}

PhysicsSliderJoint* PhysicsJointFactory::createSliderJoint(NewtonVector3 pivotPoint, NewtonVector3 pin, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody)
{
    // create a ball and socket joint
    PhysicsSliderJoint* pPhysicsSliderJoint = new PhysicsSliderJoint();
    // set the newton world for the joint
    pPhysicsSliderJoint->setNewtonWorld(this->pNewtonWorld);
    // set up the joint
    if (pPhysicsSliderJoint->build(pivotPoint, pin, pParentNewtonBody, pChildNewtonBody) == 0)
    {
        // delete the joint
        delete pPhysicsSliderJoint;
        // return null
        return 0;
    }
    // set the update callback for the joint
    pPhysicsSliderJoint->setSliderCallBack(this->pSliderCallBack);
    // set the joint destructor callback
    pPhysicsSliderJoint->setJointDestructorCallback(this->pDestructorCallBack);
    // return a pointer to the newly created joint
    return pPhysicsSliderJoint;
}

PhysicsCorkscrewJoint* PhysicsJointFactory::createCorkscrewJoint(NewtonVector3 pivotPoint, NewtonVector3 pin, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody)
{
    // create a ball and socket joint
    PhysicsCorkscrewJoint* pPhysicsCorkscrewJoint = new PhysicsCorkscrewJoint();
    // set the newton world for the joint
    pPhysicsCorkscrewJoint->setNewtonWorld(this->pNewtonWorld);
    // set up the joint
    if (pPhysicsCorkscrewJoint->build(pivotPoint, pin, pParentNewtonBody, pChildNewtonBody) == 0)
    {
        // delete the joint
        delete pPhysicsCorkscrewJoint;
        // return null
        return 0;
    }
    // set the update callback for the joint
    pPhysicsCorkscrewJoint->setCorkScrewCallBack(this->pCorkScrewCallBack);
    // set the joint destructor callback
    pPhysicsCorkscrewJoint->setJointDestructorCallback(this->pDestructorCallBack);
    // return a pointer to the newly created joint
    return pPhysicsCorkscrewJoint;
}

PhysicsUniversalJoint* PhysicsJointFactory::createUniversalJoint(NewtonVector3 pivotPoint, NewtonVector3 pin1, NewtonVector3 pin2, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody)
{
    // create a ball and socket joint
    PhysicsUniversalJoint* pPhysicsUniversalJoint = new PhysicsUniversalJoint();
    // set the newton world for the joint
    pPhysicsUniversalJoint->setNewtonWorld(this->pNewtonWorld);
    // set up the joint
    if (pPhysicsUniversalJoint->build(pivotPoint, pin1, pin2, pParentNewtonBody, pChildNewtonBody) == 0)
    {
        // delete the joint
        delete pPhysicsUniversalJoint;
        // return null
        return 0;
    }
    // set the update callback for the joint
    pPhysicsUniversalJoint->setUniversalCallBack(this->pUniversalCallBack);
    // set the joint destructor callback
    pPhysicsUniversalJoint->setJointDestructorCallback(this->pDestructorCallBack);
    // return a pointer to the newly created joint
    return pPhysicsUniversalJoint;
}

PhysicsUpVectorJoint* PhysicsJointFactory::createUpVectorJoint(NewtonVector3 pin, NewtonBody* pNewtonBody)
{
    // create a ball and socket joint
    PhysicsUpVectorJoint* pPhysicsUpVectorJoint = new PhysicsUpVectorJoint();
    // set the newton world for the joint
    pPhysicsUpVectorJoint->setNewtonWorld(this->pNewtonWorld);
    // try to set up the joint
    if (pPhysicsUpVectorJoint->build(pin, pNewtonBody) == 0)
    {
        // delete the joint
        delete pPhysicsUpVectorJoint;
        // return null
        return 0;
    }
    // NOTE: there is no update callback for UpJoint Constraints
    // set the joint destructor callback
    pPhysicsUpVectorJoint->setJointDestructorCallback(this->pDestructorCallBack);
    // return a pointer to the newly created joint
    return pPhysicsUpVectorJoint;
}
