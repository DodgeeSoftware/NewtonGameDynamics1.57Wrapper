#include "PhysicsWorld.h"

bool PhysicsWorld::init(NewtonAllocMemory allocMemory, NewtonFreeMemory freeMemory)
{
    // create the Newton world
    this->pNewtonWorld = NewtonCreate(allocMemory, freeMemory);
    // return false if the Newton world could not be made
    if (this->pNewtonWorld == 0)
        return false;
    // set the size of the Newton world
    this->setWorldSize(this->worldSize);
    // the Newton world can hold user data. The user data will be a pointer to this class
    NewtonWorldSetUserData(this->pNewtonWorld, this);
    // initialisation of the physics world successful
    return true;
}

void PhysicsWorld::update(float deltaTime)
{
    // Integrate the Physics for this frame
    NewtonUpdate(this->pNewtonWorld, deltaTime);
}

void PhysicsWorld::clear()
{
    // TODO: implement me
}

void PhysicsWorld::free()
{
    if (this->pNewtonWorld != 0)
    {
        /* NOTE: This function is only called when getting rid of the physics world
                    it autiomatically clears everything attached to the world with
                    NewtonDestroy(pNewtonWorld), but I am alittle worried about
                    the possibility that their could still be groups left
                    after a world is destroyed */
        NewtonMaterialDestroyAllGroupID(this->pNewtonWorld);
        NewtonDestroyAllBodies(this->pNewtonWorld);
        NewtonDestroy(this->pNewtonWorld);
        this->pNewtonWorld = 0;
    }
}

NewtonWorld* PhysicsWorld::getNewtonWorld()
{
    return this->pNewtonWorld;
}

// TODO: Need to remove these from the world method
float PhysicsWorld::getGlobalScale()
{
    return this->globalScale; // Not implemented in newton.h method NewtonGetGlobalScale(pNewtonWorld);
}

void PhysicsWorld::setGlobalScale(float globalScale)
{
    this->globalScale = globalScale;
}

E_SOLVER_MODEL PhysicsWorld::getSolverModel()
{
    return this->solverModel;
}

void PhysicsWorld::setSolverModel(E_SOLVER_MODEL model)
{
    if (this->pNewtonWorld != 0)
    {
        this->solverModel = model;
        NewtonSetSolverModel(this->pNewtonWorld, model);
    }
}

E_PLATFORM_ARCHITECTURE PhysicsWorld::getPlatformArchitecture()
{
    return this->platformArchitecture;
}

void PhysicsWorld::setPlatformArchitecture(E_PLATFORM_ARCHITECTURE architecture)
{
    if (this->pNewtonWorld != 0)
    {
        this->platformArchitecture = architecture;
        NewtonSetPlatformArchitecture(this->pNewtonWorld, architecture);
    }
}

E_FRICTION_MODEL PhysicsWorld::getFrictionModel()
{
    return this->frictionModel;
}

void PhysicsWorld::setFrictionModel(E_FRICTION_MODEL model)
{
    if (this->pNewtonWorld != 0)
    {
        this->frictionModel = model;
        NewtonSetFrictionModel(this->pNewtonWorld, model);
    }
}

float PhysicsWorld::getMinimumFrameRate()
{
    return this->minimumFrameRate;
}

void PhysicsWorld::setMinimumFrameRate(float rate)
{
    if (this->pNewtonWorld != 0)
    {
        this->minimumFrameRate = rate;
        NewtonSetMinimumFrameRate(this->pNewtonWorld, rate);
    }
}

float PhysicsWorld::getTimeStep()
{
    if (this->pNewtonWorld == 0)
        return 0.0f;
    return NewtonGetTimeStep(this->pNewtonWorld);
}

void PhysicsWorld::destroyAllBodies()
{
    if (this->pNewtonWorld != 0)
    {
        NewtonDestroyAllBodies(this->pNewtonWorld);
        /* a call to Newton destroy all bodies will reset the size of the physics world
           here we call Newton set were size to correct this behaviour */
        this->setWorldSize(this->worldSize);
    }
}

void PhysicsWorld::clearBuoyancy()
{
    // TODO: this function needs to clear buoyancy from newton not sure if it does right now
    // Clear Buoyancy Plane
    PhysicsBuoyancyPlane physicsBuoyancyPlane = PhysicsBuoyancyPlane();
    // Set Buoyancy Toggle
    bool buoyancy = false;
}

NewtonAABB PhysicsWorld::getWorldSize()
{
    return this->worldSize;
}

void PhysicsWorld::setWorldSize(NewtonAABB worldSize)
{
    /* TODO: remove the RenderScaleToNewton References and perform this operation somewhere else
            this way the wrapper can be rendering engine independent*/
    if (this->pNewtonWorld != 0)
    {
        float minEdge[3] = {worldSize.getMinEdgeX() * RenderScaleToNewton, worldSize.getMinEdgeY() * RenderScaleToNewton, worldSize.getMinEdgeZ() * RenderScaleToNewton};
        float maxEdge[3] = {worldSize.getMaxEdgeX() * RenderScaleToNewton, worldSize.getMaxEdgeY() * RenderScaleToNewton, worldSize.getMaxEdgeZ() * RenderScaleToNewton};
        NewtonSetWorldSize(this->pNewtonWorld, minEdge, maxEdge);
        this->worldSize = worldSize ;
    }
}

float PhysicsWorld::getNewtonVersion()
{
    // Return the Version of Newton
    return this->version;
}

void PhysicsWorld::setNewtonBodyLeaveWorldCallBack(NewtonBodyLeaveWorld pCallBack)
{
    NewtonSetBodyLeaveWorldEvent(this->pNewtonWorld, pCallBack);
}

NewtonVector3 PhysicsWorld::getGravity()
{
    return this->gravity;
}

void PhysicsWorld::setGravity(float x, float y, float z)
{
        this->gravity = NewtonVector3(x, y, z);
}

void PhysicsWorld::setGravity(NewtonVector3 vec)
{
    this->gravity = vec;
}

void PhysicsWorld::bindToLua(lua_State* pLuaState)
{
    // TODO: implement me

    /* TODO: Bindings for the EFrictionModel
        EPlatformArchitecutre, ESolverModel enumerations */
}



