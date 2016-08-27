/**
  * @file   PhysicsMaterial.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsMaterial is a container for functions relating to
  * a NewtonMaterial. Two materials are involved when two NewtonBodies
  * collide or slide against eachother
**/

#ifndef PHYSICSMATERIAL_H
#define PHYSICSMATERIAL_H

// C++ INCLUDES
#include <iostream>
#include <string>

// LUA BIND INCLUDES
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

// NEWTON INCLUDES
#include <cstddef>
#include <newton.h>

// TODO: Materials probably should have pointers to callbacks and functions to set, in the event nondefault ones are to be used
class PhysicsMaterial
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default constructor
        PhysicsMaterial()
        {
            this->group0 = -1;
            this->group1 = -1;
            this->group0Name.clear();
            this->group1Name.clear();
            // NOTE: These defaults aren't used when creating a material. They are here for queries about parameters that haven't been set (aka newton defaults)
            this->collidable = false; // Materials are not collidable by default
            this->staticFriction = 1.0f; // I have assumed 1.0f as default for staticFriction
            this->kineticFriction = 0.5f; // I have assumed 0.5f as default for kinetic Friction
            this->continuousCollide = false; // This is off by default because its expensive
            this->elasticCoef = 0.5f; // I have assumed a value of 0.5f for elastic coefficient
            this->softnessCoef = 0.15f; // I have assumed a value of 0.15f for softness coefficient
            this->name.clear();
            this->physicsEnabled = true;
        }
        //! Default destructor
        virtual ~PhysicsMaterial() {}

    protected:
        // methods and members

    // **********************
    // * MATERIAL FUNCTIONS *
    // **********************
    public:
        //! Build the Material from the specified information
        virtual bool build()
        {
            // Verify NewtonWorld
            if (this->pNewtonWorld == false)
                return false;
            // Verify GroupIDs
            if (this->group0 < 0 || this->group1 < 0)
                return false;
            // Build the Material
            NewtonMaterialSetCollisionCallback(this->pNewtonWorld, this->group0, this->group1, this, this->pContactBeginCallBack, this->pContactProcessCallBack, this->pContactEndCallBack);
        }

    protected:
        // methods and members

    // *****************************
    // * GROUPS AND MATERIAL NAMES *
    // *****************************
    public:
        //! Get Group0
        virtual int getGroup0() { return this->group0; }
        //! Set Group0
        virtual void setGroup0(int group) { this->group0 = group; }
        //! Get Group0Name
        virtual std::string getGroup0Name() { return this->group0Name; }
        //! Set Group0Name
        virtual void setGroup0Name(std::string name) { this->group0Name = name; }
        //! Get Group1
        virtual int getGroup1() { return this->group1; }
        //! Set Group1
        virtual void setGroup1(int group) { this->group1 = group; }
        //! Get Group1Name
        virtual std::string getGroup1Name() { return this->group1Name; }
        //! Set Group1Name
        virtual void setGroup1Name(std::string name) { this->group1Name = name; }
        //! Get MaterialName
        virtual std::string getName() { return this->name; }
        //! Set MaterialName
        virtual void setName(std::string name) { this->name = name; }

    protected:
        // Group0
        int group0;
        // Group0Name
        std::string group0Name;
        // Group1
        int group1;
        // Group1Name
        std::string group1Name;
        // Name
        std::string name;

    // *********************
    // * MATERIAL SETTINGS *
    // *********************
    public:
        //! Make Collidable (Allow interaction at all between materials group0 & group1 but not necessarily physics)
        virtual void makeCollidable();
        //! Make Uncollidable (No interaction at all between materials group0 & group1)
        virtual void makeUncollidable();
        //! Is Collidable
        virtual bool isCollidable() { return this->collidable; }
        //! Get Process Physics
        virtual bool isPhysicsEnabled() { return this->physicsEnabled; }
        //! Enable Physics (allows physics calculations to similate the collision)
        virtual void enablePhysics() { this->physicsEnabled = true; }
        //! Disable Physics (disallows physics calculations for the collision)
        virtual void disablePhysics() { this->physicsEnabled = false; }
        //! Set Physics (if true objects with these materials will collide with physics otherwise no collision physics will be computed but callbacks will still be triggered)
        virtual void setPhysics(bool state) { this->physicsEnabled = state; }
        //! Make Continuous Collide
        virtual void makeContinuousCollide();
        //! Make Uncontinuous Collide
        virtual void makeUncontinuousCollide();
        //! Is ContinuousCollide
        virtual bool isContinuousCollide() { return this->continuousCollide; }
        //! Set Friction
        virtual void setFriction(dFloat staticFriction, dFloat kineticFriction);
        //! Get Static Friction
        virtual dFloat getStaticFriction() { return this->staticFriction; }
        //! Get Kinetic Friction
        virtual dFloat getKineticFriction() { return this->kineticFriction; }
        //! Set Elasticity
        virtual void setElasticity(dFloat elasticCoef);
        //! Get Elasticity
        virtual dFloat getElasticity() { return this->elasticCoef; }
        //! Get Softness
        virtual float getSoftness() { return this->softnessCoef; }
        //! Set Softness
        virtual void setSoftness(dFloat softnessCoef);

    protected:
        // Turn on and off interactions between bodies (when off no interaction at all occurs)
        bool collidable;
        // Turn on and off the physics part of the collision between bodies with this material (when off material callbacks are triggered by no physics calculatons occur)
        bool physicsEnabled;
        // Continually assess collisions every single frame
        bool continuousCollide;
        // Set the static friction between the two material groups
        dFloat staticFriction;
        // Set the kinetic friction between the two material groups
        dFloat kineticFriction;
        // Set the elastic coefficient between the two material groups
        dFloat elasticCoef;
        // Set the softness coefficient between the two material groups
        dFloat softnessCoef;

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

#endif // PHYSICSMATERIAL_H
