/**
  * @file   IPhysicsDebugger.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  IPhysicsDebugger is an abstract class
  * that defines basic functions for our PhysicsDebugger.
  * To implement this class combine it with your rendering system
  * such as opengl, irrlicht, ogre anything that will allow you
  * to draw lines and such.
**/

#ifndef IPHYSICSDEBUGGER_H
#define IPHYSICSDEBUGGER_H

// C++ Includes
#include <iostream>
#include <vector>

// LUA BIND
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

// GAMEPHYSICS Includes
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonGlobalScale.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"
#include "IPhysicsRay.h"
#include "IPhysicsJoint.h"
#include "PhysicsBallAndSocketJoint.h"
#include "PhysicsCorkscrewJoint.h"
#include "PhysicsHingeJoint.h"
#include "PhysicsSliderJoint.h"
#include "PhysicsUniversalJoint.h"
#include "PhysicsUpVectorJoint.h"
#include "IPhysicsVehicle.h"
#include "IPhysicsTrigger.h"
#include "IPhysicsRagDoll.h"
#include "IPhysicsDebugger.h"

/** Implement the IPhysicsDebugger to create a physics debugger for your rendering engine. Make call backs for 'pForEachPolygonDo' and 'forEachBodyDo'
    in your game's main scope and pass them into you own PhysicsDebugger custom made for your rendering engine **/
class IPhysicsDebugger
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        IPhysicsDebugger()
        {
            this->pNewtonWorld = 0;
            this->visible = true;
            this->visibleWorldBoundaries = true;
            this->raysVisible = true;
            this->jointsVisible = true;
            this->bodiesVisible = true;
            this->triggersVisible = true;
            this->pForEachPolygonCallBack = 0;
            this->pForEachBodyCallBack = 0;
        }
        //! Destructor
        virtual ~IPhysicsDebugger() {}

    protected:
        // methods and members

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Initialise PhysicsDebugger
        virtual bool init();
        //! Update the Newton world
        virtual void update();
        //! Render the Newton world
        virtual void draw();
        //! Clear the Debugger
        virtual void clear();
        //! Clean up after PhysicsDebugger
        virtual void free();

    // NEWTON WORLD
    public:
        //! Get the Newton World being used by the Debugger
        virtual NewtonWorld* getNewtonWorld() { return this->pNewtonWorld; }
        //! Set the Newton World for the Debugger
        virtual void setNewtonWorld(NewtonWorld* pNewtonWorld) { this->pNewtonWorld = pNewtonWorld; }

    protected:
        // Local reference to the newton World
        NewtonWorld* pNewtonWorld;

    // VISIBILITY TOGGLES
    public:
        //! Is the debugger visible
        virtual bool isVisible() { return this->visible; }
        //! Show debugger
        virtual void show() { this->visible = true; }
        //! Hide debugger
        virtual void hide() { this->visible = false; }
        //! Set the visible flag
        virtual void setVisible(bool visible) { this->visible = visible; }
        //! Are the world boundaries visible
        virtual bool isWorldBoundariesVisible() { return this->visibleWorldBoundaries; }
        //! Show the world boundaries
        virtual void showWorldBoundaries() { this->visibleWorldBoundaries = true; }
        //! Hide the world boundaries
        virtual void hideWorldBoundaries() { this->visibleWorldBoundaries = false; }
        //! Set World Boundaries visible
        virtual void setWorldBoundariesVisible(bool state)  { this->visibleWorldBoundaries = state; }
        //! Are Rays visible
        bool isRaysVisible() { return this->raysVisible; }
        //! Show rays
        void showRays() { this->raysVisible = true; }
        //! Hide rays
        void hideRays() { this->raysVisible = false; }
        //! Are joints visible
        bool isJointsVisible() { return this->jointsVisible; }
        //! Show joints
        void showJoints() { this->jointsVisible = true; }
        //! Hide joints
        void hideJoints() { this->jointsVisible = false; }
        //! Are bodies visible
        bool isBodiesVisible() { return this->bodiesVisible; }
        //! Show bodies
        void showBodies() { this->bodiesVisible = true; }
        //! Hide bodies
        void hideBodies() { this->bodiesVisible = false; }
        //! Are triggers visible
        bool isTriggersVisible() { return this->triggersVisible; }
        //! Show triggers
        void showTriggers() { this->triggersVisible = true; }
        //! Hide triggers
        void hideTriggers() { this->triggersVisible = false; }

    protected:
        // enable debug information
        bool visible;
        // static Worldboundaries visible
        bool visibleWorldBoundaries;
        // rays visible
        bool raysVisible;
        // joints visible
        bool jointsVisible;
        // bodies visible
        bool bodiesVisible;
        // triggers visible
        bool triggersVisible;

    // CALLBACKS
    public:
        //! Get a function pointer to the Body Iterator Function CallBack
        virtual NewtonBodyIterator getForEachBodyCallBack() { return this->pForEachBodyCallBack; }
        //! Set the function pointer for the Body Iterator CallBack
        virtual void setForEachBodyCallBack(NewtonBodyIterator pForEachBodyCallBack) { this->pForEachBodyCallBack = pForEachBodyCallBack; }
        //! Get a function pointer to the Collision Iterator Function CallBack
        virtual NewtonCollisionIterator getForEachPolygonCallBack() { return this->pForEachPolygonCallBack; }
        //! Set the function pointer for the Collision Iterator CallBack
        virtual void setForEachPolygonCallBack(NewtonCollisionIterator pForEachPolygonCallBack) { this->pForEachPolygonCallBack = pForEachPolygonCallBack; }

    protected:
        // A pointer to the Body Iterator CallBack
        NewtonBodyIterator pForEachBodyCallBack;
        // A pointer to the Body Polygon CallBack
        NewtonCollisionIterator pForEachPolygonCallBack;

    // DRAWING FUNCTIONS
    protected:
        //! Draw World Boundaries
        virtual void drawWorldBoundaries() = 0;
        //! Draw all the bodies in the newton world
        virtual void drawBodies() = 0;
        //! Draw all rays which have been added to the debugger for this frame
        virtual void drawRays() = 0;
        //! Draw all joints that have been added to the debugger for this frame
        virtual void drawJoints() = 0;
        //! Draw all vehicles that have been added to the debugger for this frame
        virtual void drawVehicles() = 0;
        //! Draw all triggers that have been added to the debugger for this frame
        virtual void drawTriggers() = 0;
        //! Draw all the collision frames that have been added to the debugger for this frame
        virtual void drawCollisionFrames() = 0;
        //! Draw all the Buoyancy Planes that have been added to the debugger for this frame
        virtual void drawBuoyancyPlane() = 0;


    // Add Objects to the render for this frame
    public:
        ////! Add a body to the debugger for drawing. After rendering a ray is removed from the debugger
        //virtual void addBody(IPhysicsBody*);
        //! Add a ray to the debugger for drawing. After rendering a ray is removed from the debugger
        virtual void addRay(IPhysicsRay* pRay);
        //! Add a joint to the debugger for drawing. After rendering a joint is removed from the debugger
        virtual void addJoint(IPhysicsJoint* pJoint);
        //! Add a vehicle to the debugger for drawing. After rendering the vehicle will be removed from the debugger
        virtual void addVehicle(IPhysicsVehicle* pVehicle);
        //! Add a Trigger to the debugger for drawing. After rendered a trigger is removed from the debugger
        virtual void addTrigger(IPhysicsTrigger* pTrigger);
        //! Add a CollisionFrame to the debugger for drawing. After rendered a CollisionFrame is removed from the debugger
        virtual void addCollisionFrame(NewtonCollision* pNewtonCollision);
        //! Add a BuoyancyPlane to the debugger for drawing. After rendered a buoyancy plane is removed from the debugger
        virtual void addBuoyancyPlane(PhysicsBuoyancyPlane buoyancyPlane);
        //! Add a RagDoll to the debugger for drawing. After rendered a RagDoll plane is removed from the debugger
        virtual void addRagDoll(IPhysicsRagDoll* pRagDoll);

    public:
        ////! Clear Bodies
        //void clearBodies()
        //{
        //    for(std::vector<IPhysicsBody*>::iterator iter = this->bodies.begin(); iter != this->bodies.end(); iter++)
        //        delete *iter;
        //    this->bodies.clear();
        //}
        //! Clear Rays
        void clearRays()
        {
            for(std::vector<IPhysicsRay*>::iterator iter = this->rays.begin(); iter != this->rays.end(); iter++)
                delete *iter;
            //std::cout << "Clear rays" << std::endl;
            this->rays.clear();
        }
        //! Clear Joints
        void clearJoints()
        {
            //for(std::vector<IPhysicsJoint*>::iterator iter = this->joints.begin(); iter != this->joints.end(); iter++)
                //delete *iter;
            this->joints.clear();
        }
        //! Clear Vehicles
        void clearVehicles()
        {
            //for(std::vector<IPhysicsVehicle*>::iterator iter = this->vehicles.begin(); iter != this->vehicles.end(); iter++)
                //delete *iter;
            this->vehicles.clear();
        }
        //! Clear Triggers
        void clearTriggers()
        {
            //for(std::vector<IPhysicsTrigger*>::iterator iter = this->triggers.begin(); iter != this->triggers.end(); iter++)
                //delete *iter;
            this->triggers.clear();
        }
        //! Clear CollisionFrames
        void clearCollisionFrames()
        {
            this->collisionFrames.clear();
        }
        //! Clear BuoyancyPlanes
        void clearBuoyancyPlanes()
        {
            this->buoyancyPlanes.clear();
        }
        //! Clear RagDolls
        void clearRagDolls()
        {
            for(std::vector<IPhysicsRagDoll*>::iterator iter = this->ragDolls.begin(); iter != this->ragDolls.end(); iter++)
                delete *iter;
            this->ragDolls.clear();
        }

    protected:
        //// An STL vector for NewtonBodies
        //std::Vector<IPhysicsBody*> bodies;
        // An STL vector for Ray information
        std::vector<IPhysicsRay*> rays;
        // An STL vector for joint information
        std::vector<IPhysicsJoint*> joints;
        // An STL Vector for vehicle information
        std::vector<IPhysicsVehicle*> vehicles;
        // An STL Vector for trigger information
        std::vector<IPhysicsTrigger*> triggers;
        // An STL Vector for NewtonCollision information
        std::vector<NewtonCollision*> collisionFrames; // NOTE: there is no way of recursing through the geometry of a collision frame in newton, we cant implement this
        // An STL Vector for Buoyancy Planes
        std::vector<PhysicsBuoyancyPlane> buoyancyPlanes;
        // An STL Vector for RagDoll information
        std::vector<IPhysicsRagDoll*> ragDolls;
};

#endif // IPHYSICSDEBUGGER_H
