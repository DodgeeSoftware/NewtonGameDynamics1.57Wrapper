/**
  * @file   PhysicsJointFactory.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsJointFactory is a factory that
  * simplified the creation of joints
**/

#ifndef PHYSICSJOINTFACTORY_H
#define PHYSICSJOINTFACTORY_H

#include <cstddef>
#include <newton.h>
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonGlobalScale.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"
#include "PhysicsWorld.h"

#include "PhysicsJointTypes.h"
#include "IPhysicsJoint.h"
#include "PhysicsBallAndSocketJoint.h"
#include "PhysicsCorkscrewJoint.h"
//#include "PhysicsCustomJoint.h"
#include "PhysicsHingeJoint.h"
#include "PhysicsSliderJoint.h"
#include "PhysicsUniversalJoint.h"
#include "PhysicsUpVectorJoint.h"

// TODO: implement me; this replaces the Joint Mgr
/** The PhysicsJointFactory is used to create physics joints. Physics Joints Connect
    NewtonBodies together and also have the ability to constrain movement of bodies **/
class PhysicsJointFactory
{
    public:
        //! Constructor
        PhysicsJointFactory()
        {
            this->pNewtonWorld = 0;
            this->pDestructorCallBack = 0;
            this->pBallAndSocketCallBack = 0;
            this->pCorkScrewCallBack = 0;
            this->pCustomCallBack = 0;
            this->pHingeCallBack = 0;
            this->pSliderCallBack = 0;
            this->pUniversalCallBack = 0;
        }
        //! Destructor
        virtual ~PhysicsJointFactory() {}

//    // CORE FUNCTIONS
//    public:
//        //! Initialise the physics joint manager
//        bool init()
//        {
//            return true;
//        }
//        //! Free all resources allocated by the physics joint manager
//        void free()
//        {
//
//        }

    // NEWTON WORLD
    public:
        //! Get the Newton World being used by the Debugger
        virtual NewtonWorld* getNewtonWorld() { return this->pNewtonWorld; }
        //! Set the Newton World for the Debugger
        virtual void setNewtonWorld(NewtonWorld* pNewtonWorld) { this->pNewtonWorld = pNewtonWorld; }

    protected:
        //! Local reference to the newton World
        NewtonWorld* pNewtonWorld;

    // CREATION METHODS
    public:
        //! Create a ball and socket joint
        PhysicsBallAndSocketJoint* createBallAndSocketJoint(NewtonVector3 pivotPoint, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody);
        //! Create a hinge joint
        PhysicsHingeJoint* createHingeJoint(NewtonVector3 pivotPoint, NewtonVector3 pin, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody);
        //! Create a hinge joint
        PhysicsSliderJoint* createSliderJoint(NewtonVector3 pivotPoint, NewtonVector3 pin, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody);
        //! Create a corkscrew joint
        PhysicsCorkscrewJoint* createCorkscrewJoint(NewtonVector3 pivotPoint, NewtonVector3 pin, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody);
        //! Create a universal joint
        PhysicsUniversalJoint* createUniversalJoint(NewtonVector3 pivotPoint, NewtonVector3 pin1, NewtonVector3 pin2, NewtonBody* pParentNewtonBody, NewtonBody* pChildNewtonBody);
        //! Create an up vector joint
        PhysicsUpVectorJoint* createUpVectorJoint(NewtonVector3 pin, NewtonBody* pNewtonBody);
// TODO: Review this
//        //! Create a custom joint
//        template<class T> T* createCustomJoint()
//        {
//            T* pCustomJoint = new T();
//            pCustomJoint->setNewtonWorld(this->pNewtonWorld);
//            // set callbacks if an
//            return pCustomJoint;
//
//             // [This simply sets the value of the function pointer, the setup function sets the joint callback which is why this is called first]
//        }
    // CALL BACKS
    protected:

    // JOINTS CALLBACKS
    public:
        //! Get JointDestructorCallBack (called Just before a Joint is Destroyed)
        NewtonConstraintDestructor getJointDestructorCallBack() { return this->pDestructorCallBack; }
        //! Set JointDestructorCallBack (called Just before a Joint is Destroyed)
        void setJointDestructorCallBack(NewtonConstraintDestructor pCallBack) { this->pDestructorCallBack = pCallBack; }
        //! Get BallAndSocketCallBack
        NewtonBallCallBack getBallAndSocketCallBack() { return this->pBallAndSocketCallBack; }
        //! Set BallAndSocketCallBack
        void setBallAndSocketCallBack(NewtonBallCallBack pCallBack) { this->pBallAndSocketCallBack = pCallBack; }
        //! Get CorkScrewCallBack
        NewtonCorkscrewCallBack getCorkScrewCallBack() { return this->pCorkScrewCallBack; }
        //! Set CorkScrewCallBack
        void setCorkScrewCallBack(NewtonCorkscrewCallBack pCallBack) { this->pCorkScrewCallBack = pCallBack; }
        /* NOTE: I need to work out away to have custom callbacks for each joint type
            most likely from a callback router pattern inherited from a base custom joint rather than
            using one universal callback here*/
        //! Get CustomCallBack
        NewtonUserBilateralCallBack getCustomCallBack() { return this->pCustomCallBack; }
        //! Set CustomCallBack
        void setCustomCallBack(NewtonUserBilateralCallBack pCallBack) { this->pCustomCallBack = pCallBack; }
        //! Get HingeCallBack
        NewtonHingeCallBack getHingeCallBack() { return this->pHingeCallBack; }
        //! Set HingeCallBack
        void setHingeCallBack(NewtonHingeCallBack pCallBack) { this->pHingeCallBack = pCallBack; }
        //! Get SliderCallBack
        NewtonSliderCallBack getSliderCallBack() { return this->pSliderCallBack; }
        //! Set SliderCallBack
        void setSliderCallBack(NewtonSliderCallBack pCallBack) { this->pSliderCallBack = pCallBack; }
        //! Get UniversalCallBack
        NewtonUniversalCallBack getUniversalCallBack() { return this->pUniversalCallBack; }
        //! Set UniversalCallBack
        void setUniversalCallBack(NewtonUniversalCallBack pCallBack) { this->pUniversalCallBack = pCallBack; }

    protected:
        //! Local Reference to the Joint Destructor CallBack
        NewtonConstraintDestructor pDestructorCallBack;
        //! Local Reference to the Ball And Socket Joint CallBack
        NewtonBallCallBack pBallAndSocketCallBack;
        //! Local Reference to the CorkScrew Joint CallBack
        NewtonCorkscrewCallBack pCorkScrewCallBack;
        //! Local Reference to the CustomCallBack
        NewtonUserBilateralCallBack pCustomCallBack;
        //! Local Reference to the HingeCallBack
        NewtonHingeCallBack pHingeCallBack;
        //! Local Reference to the SliderCallBack
        NewtonSliderCallBack pSliderCallBack;
        //! Local Reference to the UniversalCallBack
        NewtonUniversalCallBack pUniversalCallBack;
};

#endif // PHYSICSJOINTFACTORY_H
