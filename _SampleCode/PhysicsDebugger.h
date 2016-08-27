#ifndef PHYSICSDEBUGGER_H
#define PHYSICSDEBUGGER_H

#include <iostream>
#include <cstddef>
#include <vector>

/* This Debugger was written specifically for Irrlicht and so has dependencies*/
#include <irrlicht.h>
#include <newton.h>
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonGlobalScale.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"
#include "PhysicsWorld.h"
#include "IPhysicsDebugger.h"
#include "IPhysicsRay.h"
#include "IPhysicsJoint.h"
#include "PhysicsBallAndSocketJoint.h"
#include "PhysicsCorkscrewJoint.h"
#include "PhysicsCustomJoint.h"
#include "PhysicsHingeJoint.h"
#include "PhysicsSliderJoint.h"
#include "PhysicsUniversalJoint.h"
#include "PhysicsUpVectorJoint.h"

#include "PhysicsUtils.h"

/**
  * @brief The PhysicsDebugger is a singleton class which renders a wireframe version of a Newton World.
  **/
class PhysicsDebugger : public IPhysicsDebugger
{
    public:
        //! Constructor
        PhysicsDebugger()
        {
            // Setup member variables
            this->pIrrlichtDevice = 0;
            this->visible = false;
            this->triggersVisible = true;
            this->jointsVisible = true;
            this->raysVisible = true;
            this->visibleWorldBoundaries = true;
            //TODO: implement vehicles visible, worldboundaries visible etc
            // Build default material settings
            this->material.setFlag(irr::video::EMF_LIGHTING, false);
            this->material.setFlag(irr::video::EMF_ZWRITE_ENABLE, true);
            this->material.setFlag(irr::video::EMF_ZBUFFER, true);
            this->material.setFlag(irr::video::EMF_ANTI_ALIASING, false);
            this->material.Thickness = 1.0f;
            // Build default colour scheme
            this->worldBoxColour = irr::video::SColor(255, 128, 128, 128); // Grey
            this->axisAlignedBoundingBoxColour = irr::video::SColor(255, 255, 255, 255); // White
            this->geometryColour = irr::video::SColor(255, 128, 128, 128);  // Grey
            this->jointColour = irr::video::SColor(255, 255, 0, 0); // Red
            this->vehicleColour = irr::video::SColor(255, 128, 128, 128); // Grey
            this->triggerColour = irr::video::SColor(255, 0, 255, 0); // Green
            this->rayColour = irr::video::SColor(255, 255, 255, 255); // White
            this->rayNormalColour = irr::video::SColor(255, 255, 0, 0); // Red
            this->buoyancyPlaneColour = irr::video::SColor(255, 0, 0, 255); // Blue
            this->collisionFrameColour = irr::video::SColor(255, 255, 255, 0); // Yellow
        }
        //! Destructor
        virtual ~PhysicsDebugger() {}

    // IRRLICHT DEVICE
    public:
        //! Get the Irrlicht Device for the Debugger
        virtual irr::IrrlichtDevice* getIrrlichtDevice() { return this->pIrrlichtDevice; }
        //! Set the Irrlicht Device for the Debugger
        virtual void setIrrlichtDevice(irr::IrrlichtDevice* pIrrlichtDevice) { this->pIrrlichtDevice = pIrrlichtDevice; }

    protected:
        //! Maintain a pointer to the Irrlicht Device
        irr::IrrlichtDevice* pIrrlichtDevice;

    // DRAWING FUNCTIONS
    protected:
        //! Draw World Boundaries
        virtual void drawWorldBoundaries();
        //! Draw all the bodies in the newton world
        virtual void drawBodies();
        //! Draw all rays which have been added to the debugger
        virtual void drawRays();
        //! Draw all joints that have been added to the debugger
        virtual void drawJoints();
        //! Draw all vehicles that have been added to the debugger
        virtual void drawVehicles();
        //! Draw all triggers that have been added to the debugger
        virtual void drawTriggers();
        //! Draw all the collision frames that have been added to the debugger for this frame
        virtual void drawCollisionFrames();
        //! Draw all the Buoyancy Planes that have been added to the debugger for this frame
        virtual void drawBuoyancyPlane();

    // JOINT DRAWING FUNCTIONS
        //! Draw BallAndSocketJoint
        virtual void drawBallAndSocketJoint(PhysicsBallAndSocketJoint* pPhysicsBallAndSocketJoint);
        //! Draw CorkscewJoint
        virtual void drawCorkscrewJoint(PhysicsCorkscrewJoint* pPhysicsCorkscrewJoint);
        //! Draw CustomJoint
        virtual void drawCustomJoint(PhysicsCustomJoint* pPhysicsCustomJoint);
        //! Draw HingeJoint
        virtual void drawHingeJoint(PhysicsHingeJoint* pPhysicsHingeJoint);
        //! Draw Slider Joint
        virtual void drawSliderJoint(PhysicsSliderJoint* pPhysicsSliderJoint);
        //! Draw Universal Joint
        virtual void drawUniversalJoint(PhysicsUniversalJoint* pPhysicsUniversalJoint);
        //! Draw UpVectorJoint
        virtual void drawUpVectorJoint(PhysicsUpVectorJoint* pPhysicsUpVectorJoint);

    // MATERIALS AND COLOURS
    public:
        //! Get Material
        irr::video::SMaterial& getMaterial() { return this->material; }
        //! Get WorldBox Colour
        irr::video::SColor getWorldBoxColour() { return this->worldBoxColour; }
        //! Set WorldBox Colour
        void setWorldBoxColour(irr::video::SColor colour) { this->worldBoxColour = colour; }
        //! Get axisAlignedBoundingBoxColor Colour
        irr::video::SColor getAxisAlignedBoundingBoxColour() { return this->axisAlignedBoundingBoxColour; }
        //! Set axisAlignedBoundingBoxColor Colour
        void setAxisAlignedBoundingBoxColour(irr::video::SColor colour) { this->axisAlignedBoundingBoxColour = colour; }
        //! Get GeometryColour Colour
        irr::video::SColor getGeometryColour() { return this->geometryColour; }
        //! Set GeometryColor Colour
        void setGeometryColour(irr::video::SColor colour) { this->geometryColour = colour; }
        //! Get JointColour Colour
        irr::video::SColor getJointColour() { return this->jointColour; }
        //! Set JointColour Colour
        void setJointColour(irr::video::SColor colour) { this->jointColour = colour; }
        //! Get VehicleColour Colour
        irr::video::SColor getVehicleColour() { return this->vehicleColour; }
        //! Set VehicleColour Colour
        void setVehicleColour(irr::video::SColor colour) { this->vehicleColour = colour; }
        //! Get TriggerColour Colour
        irr::video::SColor getTriggerColour() { return this->triggerColour; }
        //! Set TriggerColour Colour
        void setTriggerColour(irr::video::SColor colour) { this->triggerColour = colour; }
        //! Get RayColour
        irr::video::SColor getRayColour() { return this->rayColour; }
        //! Set RayColour Colour
        void setRayColour(irr::video::SColor colour) { this->rayColour = colour; }
        //! Get RayNormalColour
        irr::video::SColor getRayNormalColour() { return this->rayNormalColour; }
        //! Set RayNormalColour
        void setRayNormalColour(irr::video::SColor colour) { this->rayNormalColour = colour; }
        //! Get BuoyancyPlaneColour
        irr::video::SColor getBuoyancyPlaneColour() { return this->buoyancyPlaneColour; }
        //! Set BuoyancyPlaneColour
        void setBuoyancyPlaneColour(irr::video::SColor colour) { this->buoyancyPlaneColour = colour; }
        //! Get CollisionFrameColour
        irr::video::SColor getCollisionFrameColour() { return this->collisionFrameColour; }
        //! Set CollisionFrameColour
        void setCollisionFrameColour(irr::video::SColor colour) { this->collisionFrameColour = colour; }

    protected:
        //! Material Used By the renderer
        irr::video::SMaterial material;
        //! WorldBox Colour
        irr::video::SColor worldBoxColour;
        //! BoundingBox Colour
        irr::video::SColor axisAlignedBoundingBoxColour;
        //! Geometry Colour
        irr::video::SColor geometryColour;
        //! Joint Colour
        irr::video::SColor jointColour;
        //! Vehicle Colour
        irr::video::SColor vehicleColour;
        //! Trigger Colour
        irr::video::SColor triggerColour;
        //! Ray Colour
        irr::video::SColor rayColour;
        //! Ray Normal Colour
        irr::video::SColor rayNormalColour;
        //! Buoyancy Plane Colour
        irr::video::SColor buoyancyPlaneColour;
        //! Collision Frame Colour
        irr::video::SColor collisionFrameColour;
};

#endif // PHYSICSDEBUGGER_H
