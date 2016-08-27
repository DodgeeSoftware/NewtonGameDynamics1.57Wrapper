#ifndef PHYSICSCOLLISIONFRAMECLOSESTPOINT_H
#define PHYSICSCOLLISIONFRAMECLOSESTPOINT_H

// LUA BIND
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

// Newton Includes
#include <cstddef>
#include <newton.h>

// Newton Wrapper Includes
#include "NewtonUtils.h"

//class PhysicsCollisionFrameClosestPoint
//{
//    public:
//        //! Default Constructor
//        PhysicsCollisionFrameClosestPoint()
//        {
//            this->closestPoint = NewtonVector3(0.0f, 0.0f, 0.0f);
//            this->seperationVector = NewtonVector3(0.0f, 0.0f, 0.0f);
//        }
//        //! Destructor
//        virtual ~PhysicsCollisionFrameClosestPoint() {}
//
//    public:
//        //! Get Closest Point
//        NewtonVector3& getClosestPoint() { return this->closestPoint; }
//        //! Set Closest Point
//        void setClosestPoint(NewtonVector3 closestPoint) { this->closestPoint = closestPoint; }
//        //! Set Closest Point
//        void setClosestPoint(dFloat x, dFloat y, dFloat z) { this->closestPoint = NewtonVector3(x, y, z); }
//        //! Get Seperation Vector
//        NewtonVector3& getSeperationVector() { return this->seperationVector; }
//        //! Set Seperation Vector
//        void setSeperationVector(NewtonVector3 seperationVector) { this->seperationVector = seperationVector; }
//        //! Set Seperation Vector
//        void setSeperationVector(dFloat x, dFloat y, dFloat z) { this->seperationVector = NewtonVector3(x, y, z); }
//
//    protected:
//        NewtonVector3 closestPoint;
//        NewtonVector3 seperationVector;
//};

#endif // PHYSICSCOLLISIONFRAMECLOSESTPOINT_H
