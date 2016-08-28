/**
  * @file   IPhysicsBody.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  IPhysicsBody is a small wrapper around a NewtonBody
  * which is usually either a component of a scenenode or used as
  * a base class for a scenenode
**/

#ifndef IPHYSICSBODY_H
#define IPHYSICSBODY_H

// C++ Includes
#include <cstddef>

// NEWTON Includes
#include <newton.h>

// GAME PHYSICS Includes
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonGlobalScale.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector2.h"
#include "NewtonVector3.h"
#include "PhysicsBodyTypes.h"

/** @class IPhysicsBody
  * @brief An interface definition for a Physicsody
  * @detail This class defines all the basic and mandatory
  * functions to implement for a PhysicsBody **/
class IPhysicsBody
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        IPhysicsBody()
        {

        }
        //! Destructor
        virtual ~IPhysicsBody() {}

    public:
        //! Get World
        virtual const NewtonWorld* getNewtonWorld() const = 0;
        //! Set NewtonWorld
        virtual void setNewtonWorld(NewtonWorld* pNewtonWorld) = 0;

    public:
        //! Get NewtonBody
        virtual NewtonBody* getNewtonBody() = 0;

    public:
        //! Has a Newton Body
        virtual bool isInUse() = 0;
        //! Clear the body
        virtual void clear() = 0;

    public:
        //! Get the Collision Frame for this Body
        virtual const NewtonCollision* getCollisionFrame() const = 0;
        //! Create the Physics Body
        virtual void setCollisionFrame(NewtonCollision* pCollisionFrame) = 0;

    public:
        //! Get UserData
        virtual const void* getUserData() const = 0;
        //! Set UserData
        virtual void setUserData(void* pUserData) = 0;

    public:
        //! IsTransform Callback
        bool isTransformCallBack() { return pTransformCallBack != 0; }
        //! Get Transform CallBack
        virtual NewtonSetTransform getTransformCallBack() { return this->pTransformCallBack; }
        //! Set Transform CallBack
        virtual void setTransformCallBack(NewtonSetTransform pCallBack)
        {
            this->pTransformCallBack = pCallBack;
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetTransformCallback(this->pNewtonBody, pCallBack);
        }
        //! Is AutoActivationState CallBack
        bool isAutoActivationCallBack() { return pAutoActivationStateCallBack != 0; }
        //! Get Auto-Active CallBack
        virtual NewtonBodyActivationState getAutoActivationStateCallBack() { return this->pAutoActivationStateCallBack; }
        //! Set Auto-Active CallBack
        virtual void setAutoActiveCallBack(NewtonBodyActivationState pCallBack)
        {
            this->pAutoActivationStateCallBack = pCallBack;
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetAutoactiveCallback(this->pNewtonBody, pCallBack);
        }
        //! Is AutoActivationState CallBack
        bool isApplyForceAndTorqueCallBack() { return pApplyForceAndTorqueCallBack != 0; }
        //! Get Force and Torque CallBack
        virtual NewtonApplyForceAndTorque getApplyForceAndTorqueCallBack() { return this->pApplyForceAndTorqueCallBack; }
        //! Set Force and Torque CallBack
        virtual void setApplyForceAndTorqueCallBack(NewtonApplyForceAndTorque pCallBack)
        {
            this->pApplyForceAndTorqueCallBack = pCallBack;
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetForceAndTorqueCallback(this->pNewtonBody, pCallBack);
        }
        //! Is Destructor CallBack
        bool isDestructorCallBack() { return pDestructorCallBack != 0; }
        //! Get Destructor CallBack
        virtual NewtonBodyDestructor getDestructorCallBack() { return this->pDestructorCallBack; }
        //! Set Destructor CallBack
        virtual void setDestructorCallBack(NewtonBodyDestructor pCallBack)
        {
            this->pDestructorCallBack = pCallBack;
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetDestructorCallback(this->pNewtonBody, pCallBack);
        }

    public:
        //! Get Mass Matrix(Moment of inertia)
        virtual NewtonMassMatrix getMassMatrix() = 0;
        //! Set Mass Matrix (Moment of inertia)
        virtual void setMassMatrix(float mass, float Ixx, float Iyy, float Izz) = 0;
        //! Set Mass Matrix (Moment of inertia)
        virtual void setMassMatrix(NewtonMassMatrix massMatrix) = 0;
        //! Get the Inverse Mass Matrix
        virtual NewtonMassMatrix getInverseMassMatrix() = 0;

    public:
        //! Get Matrix
        virtual const NewtonMatrix4 getMatrix() const = 0;
        //! Set the Matrix
        virtual void setMatrix(float* matrix) = 0;
        //! Set the Matrix
        virtual void setMatrix(NewtonMatrix4 matrix) = 0;
        //! Set Matrix Recursive
        virtual void setMatrixRecursive(const float* pMatrix) = 0;

    public:
        //! Get Centre of Mass
        virtual NewtonVector3 getCentreOfMass() = 0;
        //! Set Centre of Mass (local co-ordinates)
        virtual void setCentreOfMass(float x, float y, float z) = 0;
        //! Set Centre of Mass (local co-ordinates)
        virtual void setCentreOfMass(NewtonVector3 position) = 0;

    public:
        //! Get the Position of the Physics Body
        virtual const NewtonVector3 getPosition() const = 0;
        //! Set the Position of the Physics Body
        virtual void setPosition(float x, float y, float z) = 0;
        //! Set the Position of the Physics Body
        virtual void setPosition(float* position) = 0;
        //! Set the Position of the Physics Body
        virtual void setPosition(NewtonVector3 position) = 0;

    public:
        //! Get the rotation of the body in degrees
        virtual const NewtonVector3 getRotationDegrees() const = 0;
        //! Set the rotation of the body in degrees
        virtual void setRotationDegrees(float x, float y, float z) = 0;
        //! Set the rotation of the body in degrees
        virtual void setRotationDegrees(NewtonVector3 rotation) = 0;
        //! Get the roation of the body in radians
        virtual NewtonVector3 getRotationRadians() = 0;
        //! Set the rotation of the body in radians
        virtual void setRotationRadians(float x, float y, float z) = 0;
        //! Set the rotation of the body in degrees
        virtual void setRotationRadians(NewtonVector3 rotation) = 0;
        //! Get the Size of the PhysicsBody's matrix (this function doesn't return the bodies size, rather just values present in the matrix; result of how Newton works)
        virtual const NewtonVector3 getSize() const = 0;
        //! Set the Size of the Physics Body (this function doesn't set the bodies size, rather just change present in the matrix; result of how Newton works)
        virtual void setSize(float x, float y, float z) = 0;
        //! Set the Size of the Physics Body
        virtual void setSize(NewtonVector3 size) = 0;

    public:
        //! Get the Matrix of the CollisionFrame of a ConvexHull
        virtual NewtonMatrix4 getConvexHullMatrix() = 0;
        //! Change the Collision Frame of a ConvexHull (IMPORTANT!!! ---> only works on convex hulls!!)
        virtual void setConvexHullMatrix(NewtonMatrix4 matrix) = 0;

    public:
        //! Get Velocity
        virtual NewtonVector3 getVelocity() = 0;
        //! Set Velocity
        virtual void setVelocity(float x, float y, float z) = 0;
        //! Set Velocity
        virtual void setVelocity(NewtonVector3 velocity) = 0;

    public:
        //! Get AngularVelocity
        virtual NewtonVector3 getAngularVelocity() = 0;
        //! Set AngularVelocity
        virtual void setAngularVelocity(float x, float y, float z) = 0;
        //! Set AngularVelocity
        virtual void setAngularVelocity(NewtonVector3 angularVelocity) = 0;

    public:
        //! Set the bodies Material ID
        virtual int getMaterialID() = 0;
        //! Set the bodies Material ID
        virtual void setMaterialID(int id) = 0;

    public:
        //! Set the State of Coriolis (Gyroscopic) Forces
        virtual void setCoroilisForcesMode(bool state) = 0;
        //! Set the State for continuous Collision calculations. Used for fast objects don't want to have this turned on for many objects because its computationally expensive
        virtual void setContinuousCollisionMode(bool state) = 0;
        //! Get the State for continuous Collision calculations.
        virtual bool getContinuousCollisionMode() = 0;
        //! Set Recursive Joint Collision Mode
        virtual void setRecursiveJointCollisionMode(bool state) = 0;
        //! Get Recursive Joint Collision Mode
        virtual bool getRecursiveJointCollisionMode() = 0;
        //! Freeze the Body (used for player objects)
        virtual void freezeBody() = 0;
        //! Freeze the Body (used for player objects)
        virtual void unfreezeBody() = 0;
        //! Set AutoFreeze
        virtual void setAutoFreeze(bool state) = 0;
        //! Is AutoFreeze Turned on?
        virtual bool getAutoFreeze() = 0;
        //! Is the Body sleeping (at rest)
        virtual bool isBodySleeping() = 0;
        //! Get the Body's FreeThreshold
        virtual NewtonFreezeThreshold getFreezeThreshHold() = 0;
        //! Set the Body's FreezeThreshold
        virtual void setFreezeThreshHold(NewtonFreezeThreshold threshold, int frameCount) = 0;
        //! Get AABB (two points define a box when a diagonal is drawn between them)
        virtual const NewtonAABB getAABB() const = 0;

    public:
        //! Set Linear Damping Co-Efficient
        virtual void setLinearDamping(float coEfficient) = 0;
        //! Get Linear Damping Co-Efficient
        virtual float getLinearDamping() = 0;
        //! Set Angular Damping Co-Efficient
        virtual void setAngularDamping(float coEfficientX, float coEfficientY, float coEfficientZ) = 0;
        //! Get Angular Linear Damping Co-Efficient
        virtual NewtonVector3 getAngularLinearDamping() = 0;

    public:
        //! Add Impulse Force (applies a force (velocity) to a position on the Body)
        virtual void addImpulseForce(float x, float y, float z, float impulseX, float impulseY, float impulseZ) = 0;

    public:
        //! Get the type of physics body
        E_PHYSICS_BODY_TYPE getType() { return this->type; }

    protected:
        //! Type of PhysicsBody
        E_PHYSICS_BODY_TYPE type;

    protected:
        //! Pointer to the NewtonBody
        NewtonBody* pNewtonBody;
        //! Pointer to the Physics World
        NewtonWorld* pNewtonWorld;
        //! Transform CallBack
        NewtonSetTransform pTransformCallBack;
        //! Auto-Active CallBack
        NewtonBodyActivationState pAutoActivationStateCallBack;
        //! Force and Torque CallBack
        NewtonApplyForceAndTorque pApplyForceAndTorqueCallBack;
        //! Set Destructor CallBack
        NewtonBodyDestructor pDestructorCallBack;

};

#endif // IPHYSICSBODY_H
