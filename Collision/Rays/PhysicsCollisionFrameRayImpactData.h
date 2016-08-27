/**
  * @file   PhysicsCollisionFrameRayImpactData.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsCollisionFrameRayImpactData
  * is a simple class for capturing ray impacts with collision
  * frames and is used mostly when you are using CollisionFrames
  * and doing the physics calculations yourself outside of the
  * standard newton pipeline
**/

#ifndef PHYSICSCOLLISIONFRAMERAYIMPACTDATA_H
#define PHYSICSCOLLISIONFRAMERAYIMPACTDATA_H

// NEWTON GAME DYNAMICS Includes
#include <cstddef>
#include <newton.h>

// GAMEPHYSICS Includes
#include "NewtonUtils.h"

//class PhysicsCollisionFrameRayImpactData
//{
//    public:
//        //! Default Constructor
//        PhysicsCollisionFrameRayImpactData()
//        {
//            this->position = NewtonVector3(0.0f, 0.0f, 0.0f);
//            this->normal = NewtonVector3(0.0f, 0.0f, 0.0f);
//            this->faceIndex = -1;
//        }
//        //! Destructor
//        virtual ~PhysicsCollisionFrameRayImpactData() {}
//
//    public:
//        //! Get Position
//        const NewtonVector3& getPosition() const { return this->position; }
//        //! Set Position
//        void setPosition(NewtonVector3 position) { this->position = position; }
//        //! Set Position
//        void setPosition(dFloat x, dFloat y, dFloat z) { this->position = NewtonVector3(x, y, z); }
//        //! Get Normal
//        const NewtonVector3& getNormal() const { return this->normal; }
//        //! Set Normal
//        void setNormal(NewtonVector3 normal) { this->normal = normal; }
//        //! Set Normal
//        void setNormal(dFloat x, dFloat y, dFloat z) { this->normal = NewtonVector3(x, y, z); }
//        //! Get Face Index
//        int getFaceIndex() { return this->faceIndex; }
//        //! Set Face Index
//        void setFaceIndex(int faceIndex) { this->faceIndex = faceIndex; }
//
//    protected:
//        NewtonVector3 position;
//        NewtonVector3 normal;
//        int faceIndex;
//};

#endif // PHYSICSCOLLISIONFRAMERAYIMPACTDATA_H
