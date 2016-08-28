/**
  * @file   PhysicsWorld.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsWorld is a simple wrapper around a NewtonWorld
  * which is where all the purely mathematical objects driving physical
  * interaction for out game exist
*/

#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

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

// NEWTON WRAPPER INCLUDES
#include "EFrictionModel.h"
#include "EPlatformArchitecture.h"
#include "ESolverModel.h"
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonGlobalScale.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"
#include "PhysicsBuoyancyPlane.h"

/** @class PhysicsWorld
  * @brief The PhysicsWorld is a container for the NewtonWorld
  * @detail The PhysicsWorld Class is the core of the wrapper
  * and provides interpolation from one frame to another and
  * provides a NewtonWorld for our Objects to live in
  **/
class PhysicsWorld
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! the default constructor
        PhysicsWorld()
        {
            // Set the version of NewtonGameDynamics in Use
            this->version = 1.53;
            // when the Newton world is first created the default solver model is exact
            this->solverModel = ESM_EXACT;
            // when the Newton world is first created the default platform architecture is default
            this->platformArchitecture = EPA_DEFAULT;
            // when the Newton world is first created the default friction model is exact
            this->frictionModel = EFM_EXACT;
            // when the Newton world is first created the default minimum frame rate is 60 frames
            this->minimumFrameRate = 60.0f;
            // when the Newton world is created its default size is +/- 100
            this->worldSize = NewtonAABB(-100.0f, -100.0f, -100.0f, 100.0f, 100.0f, 100.0f);
            // Set the gravity vector to no gravity by default
            this->gravity = NewtonVector3(0.0f, 0.0f, 0.0f);
            // Set the buoyance toggle to false
            this->buoyancy = false;
            // Set the buoyancy callback to 0
            this->pBuoyancyPlaneCallBack = 0;
            // Set the default world scale
            this->globalScale = 1.0f;
        }
        //! Destructor
        virtual ~PhysicsWorld() {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // methods and members

    protected:
        //! Assignment operator
        PhysicsWorld& operator=(const PhysicsWorld& other) { return *this; }

    // ******************
    // * CORE FUNCTIONS *
    // ******************
    public:
        /** @brief Initialise the Newton world
          * @param allocMemory a callback which overrides default memory allocation with your own custom one (usually null or 0)
          * @param freeMemory a callback which overrides default memory deallocation with your own custom one (usually null or 0)
          * @return true on success, false on failure **/
        virtual bool init(NewtonAllocMemory allocMemory, NewtonFreeMemory freeMemory);
        /** @brief Update the Newton world
          * @param deltaTime difference between this frame and the last one **/
        virtual void update(float deltaTime);
        /** @brief Clear **/
        virtual void clear();
        /** @brief Free all objects in the Newton world **/
        virtual void free();

    protected:
        // methods and members

    // **********************
    // * CLEARING FUNCTIONS *
    // **********************
    public:
        /** @brief Destroy all bodies **/
        virtual void destroyAllBodies();
        /** @brief clearBuoyancy **/
        virtual void clearBuoyancy();
        // TODO: Clear, needs to reset buoyancy toggle to turn it off

    protected:
        // methods and members

    // ***************
    // * NEWTONWORLD *
    // ***************
    public:
        /** @brief Accessor to the Newton world
          * @return NewtonWorld **/
        virtual NewtonWorld* getNewtonWorld();

    protected:
        // Pointer to the Newton world
        NewtonWorld* pNewtonWorld;

    // *********
    // * SCALE *
    // *********
    public:
        /** @brief Get the global scale - not implemented in newton.h so we implement it here
          * @return GlobalScale **/
        virtual float getGlobalScale();
        /** @brief Set the global scale - not implemented in newton.h so we implement it here
          * @param globalScale the global scale to use NOTE: This is not used by NewtonGameDynamics **/
        virtual void setGlobalScale(float globalScale);

    protected:
        // Float for scaling the entire world (used to transform units from Newton to the units in the rendering engine)
        float globalScale;

    // *************************************
    // * ARCHITECTURES, SOLVERS AND MODELS *
    // *************************************
    public:
        /** @brief Get the Solver model
          * @return Solver Model **/
        virtual E_SOLVER_MODEL getSolverModel();
        /** @brief Set the Solver model
          * @param model the solver model to use values are ESM_EXACT = 0, ESM_ADAPTIVE = 1, ESM_LINEAR = 2 **/
        virtual void setSolverModel(E_SOLVER_MODEL model);
        /** @brief Get the platform architecture
          * @return platform architecture **/
        virtual E_PLATFORM_ARCHITECTURE getPlatformArchitecture();
        /** @brief set the platform architecture
          * @param achitecture the architecture model to use values are EPA_DEFAULT = 0, EPA_MEDIUM = 1, EPA_BEST = 2  **/
        virtual void setPlatformArchitecture(E_PLATFORM_ARCHITECTURE architecture);
        /** @brief get the friction model
          * @return friction model **/
        virtual E_FRICTION_MODEL getFrictionModel();
        /** @brief set the friction model
          * @param model friction model to use values are EFM_EXACT = 0, EFM_ADAPTIVE = 1 **/
        virtual void setFrictionModel(E_FRICTION_MODEL model);

    protected:
        // enumeration representing Solver model
        E_SOLVER_MODEL solverModel;
        // enumeration representing the platform architecture
        E_PLATFORM_ARCHITECTURE platformArchitecture;
        // enumeration representing the friction model
        E_FRICTION_MODEL frictionModel;

    // *************************
    // * FRAME RATE AND TIMING *
    // *************************
    public:
        /** @brief get the minimum frame rate
          * @return minimum frame rate **/
        virtual float getMinimumFrameRate();
        /** @brief set the minimum frame rate
          * @param rate the minimum frame rate to use **/
        virtual void setMinimumFrameRate(float rate);
        /** @brief get the time step
          * @return the time Step **/ // TODO: Need better documentation
        virtual float getTimeStep();

    protected:
        // minimum frame rate
        float minimumFrameRate;

    // **************
    // * WORLD SIZE *
    // **************
    public:
        /** @brief get the world size
          * @return a NewtonAABB object which represents the size of the physicsworld in newton scale not render scale**/
        virtual NewtonAABB getWorldSize();
        /** @brief set world size in newtonscale which may differ from render scale
          * @param worldSize a NewtonAABB defining the size of the NewtonWorld **/
        virtual void setWorldSize(NewtonAABB worldSize);

    protected:
        // an axis aligned bounding box representing the size of the Newton world
        NewtonAABB worldSize;

    // ***********
    // * VERSION *
    // ***********
    public:
        /** @brief Get the Newton Version
          * @return Newton Version **/
        virtual float getNewtonVersion();

    protected:
        // The Newton Version
        float version;

    // *************
    // * CALLBACKS *
    // *************
    public:
        /** @brief set NewtonBody Leave World CallBack
          * @param pCallBack is a NewtonBodyLeaveWorld callback function that is fired when a
          * NewtonBody, leaves the worldBoundaries **/
        virtual void setNewtonBodyLeaveWorldCallBack(NewtonBodyLeaveWorld pCallBack);

    protected:
        // methods and members

    // ***********
    // * GRAVITY *
    // ***********
    public:
        /** @brief get the global gravity vector
          * @return gravity vector as a NewtonVector3;
          * the scale is in newton scale which may or may not match
          * render scale **/
        virtual NewtonVector3 getGravity();
        /** @brief set the global gravity vector
          * @param x the horizontal part of the gravity vector
          * @param y the vertical part of the gravity vector
          * @param z the depth part of the gravity vector **/
        virtual void setGravity(float x, float y, float z);
        /** @brief set the global gravity vector
          * @param vec the gravity vector as a NewtonVector3 **/
        virtual void setGravity(NewtonVector3 vec);

    protected:
        // Gravity vector
        NewtonVector3 gravity;

    // ************
    // * BUOYANCY *
    // ************
    public:
        /** @brief is Buoyancy
          * @return true if there is buoyancy otherwise false **/
        virtual bool isBuoyancy() { return this->buoyancy; }
        /** @brief Turn Buoyancy On **/
        virtual void buoyancyOn() { this->buoyancy = true; }
        /** @brief Turn Buoyancy Off **/
        virtual void buoyancyOff() { this->buoyancy = false; }
        /** @brief Get Buoyancy Plane
          * @param the Buoyancy plane as an PhysicsBuoyancyPlane object **/
        virtual PhysicsBuoyancyPlane& getBuoyancyPlane() { return this->physicsBuoyancyPlane; }
        /** @brief Set Buoyancy Plane
          * @param plane the plane that defines buoyance as a PhysicsBuoyancyPlane object **/
        virtual void setBuoyancyPlane(PhysicsBuoyancyPlane plane) { this->physicsBuoyancyPlane = plane; }
        /** @brief Get Buoyancy Plane CallBack
          * @return the buoyancy plane as an PhysicsBuoyancyPlane object **/
        virtual NewtonGetBuoyancyPlane getBuoyancyPlaneCallBack() { return this->pBuoyancyPlaneCallBack; }
        /** @brief Set Buoyancy Plane CallBack
          * @param pCallBack is a NewtonGetBuoyancyPlane function callback **/
        virtual void setBuoyancyPlaneCallBack(NewtonGetBuoyancyPlane pCallBack) { this->pBuoyancyPlaneCallBack = pCallBack; }

    protected:
        // Buoyancy Plane
        PhysicsBuoyancyPlane physicsBuoyancyPlane;
        // Buoyancy Toggle
        bool buoyancy;
        // Local Reference tot he Buoyancy Plane CallBack
        NewtonGetBuoyancyPlane pBuoyancyPlaneCallBack;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // PHYSICSWORLD_H
