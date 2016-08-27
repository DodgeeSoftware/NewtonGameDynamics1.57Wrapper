/**
  * @file   PhysicsCollisionFrameCollide.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsCollisionFrameCollide
**/

#ifndef PHYSICSCOLLISIONFRAMECOLLIDE_H
#define PHYSICSCOLLISIONFRAMECOLLIDE_H

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
// NEWTON GAME DYNAMICS Includes
#include <newton.h>
// Newton Wrapper Includes
#include "NewtonUtils.h"

// TODO: Comment and implement me

//class PhysicsCollisionFrameCollide
//{
//    public:
//        //! Default Constructor
//        PhysicsCollisionFrameCollide()
//        {
//            this->position = NewtonVector3(0.0f, 0.0f, 0.0f);
//            this->normal = NewtonVector3(0.0f, 0.0f, 0.0f);
//            this->penetration = 0.0f;
//
//        }
//        //! Destructor
//        virtual ~PhysicsCollisionFrameCollide() {}
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
//        //! Get Penetration
//        int getPenetration() { return this->penetration; }
//        //! Set Penetration
//        void setPenetration(int penetration) { this->penetration = penetration; }
//
//    protected:
//        NewtonVector3 position;
//        NewtonVector3 normal;
//        float penetration;
//};

#endif // PHYSICSCOLLISIONFRAMECOLLIDE_H
