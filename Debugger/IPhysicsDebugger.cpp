#include "IPhysicsDebugger.h"

bool IPhysicsDebugger::init()
{
    // Success
    return true;
}

void IPhysicsDebugger::update()
{

}

void IPhysicsDebugger::draw()
{
    // If the debugger isn't visible then don't draw
    if (this->visible == false)
        return;
    /* the reason why the physics world is being passed as a parameter here is because there is no get world size function
       in Newton game dynamics. In order to draw the world boundaries this function is required. */
    if (this->pNewtonWorld != 0)
    {
        // draw the world boundaries if they are visible
        this->drawWorldBoundaries();
        // Draw all Bodies in the scene
        this->drawBodies();
        // draw all of the rays added to the debugger
        this->drawRays();
        // draw all of the joints added to the debugger
        this->drawJoints();
        // draw all of the vechiles addded to the debugger
        this->drawVehicles();
        // draw all of the triggers addded to the debugger
        this->drawTriggers();
        // draw all of the collision frames addded to the debugger
        this->drawCollisionFrames();
        // draw all of the buoyancy planes addded to the debugger
        this->drawBuoyancyPlane();

    }
    // Clear Bodies
    //this->bodies.clear();
    // Clear rays
    this->clearRays();
    // Clear joints
    this->clearJoints();
    // Clear vehicles
    this->clearVehicles();
    // Clear triggers
    this->clearTriggers();
    // Clear collision frames
    this->clearCollisionFrames();
    // Clear Buoyancy planes
    this->clearBuoyancyPlanes();
    // Clear Rag Dolls
    this->clearRagDolls();
}

void IPhysicsDebugger::clear()
{
    // TODO: implement me
}

void IPhysicsDebugger::free()
{
    // Clear rays
    this->clearRays();
    // Clear joints
    this->clearJoints();
    // Clear vehicles
    this->clearVehicles();
    // Clear triggers
    this->clearTriggers();
    // Clear collision frames
    this->clearCollisionFrames();
    // Clear Buoyancy planes
    this->clearBuoyancyPlanes();
    // Clear Rag Dolls
    this->clearRagDolls();
}

void IPhysicsDebugger::addRay(IPhysicsRay* pRay)
{
    // Add a ray to the ray list
    this->rays.push_back(pRay->clone());
    //this->rays.push_back(pRay);
}

void IPhysicsDebugger::addJoint(IPhysicsJoint* pJoint)
{
    // Add a joint to the joint list
    this->joints.push_back(pJoint);
}

void IPhysicsDebugger::addVehicle(IPhysicsVehicle* pVehicle)
{
    // Add a vehicle to the vehicle list
    this->vehicles.push_back(pVehicle);
}

void IPhysicsDebugger::addTrigger(IPhysicsTrigger* pPhysicsTrigger)
{
    // Add a trigger to the trigger list
    this->triggers.push_back(pPhysicsTrigger);
}

void IPhysicsDebugger::addCollisionFrame(NewtonCollision* pNewtonCollision)
{
    // Add a collision frame to the colliison frame list
    this->collisionFrames.push_back(pNewtonCollision);
}

void IPhysicsDebugger::addBuoyancyPlane(PhysicsBuoyancyPlane buoyancyPlane)
{
    // Add a buoyancy plane to the buoyancy plane list
    this->buoyancyPlanes.push_back(buoyancyPlane);
}

void IPhysicsDebugger::addRagDoll(IPhysicsRagDoll* pRagDoll)
{
    this->ragDolls.push_back(pRagDoll);
}
