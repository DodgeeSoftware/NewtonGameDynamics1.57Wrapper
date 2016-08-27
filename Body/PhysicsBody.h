/**
  * @file   PhysicsBody.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsBody is a small wrapper around a NewtonBody
  * which is usually either a component of a scenenode or used as
  * a base class for a scenenode
**/

#ifndef PHYSICSBODY_H
#define PHYSICSBODY_H

// C++ Includes
#include <cmath>
#include <iostream>

// LUA BIND INCLUDES
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

// NEWTON Includes
#include <cstddef>
#include <newton.h>

// NEWTON WRAPPER Includes
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"
#include "PhysicsBodyTypes.h"

/** The PhysicsBody class is a wrapper around a NewtonBody **/
class PhysicsBody
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        PhysicsBody()
        {
            this->pNewtonBody = 0;
            this->pNewtonWorld = 0;
            this->pBodyTransformCallBack = 0;
            this->pBodyAutoActivationStateCallBack = 0;
            this->pBodyApplyForceAndTorqueCallBack = 0;
            this->pBodyDestructorCallBack = 0;
            this->type = PBT_NOT_SET;
        }
        //! Destructor
        virtual ~PhysicsBody()
        {
            if (this->pNewtonBody != 0)
                NewtonDestroyBody(this->pNewtonWorld, this->pNewtonBody);
            this->type = PBT_NOT_SET;
        }

    protected:
        // Methods and members

    // ****************
    // * NEWTON WORLD *
    // ****************
    public:
        //! Get World
        virtual const NewtonWorld* getNewtonWorld() const
        {
            return this->pNewtonWorld;
        }
        //! Set NewtonWorld
        virtual void setNewtonWorld(NewtonWorld* pNewtonWorld) { this->pNewtonWorld = pNewtonWorld; }

    protected:
        // Pointer to the Physics World
        NewtonWorld* pNewtonWorld;

    // ***************
    // * NEWTON BODY *
    // ***************
    public:
        //! Get NewtonBody
        virtual NewtonBody* getNewtonBody() { return this->pNewtonBody; }
        //! Has a Newton Body
        virtual bool isInUse() { return (this->pNewtonBody != 0); }

    protected:
        // Pointer to the NewtonBody
        NewtonBody* pNewtonBody;

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Clear the body
        virtual void clearBody()
        {
            if (this->pNewtonBody != 0 && this->pNewtonWorld != 0)
                NewtonDestroyBody(this->pNewtonWorld, this->pNewtonBody);
            this->type = PBT_NOT_SET;
            this->pNewtonBody = 0;
            this->pNewtonWorld = 0;
            this->pBodyTransformCallBack = 0;
            this->pBodyAutoActivationStateCallBack = 0;
            this->pBodyApplyForceAndTorqueCallBack = 0;
            this->pBodyDestructorCallBack = 0;
        }

    protected:
        // Methods and members

    // *******************
    // * COLLISION FRAME *
    // *******************
    public:
        //! Get the Collision Frame for this Body
        //virtual const NewtonCollision* getBodyCollisionFrame() const
        virtual NewtonCollision* getBodyCollisionFrame() const
        {
            if (this->pNewtonBody == 0)
                return 0;
            return NewtonBodyGetCollision(this->pNewtonBody);
        }
        //! Create the Physics Body
        virtual void setBodyCollisionFrame(NewtonCollision* pCollisionFrame)
        {
            if (this->pNewtonWorld == 0)
            {
                std::cout << "Tried to set a collision frame for a physics body with a null NewtonWorld" << std::endl;
                return;
            }
            if (pCollisionFrame == 0)
            {
                std::cout << "Invalid CollisionFrame for a physics body" << std::endl;
                return;
            }

            if (this->pNewtonBody == 0)
            {
                std::cout << "NewtonBody was Null for a physics body so creating a null physics body" << std::endl;
                this->pNewtonBody = NewtonCreateBody(this->pNewtonWorld, NewtonCreateNull(this->pNewtonWorld));
            }
            std::cout << "Replacing existing collision frame for the body: " << pCollisionFrame << std::endl;
            NewtonBodySetCollision(this->pNewtonBody, pCollisionFrame);
            // The callbacks that were set for the previous NewtonBody will now apply to the new body
            this->setBodyTransformCallBack(this->pBodyTransformCallBack);
            this->setBodyAutoActiveCallBack(this->pBodyAutoActivationStateCallBack);
            this->setBodyApplyForceAndTorqueCallBack(this->pBodyApplyForceAndTorqueCallBack);
            this->setBodyDestructorCallBack(this->pBodyDestructorCallBack);
            this->type = (E_PHYSICS_BODY_TYPE)NewtonConvexCollisionGetUserID(pCollisionFrame);
        }

    protected:
        // Methods and members

    // *************
    // * USER DATA *
    // *************
    public:
        //! Get UserData
        virtual const void* getBodyUserData() const
        {
            if (this->pNewtonBody == 0)
                return 0;
            return NewtonBodyGetUserData(this->pNewtonBody);
        }
        //! Set UserData
        virtual void setBodyUserData(void* pUserData)
        {
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetUserData(this->pNewtonBody, pUserData);
        }

    protected:
        // Methods and members

    // *************
    // * CALLBACKS *
    // *************
    public:
        //! IsTransform Callback
        bool isBodyTransformCallBack() { return pBodyTransformCallBack != 0; }
        //! Get Transform CallBack
        virtual NewtonSetTransform getBodyTransformCallBack() { return this->pBodyTransformCallBack; }
        //! Set Transform CallBack
        virtual void setBodyTransformCallBack(NewtonSetTransform pCallBack)
        {
            this->pBodyTransformCallBack = pCallBack;
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetTransformCallback(this->pNewtonBody, pCallBack);
        }
        //! Is AutoActivationState CallBack
        bool isBodyAutoActivationCallBack() { return pBodyAutoActivationStateCallBack != 0; }
        //! Get Auto-Active CallBack
        virtual NewtonBodyActivationState getBodyAutoActivationStateCallBack() { return this->pBodyAutoActivationStateCallBack; }
        //! Set Auto-Active CallBack
        virtual void setBodyAutoActiveCallBack(NewtonBodyActivationState pCallBack)
        {
            this->pBodyAutoActivationStateCallBack = pCallBack;
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetAutoactiveCallback(this->pNewtonBody, pCallBack);
        }
        //! Is AutoActivationState CallBack
        bool isBodyApplyForceAndTorqueCallBack() { return pBodyApplyForceAndTorqueCallBack != 0; }
        //! Get Force and Torque CallBack
        virtual NewtonApplyForceAndTorque getBodyApplyForceAndTorqueCallBack() { return this->pBodyApplyForceAndTorqueCallBack; }
        //! Set Force and Torque CallBack
        virtual void setBodyApplyForceAndTorqueCallBack(NewtonApplyForceAndTorque pCallBack)
        {
            this->pBodyApplyForceAndTorqueCallBack = pCallBack;
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetForceAndTorqueCallback(this->pNewtonBody, pCallBack);
        }
        //! Is Destructor CallBack
        bool isBodyDestructorCallBack() { return pBodyDestructorCallBack != 0; }
        //! Get Destructor CallBack
        virtual NewtonBodyDestructor getBodyDestructorCallBack() { return this->pBodyDestructorCallBack; }
        //! Set Destructor CallBack
        virtual void setBodyDestructorCallBack(NewtonBodyDestructor pCallBack)
        {
            this->pBodyDestructorCallBack = pCallBack;
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetDestructorCallback(this->pNewtonBody, pCallBack);
        }

    protected:
        // Transform CallBack
        NewtonSetTransform pBodyTransformCallBack;
        // Auto-Active CallBack
        NewtonBodyActivationState pBodyAutoActivationStateCallBack;
        // Force and Torque CallBack
        NewtonApplyForceAndTorque pBodyApplyForceAndTorqueCallBack;
        // Set Destructor CallBack
        NewtonBodyDestructor pBodyDestructorCallBack;

    // ********
    // * MASS *
    // ********
    public:
        //! Get Mass Matrix(Moment of inertia)
        virtual NewtonMassMatrix getBodyMassMatrix()
        {
            if (this->pNewtonBody == 0)
                return NewtonMassMatrix();
            float mass = 0.0f, iX = 0.0f, iY = 0.0f, iZ = 0.0f;
            NewtonBodyGetMassMatrix(this->pNewtonBody, &mass, &iX, &iY, &iZ);
            return NewtonMassMatrix(mass, iX, iY, iZ);
        }
        //! Set Mass Matrix (Moment of inertia)
        virtual void setBodyMassMatrix(float mass, float Ixx, float Iyy, float Izz)
        {
            if (this->pNewtonBody == 0)
            {
                std::cout << "Couldnt set mass matrix newton body null" << std::endl;
                return;
            }
            NewtonBodySetMassMatrix(this->pNewtonBody, mass, Ixx, Iyy, Izz);
        }
        //! Set Mass Matrix (Moment of inertia)
        virtual void setBodyMassMatrix(NewtonMassMatrix massMatrix)
        {
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetMassMatrix(this->pNewtonBody, massMatrix.getMass(), massMatrix.getIX(), massMatrix.getIY(), massMatrix.getIZ());
        }
        //! Get the Inverse Mass Matrix
        virtual NewtonMassMatrix getBodyInverseMassMatrix()
        {
            if (this->pNewtonBody == 0)
                return NewtonMassMatrix();
            float mass = 0.0f, iX = 0.0f, iY = 0.0f, iZ = 0.0f;
            NewtonBodyGetInvMass(this->pNewtonBody, &mass, &iX, &iY, &iZ);
            return NewtonMassMatrix(mass, iX, iY, iZ);
        }
        //! Get Centre of Mass
        virtual NewtonVector3 getBodyCentreOfMass()
        {
            if (this->pNewtonBody == 0)
                return NewtonVector3();
            float pos[3] = {0.0f};
            NewtonBodyGetCentreOfMass(this->pNewtonBody, &pos[0]);
            return NewtonVector3(pos[0], pos[1], pos[2]);
        }
        //! Set Centre of Mass (local co-ordinates)
        virtual void setBodyCentreOfMass(float x, float y, float z)
        {
            if (this->pNewtonBody == 0)
                return;
            float pos[3] = {x, y, z};
            NewtonBodySetCentreOfMass(this->pNewtonBody, &pos[0]);
        }
        //! Set Centre of Mass (local co-ordinates)
        virtual void setBodyCentreOfMass(NewtonVector3 position)
        {
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetCentreOfMass(this->pNewtonBody, position.getPointer());
        }

    protected:
        // Methods and members

    // **********
    // * MATRIX *
    // **********
    public:
        //! Get Matrix (position, rotation matrix)
        virtual const NewtonMatrix4 getBodyMatrix() const
        {
            NewtonMatrix4 matrix;
            if (this->pNewtonBody != 0)
                NewtonBodyGetMatrix(this->pNewtonBody, matrix.getPointer());
            return matrix;
        }
        //! Set the Matrix (will call the TransformCallBack if one has been specified, param is 4x4 matrix)
        virtual void setBodyMatrix(float* matrix)
        {
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetMatrix(this->pNewtonBody, matrix);
            if (this->pBodyTransformCallBack != 0)
                this->pBodyTransformCallBack(this->pNewtonBody, matrix);
        }
        //! Set the Matrix (will call the TransformCallBack if one has been specified, param is 4x4 matrix)
        virtual void setBodyMatrix(NewtonMatrix4 matrix) { this->setBodyMatrix(matrix.getPointer()); }
        //! Set Matrix Recursive
        virtual void setBodyMatrixRecursive(const float* pMatrix)
        {
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetMatrixRecursive(this->pNewtonBody, pMatrix);
        }

    protected:
        // Methods and members

    // ************
    // * POSITION *
    // ************
    public:
        //! Get the Position of the Physics Body
        virtual const NewtonVector3 getBodyPosition() const
        {
            NewtonMatrix4 matrix = this->getBodyMatrix();
            return matrix.getTranslation();
        }
        //! Set the Position of the Physics Body
        virtual void setBodyPosition(float x, float y, float z)
        {
            NewtonMatrix4 matrix = this->getBodyMatrix();
            matrix.setTranslation(x, y, z);
            this->setBodyMatrix(matrix);
        }
        //! Set the Position of the Physics Body
        virtual void setBodyPosition(float* position)
        {
            this->setBodyPosition(position[0], position[1], position[2]);
        }
        //! Set the Position of the Physics Body
        virtual void setBodyPosition(NewtonVector3 position)
        {
            this->setBodyPosition(position.getX(), position.getY(), position.getZ());
        }

    protected:
        // Methods and members

    // ************
    // * ROTATION *
    // ************
    public:
        //! Get the rotation of the body in degrees
        virtual const NewtonVector3 getBodyRotationDegrees() const
        {
            NewtonMatrix4 matrix = this->getBodyMatrix();
            return matrix.getRotationDegrees();
        }
        //! Set the rotation of the body in degrees
        virtual void setBodyRotationDegrees(float x, float y, float z)
        {
            NewtonMatrix4 matrix = this->getBodyMatrix();
            matrix.setRotationDegrees(x, y, z);
            this->setBodyMatrix(matrix);
        }
        //! Set the rotation of the body in degrees
        virtual void setBodyRotationDegrees(NewtonVector3 rotation)
        {
            this->setBodyRotationDegrees(rotation.getX(), rotation.getY(), rotation.getZ());
        }
        //! Get the roation of the body in radians
        virtual NewtonVector3 getBodyRotationRadians()
        {
            NewtonMatrix4 matrix = this->getBodyMatrix();
            return matrix.getRotationRadians();
        }
        //! Set the rotation of the body in radians
        virtual void setBodyRotationRadians(float x, float y, float z)
        {
            NewtonMatrix4 matrix = this->getBodyMatrix();
            matrix.setRotationRadians(x, y, z);
            this->setBodyMatrix(matrix);
        }
        //! Set the rotation of the body in degrees
        virtual void setBodyRotationRadians(NewtonVector3 rotation)
        {
            this->setBodyRotationRadians(rotation.getX(), rotation.getY(), rotation.getZ());
        }
//        //! Get the Size of the PhysicsBody's matrix (this function doesn't return the bodies size, rather just values present in the matrix; result of how Newton works)
//        virtual const NewtonVector3 getBodySize() const
//        {
//            /* NOTE: This function will likely not work because it will only grab the size of objects increasing in size in the frame otherwise
//                it will return the identity scale of (1, 1, 1). TODO: Unit Testing on get size method
//                need a local variable for physics bodies for size (I believe only convex hulls can change size */
//            NewtonMatrix4 matrix = this->getMatrix();
//            return matrix.getScale();
//        }
//        //! Set the Size of the Physics Body (this function doesn't set the bodies size, rather just change present in the matrix; result of how Newton works)
//        virtual void setBodySize(float x, float y, float z)
//        {
//            NewtonMatrix4 matrix = this->getMatrix();
//            matrix.setScale(x, y, z);
//            this->setMatrix(matrix.getPointer());
//        }
//        //! Set the Size of the Physics Body
//        virtual void setBodySize(NewtonVector3 size)
//        {
//            this->setSize(size.getX(), size.getY(), size.getZ());
//        }

    protected:
        // Methods and members

    // ***********************************************************
    // * CONVEX HULL (Only use when this object is a convexHull) *
    // ***********************************************************
    public:
        //! Convert to a ConvexHull (NOTE: because we are recreating the body, we lose all information we setup about it mass, dampening, groupID etc)
        void convertToAConvexHull()
        {
            NewtonCollision* pNewtonCollision = NewtonCreateConvexHullModifier(this->pNewtonWorld, NewtonBodyGetCollision(this->pNewtonBody));
            // Set the Collision Frame Type to a ConvexHull
            NewtonConvexCollisionSetUserID(pNewtonCollision, PBT_CONVEX_HULL);
            // Cache the the user data from the body
            void* pUserData = NewtonBodyGetUserData(this->pNewtonBody);
            // Set the New Collision Frame for this body
            this->setBodyCollisionFrame(pNewtonCollision);
            // Set the UserData for the new Body
            this->setBodyUserData(pUserData);
        }
        //! Get the Matrix of the CollisionFrame of a ConvexHull
        virtual NewtonMatrix4 getBodyConvexHullMatrix()
        {
            // Do nothing there is no NewtonBody or no NewtonWorld or this object is not a ConvexHull
            if (this->pNewtonBody == 0 || this->pNewtonWorld == 0 || this->getBodyType() != PBT_CONVEX_HULL)
                return NewtonMatrix4();
            // A containter for the ConvexHull Matrix
            NewtonMatrix4 convexHullMatrix;
            // Grab the NewtonCollision for this body
            NewtonCollision* pNewtonCollision = NewtonBodyGetCollision(this->pNewtonBody);
            // Grab the ConvexHull Matrix from the CollisionFrame
            NewtonConvexHullModifierGetMatrix(pNewtonCollision, convexHullMatrix.getPointer());
            // Return the ConvexHull
            return convexHullMatrix;
        }
        //! Change the Collision Frame of a ConvexHull (IMPORTANT!!! ---> only works on convex hulls!!)
        virtual void setBodyConvexHullMatrix(NewtonMatrix4 matrix)
        {
            // Do nothing there is no NewtonBody or no NewtonWorld or this object is not a ConvexHull
            if (this->pNewtonBody == 0 || this->pNewtonWorld == 0 || this->getBodyType() != PBT_CONVEX_HULL)
                return;
            // Grab the NewtonCollision for this body
            NewtonCollision* pNewtonCollision = NewtonBodyGetCollision(this->pNewtonBody);
            // Make the NewtonCollision Frame Modifiable
            pNewtonCollision = NewtonCreateConvexHullModifier(this->pNewtonWorld, pNewtonCollision);
            // Modify the collision frame
            NewtonConvexHullModifierSetMatrix(pNewtonCollision, matrix.getPointer());
            //8888888888888
            // TODO: Review this convex hull stuff. Do I need to reset the body or am I allowed to simply transform the collision frame?

            /*
                "The Collision modifier cannot be used on compound collisions but works on the rest of shapes (it is not limited to just convex hulls)"
                    source: http://newtondynamics.com/wiki/index.php5?title=NewtonCreateConvexHullModifier

            */
            // Set the Collision Frame Type to a ConvexHull
            NewtonConvexCollisionSetUserID(pNewtonCollision, PBT_CONVEX_HULL); // Using the PhysicsBodyType Enumeration here is only possible because the CollisionFrameType value match perfectly
            // Set the modified collision frame as the collision frame for this Physics Body
            this->setBodyCollisionFrame(pNewtonCollision);
            // 8888888888888
        }

    protected:
        // Methods and members

    // ************
    // * VELOCITY *
    // ************
    public:
        //! Get Velocity
        virtual NewtonVector3 getBodyVelocity()
        {
            NewtonVector3 velocity;
            if (this->pNewtonBody != 0)
                NewtonBodyGetVelocity(this->pNewtonBody, velocity.getPointer());
            return velocity;
        }
        //! Set Velocity
        virtual void setBodyVelocity(float x, float y, float z)
        {
            if (this->pNewtonBody == 0)
                return;
            float vel[3] = {x, y, z};
            NewtonBodySetVelocity(this->pNewtonBody, vel);
        }
        //! Set Velocity
        virtual void setBodyVelocity(NewtonVector3 velocity)
        {
            this->setBodyVelocity(velocity.getX(), velocity.getY(), velocity.getZ());
        }
        //! Add Velocity
        virtual void addBodyVelocity(float x, float y, float z)
        {
            if (this->pNewtonBody == 0)
                return;
            NewtonVector3 velocity;
            NewtonBodyGetVelocity(this->pNewtonBody, velocity.getPointer());
            velocity = velocity + NewtonVector3(x, y, z);
            NewtonBodySetVelocity(this->pNewtonBody, velocity.getPointer());
        }
        //! Add Velocity
        virtual void addBodyVelocity(NewtonVector3 velocity)
        {
            this->addBodyVelocity(velocity.getX(), velocity.getY(), velocity.getZ());
        }

    protected:
        // Methods and members

    // ********************
    // * ANGULAR VELOCITY *
    // ********************
    public:
        //! Get AngularVelocity
        virtual NewtonVector3 getBodyAngularVelocity()
        {
            NewtonVector3 angularVelocity;
            if (this->pNewtonBody != 0)
                NewtonBodyGetOmega(this->pNewtonBody, angularVelocity.getPointer());
            return angularVelocity;
        }

        //! Set AngularVelocity
        virtual void setBodyAngularVelocity(float x, float y, float z)
        {
            if (this->pNewtonBody == 0)
                return;
            float vel[3] = {x, y, z};
            NewtonBodySetOmega(this->pNewtonBody, vel);
        }
        //! Set AngularVelocity
        virtual void setBodyAngularVelocity(NewtonVector3 angularVelocity)
        {
            this->setBodyAngularVelocity(angularVelocity.getX(), angularVelocity.getY(), angularVelocity.getZ());
        }
        //! Add AngularVelocity
        virtual void addAngularVelocity(NewtonVector3 velocity)
        {
            this->addAngularVelocity(velocity.getX(), velocity.getY(), velocity.getZ());
        }
        //! Add AngularVelocity
        virtual void addAngularVelocity(float x, float y, float z)
        {
            if (this->pNewtonBody == 0)
                return;
            NewtonVector3 angularVelocity;
            NewtonBodySetOmega(this->pNewtonBody, angularVelocity.getPointer());
            angularVelocity = angularVelocity + NewtonVector3(x, y, z);
            NewtonBodySetOmega(this->pNewtonBody, angularVelocity.getPointer());
        }

    protected:
        // Methods and members

    // ***********
    // * IMPULSE *
    // ***********
    public:
        //! Add Impulse Force (applies a force (velocity) to a position on the Body)
        virtual void addBodyImpulseForce(float x, float y, float z, float impulseX, float impulseY, float impulseZ)
        {
            if (this->pNewtonBody == 0)
                return;
            float pos[3] = {x, y, z};
            float imp[3] = {impulseX, impulseY, impulseZ};
            NewtonAddBodyImpulse(this->pNewtonBody, &imp[0], &pos[0]);
        }

    protected:
        // Methods and members

    // ***********************
    // * PHYSICS MATERIAL ID *
    // ***********************
    public:
        //! Set the bodies Material ID
        virtual int getBodyMaterialID()
        {
            int materialID = 0;
            if (this->pNewtonBody != 0)
                materialID = NewtonBodyGetMaterialGroupID(this->pNewtonBody);
            return materialID;
        }
        //! Set the bodies Material ID
        virtual void setBodyMaterialID(int id)
        {
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetMaterialGroupID(this->pNewtonBody, id);
        }

    protected:
        // Methods and members

    // *******************
    // * COROILIS FORCES *
    // *******************
    public:
        //! Set the State of Coriolis (Gyroscopic) Forces
        virtual void setBodyCoroilisForcesMode(bool state)
        {
            if (this->pNewtonBody == 0)
                return;
            NewtonBodyCoriolisForcesMode(this->pNewtonBody, state);
        }

    protected:
        // Methods and members

    // ************************
    // * CONTINUOUS COLLISION *
    // ************************
    public:
        //! Get the State for continuous Collision calculations.
        virtual bool getBodyContinuousCollisionMode()
        {
            if (this->pNewtonBody == 0)
                return false;
            return NewtonBodyGetContinuousCollisionMode(this->pNewtonBody);
        }
        //! Set the State for continuous Collision calculations. Used for fast objects don't want to have this turned on for many objects because its computationally expensive
        virtual void setBodyContinuousCollisionMode(bool state)
        {
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetContinuousCollisionMode(this->pNewtonBody, state);
        }

    protected:
        // Methods and members

    // ********************
    // * RECURSIVE JOINTS *
    // ********************
    public:
        //! Set Recursive Joint Collision Mode
        virtual void setBodyRecursiveJointCollisionMode(bool state)
        {
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetJointRecursiveCollision(this->pNewtonBody, state);
        }
        //! Get Recursive Joint Collision Mode
        virtual bool getBodyRecursiveJointCollisionMode()
        {
            if (this->pNewtonBody == 0)
                return false;
            return NewtonBodyGetJointRecursiveCollision(this->pNewtonBody);
        }

    protected:
        // Methods and members

    // ********************************
    // * FREEZE AND FREEZE THRESHOLDS *
    // ********************************
    public:
        //! Freeze the Body (used for player objects)
        virtual void freezeBody()
        {
            if (this->pNewtonBody == 0)
                return;
            if (this->pNewtonWorld == 0)
                return;
            NewtonWorldFreezeBody(this->pNewtonWorld, this->pNewtonBody);
        }
        //! Freeze the Body (used for player objects)
        virtual void unfreezeBody()
        {
            if (this->pNewtonBody == 0)
                return;
            if (this->pNewtonWorld == 0)
                return;
            NewtonWorldUnfreezeBody(this->pNewtonWorld, this->pNewtonBody);
        }
        //! Set AutoFreeze
        virtual void setBodyAutoFreeze(bool state)
        {
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetAutoFreeze(this->pNewtonBody, state);
        }
        //! Is AutoFreeze Turned on?
        virtual bool getBodyAutoFreeze()
        {
            if (this->pNewtonBody == 0)
                return true;
            return NewtonBodyGetAutoFreeze(this->pNewtonBody);
        }
        //! Is the Body Frozen (at rest)
        virtual bool isBodyFrozen()
        {
            if (this->pNewtonBody == 0)
                return true;
            return NewtonBodyGetSleepingState(this->pNewtonBody);
        }
        //! Get the Body's FreeThreshold
        virtual NewtonFreezeThreshold getBodyFreezeThreshHold()
        {
            dFloat velocityThreshold = 0.0f;
            dFloat angularVelocityThreshold = 0.0f;
            NewtonBodyGetFreezeTreshold(this->pNewtonBody, &velocityThreshold, &angularVelocityThreshold);
            return NewtonFreezeThreshold(velocityThreshold, angularVelocityThreshold);
        }
        //! Set the Body's FreezeThreshold
        virtual void setBodyFreezeThreshHold(NewtonFreezeThreshold threshold, int frameCount)
        {
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetFreezeTreshold(this->pNewtonBody, threshold.getVelocityThreshold(), threshold.getAngularVelocityThreshold(), frameCount);
        }

    protected:
        // Methods and members

    // ****************
    // * BOUNDING BOX *
    // ****************
    public:
        //! Get AABB (two points define a box when a diagonal is drawn between them)
        virtual const NewtonAABB getBodyAABB() const
        {
            if (this->pNewtonBody == 0)
                return NewtonAABB();
            NewtonAABB aabb;
            NewtonBodyGetAABB(this->pNewtonBody, aabb.getMinEdge(), aabb.getMaxEdge());
            aabb.fix();
            return aabb;
        }

    protected:
        // Methods and members

    // ***********
    // * DAMPING *
    // ***********
    public:
        //! Set Linear Damping Co-Efficient
        virtual void setBodyLinearDamping(float coEfficient)
        {
            if (this->pNewtonBody == 0)
                return;
            NewtonBodySetLinearDamping(this->pNewtonBody, coEfficient);
        }
        //! Get Linear Damping Co-Efficient
        virtual float getBodyLinearDamping()
        {
            if (this->pNewtonBody == 0)
                return 0.0f;
            return NewtonBodyGetLinearDamping(this->pNewtonBody);
        }
        //! Set Angular Damping Co-Efficient
        virtual void setBodyAngularDamping(float coEfficientX, float coEfficientY, float coEfficientZ)
        {
            if (this->pNewtonBody == 0)
                return;
            float angularDamping[3] = {coEfficientX, coEfficientY, coEfficientZ};
            NewtonBodySetAngularDamping(this->pNewtonBody, &angularDamping[0]);
        }
        //! Get Angular Linear Damping Co-Efficient
        virtual NewtonVector3 getBodyAngularLinearDamping()
        {
            if (this->pNewtonBody == 0)
                return NewtonVector3();
            NewtonVector3 angularLinearDamping;
            NewtonBodyGetAngularDamping (this->pNewtonBody, angularLinearDamping.getPointer());
            return angularLinearDamping;
        }

    protected:
        // Methods and members

    // **************
    // * BODY TYPES *
    // **************
    public:
        //! Get the type of physics body
        E_PHYSICS_BODY_TYPE getBodyType() { return this->type; }

    protected:
        // Type of PhysicsBody
        E_PHYSICS_BODY_TYPE type;

    // ************
    // * BINDINGS *
    // ************
    public:
        //! Bind this class to a luaState
        static void bindToLua(lua_State* pLuaState);
};


#endif // PHYSICSBODY_H
