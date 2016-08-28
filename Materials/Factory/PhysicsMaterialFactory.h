/**
  * @file   PhysicsMaterialFactory.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsMaterialFactory is a class which builds
  * Physics Materials
**/

#ifndef PHYSICSMATERIALFACTORY_H
#define PHYSICSMATERIALFACTORY_H

// LUA BIND INCLUDES
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

// C++ INCLUDES
#include <cstddef>
#include <cmath>

// NEWTON INCLUDES
#include <newton.h>

// NEWTON WRAPPER INCLUDES
#include "PhysicsMaterial.h"

/** @class PhysicsMaterialFactory
  * @brief PhysicsMaterialFactory is a class which builds Physics Materials
  * @detail **/
class PhysicsMaterialFactory
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Constructor
        PhysicsMaterialFactory()
        {
            this->pNewtonWorld = 0;
            this->pContactBeginCallBack = 0;
            this->pContactProcessCallBack = 0;
            this->pContactEndCallBack = 0;
        }
        //! Destructor
        virtual ~PhysicsMaterialFactory() {}

    // *********************
    // * FACTORY FUNCTIONS *
    // *********************
    public:
        //! Create a PhysicsMaterial
        virtual PhysicsMaterial* createPhysicsMaterial()
        {
            // Create the PhysicsMaterial
            PhysicsMaterial* pPhysicsMaterial = new PhysicsMaterial();
            // Set the NewtonWorld for the PhysicsMaterial
            pPhysicsMaterial->setNewtonWorld(this->pNewtonWorld);
            // Set the ContactBegin CallBack
            pPhysicsMaterial->setContactBeginCallBack(this->pContactBeginCallBack);
            // Set the ContactProcess CallBack
            pPhysicsMaterial->setContactProcessCallBack(this->pContactProcessCallBack);
            // Set the ContactEndCallBack
            pPhysicsMaterial->setContactEndCallBack(this->pContactEndCallBack);
            // Returnt the new PhysicsMaterial
            return pPhysicsMaterial;
        }

    // ****************
    // * NEWTON WORLD *
    // ****************
    public:
        //! Get the NewtonWorld
        virtual const NewtonWorld* getNewtonWorld() { return this->pNewtonWorld; }
        //! Set the NewtonWorld
        virtual void setNewtonWorld(NewtonWorld* pNewtonWorld) { this->pNewtonWorld = pNewtonWorld; }

    protected:
        // Maintain a pointer to the Newton world
        NewtonWorld* pNewtonWorld;

    // *************
    // * CALLBACKS *
    // *************
    public:
        //! Set ContactBegin CallBack
        virtual void setContactBeginCallBack(NewtonContactBegin pCallBack) { this->pContactBeginCallBack = pCallBack; }
        //! Set ContactProcess CallBack
        virtual void setContactProcessCallBack(NewtonContactProcess pCallBack) { this->pContactProcessCallBack = pCallBack; }
        //! Set ContactEnd CallBack
        virtual void setContactEndCallBack(NewtonContactEnd pCallBack) { this->pContactEndCallBack = pCallBack; }

    protected:
        // Keep a local reference to the Contact Begin CallBack (Broad Phased Axis Aligned BoundingBox)
        NewtonContactBegin pContactBeginCallBack;
        // Keep a local reference to the proccess CallBack (process each point of collision between the bodies)
        NewtonContactProcess pContactProcessCallBack;
        // Keep a local reference to the contactEnd CallBack (called once all contacts have been processed)
        NewtonContactEnd pContactEndCallBack;
};

#endif // PHYSICSMATERIALFACTORY_H
