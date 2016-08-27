/**
  * @file   PhysicsCollisionFrameCollide.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsCollisionFrameCollide
**/

#ifndef PHYSICSCOLLISIONFRAMECLOSESTPOINTS_H
#define PHYSICSCOLLISIONFRAMECLOSESTPOINTS_H

// C++ Includes
#include <cstddef>
// LUA Includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
// LUA BIND Includes
#include <luabind/luabind.hpp>
// NEWTON Includes
#include <newton.h>
// GAMEPHYSICS Includes
#include "NewtonUtils.h"

// TODO: comment and implement me
//class PhysicsCollisionFrameClosestPoints
//{
//    public:
//        //! Default Constructor
//        PhysicsCollisionFrameClosestPoints()
//        {
//
//        }
//        //! Destructor
//        virtual ~PhysicsCollisionFrameClosestPoints() {}
//
//    public:
//        //! Get Closest Point to This Object
//        NewtonVector3& getClosestPointToThisObject() { return this->closestPointToThisObject; }
//        //! Set Closest Point to This Object
//        void setClosestPointToThisObject(NewtonVector3 closestPointToThisObject) { this->closestPointToThisObject = closestPointToThisObject; }
//        //! Set Closest Point to This Object
//        void setClosestPointToThisObject(dFloat x, dFloat y, dFloat z) { this->closestPointToThisObject = NewtonVector3(x, y, z); }
//        //! Get Closest Point to the other Object
//        NewtonVector3& getClosestPointToTheOtherObject() { return this->closestPointToTheOtherObject; }
//        //! Set Closest Point to the other Object
//        void setClosestPointToTheOtherObject(NewtonVector3 closestPointToTheOtherObject) { this->closestPointToTheOtherObject = closestPointToTheOtherObject; }
//        //! Set Closest Point to the other Object
//        void setClosestPointToTheOtherObject(dFloat x, dFloat y, dFloat z) { this->closestPointToTheOtherObject = NewtonVector3(x, y, z); }
//        //! Get Seperation Vector
//        NewtonVector3& getSeperationVector() { return this->seperationVector; }
//        //! Set Seperation Vector
//        void setSeperationVector(NewtonVector3 seperationVector) { this->seperationVector = seperationVector; }
//        //! Set Seperation Vector
//        void setSeperationVector(dFloat x, dFloat y, dFloat z) { this->seperationVector = NewtonVector3(x, y, z); }
//
//    protected:
//        NewtonVector3 closestPointToThisObject;
//        NewtonVector3 closestPointToTheOtherObject;
//        NewtonVector3 seperationVector;
//};

#endif // PHYSICSCOLLISIONFRAMECLOSESTPOINTS_H
