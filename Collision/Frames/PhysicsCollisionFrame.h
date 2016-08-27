/**
  * @file   PhysicsCollisionFrame.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsCollisionFrame is a wrapper around
  * a NewtonCollision object and is used to build NewtonBodies which.
  * are the basis of PhysicsBodies
**/

#ifndef PHYSICSCOLLISIONFRAME_H
#define PHYSICSCOLLISIONFRAME_H

// C++ Includes
#include <cmath>
#include <vector>
// LUA Includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
// LUA BIND Includes
#include <luabind/luabind.hpp>
// NEWTON INCLUDES
#include <cstddef>
// NEWTON GAME DYNAMICS Includes
#include <newton.h>
// GAMEPHYSICS Includes
#include "NewtonUtils.h"
#include "PhysicsCollisionFrameTypes.h"

/** The PhysicsCollisionFrame class is a wrapper around a NewtonCollision Object. The PhysicsCollisionFrame can used as a collision object
    on its own but doing so will require you to manually handle collisions **/
class PhysicsCollisionFrame
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        PhysicsCollisionFrame()
        {
            this->pNewtonWorld = 0;
            this->pNewtonCollision = 0;
            //this->newtonCollisionMatrix.makeIdentity();
            //this->newtonCollisionVelocity.setPosition(0.0f, 0.0f, 0.0f);
            //this->newtonCollisionAngularVelocity.setPosition(0.0f, 0.0f, 0.0f);
            this->newtonCollisionType = PCFT_NOT_SET;
            this->newtonCollisionModifiable = false;
        }
        //! Destructor
        virtual ~PhysicsCollisionFrame()
        {
            if (this->pNewtonWorld != 0 &&  this->pNewtonCollision != 0)
                NewtonReleaseCollision(this->pNewtonWorld, this->pNewtonCollision);
        }

    protected:
        // Methods and members

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Get NewtonCollision
        virtual NewtonCollision* getNewtonCollision();
        //! Set NewtonCollision
        virtual void setNewtonCollision(NewtonCollision* pNewtonCollision);
        //! Get CollisionFrameType
        E_PHYSICS_COLLISIONFRAME_TYPE getNewtonCollisionType();
        //! Get the Volume of space this collision frame occupies
        virtual dFloat getNewtonCollisionVolume();
        //! Get Axis-Aligned Bounding Box
        virtual NewtonAABB getNewtonCollisionAABB();
        //! Make Unique [Makes the CollisionFrame Unique aka not a reference to an instance inside Newton]
        virtual void makeNewtonCollisionUnique();
        //! Clear
        void clear();

    protected:
        // Newton Collision Frame
        NewtonCollision* pNewtonCollision;
        // Collision Frame type
        E_PHYSICS_COLLISIONFRAME_TYPE newtonCollisionType;

    // ****************************
    // * CONVEX HULL MODIFICATION *(to use these you should make sure the CollisionFrame is unique (PhysicsCollisionFrame::makeNewtonCollisionUnique)and you must call the makeConvexHullModifiable after that
    // ****************************
    public:
        //! Is this Convex Hull Modifiable with a ConvexHull Matrix
        virtual bool isNewtonCollisionModifiable();
        //! Make ConvexHull Modifiable
        virtual bool makeNewtonCollisionConvexHullModifiable();
        // NOTE: No function exists to make the Collisions frame unModifiable / locked in the NewtonLibrary
        /** getConvexHullMatrix
          * @brief This function only works on convex hull type collision frames. It can be used to change the orientation
          *         size or offset after the frame has been made. Must call makeConvexHullModifiable before this function can
          *         be used
        **/
        virtual NewtonMatrix4 getNewtonCollisionConvexHullMatrix();
        /** setConvexHullMatrix
          * @brief This function only works on convex hull type collision frames. It can be used to change the orientation
          *         size or offset after the frame has been made. Must call makeConvexHullModifiable before this function can
          *         be used
        **/
        virtual void setNewtonCollisionConvexHullMatrix(NewtonMatrix4& matrix);

    protected:
        // If this is a convex hull, can it be altered with a convexhull modifier
        bool newtonCollisionModifiable;

    /* The functions in this section are only used when this CollisionFrame is being used seperately from a NewtonBody/PhysicsBody
        as an independant collision object (aka being processed with the generic collision functions) using these functions will have
        no effect on NewtonBodies made with this CollisionFrame */
    // *******************
    // * TRANSFORMATIONS *
    // *******************
    public:
        //! Get Position
        virtual NewtonVector3 getNewtonCollisionPosition() { return this->newtonCollisionMatrix.getTranslation(); }
        //! Set Position
        virtual void setNewtonCollisionPosition(float x, float y, float z) { this->newtonCollisionMatrix.setTranslation(x, y, z); }
        //! Set Position
        virtual void setNewtonCollisionPosition(NewtonVector3 newtonCollisionPosition) { this->newtonCollisionMatrix.setTranslation(newtonCollisionPosition.getX(), newtonCollisionPosition.getY(), newtonCollisionPosition.getZ()); }
        //! Get Velocity
        virtual NewtonVector3 getNewtonCollisionVelocity() { return this->newtonCollisionVelocity; }
        //! Set Velocity
        virtual void setNewtonCollisionVelocity(NewtonVector3 newtonCollisionVelocity) { this->newtonCollisionVelocity = newtonCollisionVelocity; }
        //! Set Velocity
        virtual void setNewtonCollisionVelocity(float x, float y, float z) { this->newtonCollisionVelocity.setPosition(x, y, z); }
        //! Get Angular Velocity
        virtual NewtonVector3 getNewtonCollisionAngularVelocity() { return this->newtonCollisionAngularVelocity; }
        //! Set Angular Velocity
        virtual void setNewtonCollisionAngularVelocity(NewtonVector3 newtonCollisionAngularVelocity) { this->newtonCollisionAngularVelocity = newtonCollisionAngularVelocity; }
        //! Set Angular Velocity
        virtual void setNewtonCollisionAngularVelocity(float x, float y, float z) { this->newtonCollisionAngularVelocity.setPosition(x, y, z); }
        //! Get Matrix
        virtual NewtonMatrix4* getNewtonCollisionMatrix() { return &(this->newtonCollisionMatrix); }
        //! Set Matrix
        virtual void setNewtonCollisionMatrix(float* newtonCollisionMatrix) { this->newtonCollisionMatrix.setMatrix(newtonCollisionMatrix); }
        //! Set Matrix
        virtual void setNewtonCollisionMatrix(NewtonMatrix4 newtonCollisionMatrix) { this->newtonCollisionMatrix = newtonCollisionMatrix; }

    protected:
        // Offset matrix
        NewtonMatrix4 newtonCollisionMatrix;
        // Velocity of this Collision Frame
        NewtonVector3 newtonCollisionVelocity;
        // Angular Velocity of this Collision Frame
        NewtonVector3 newtonCollisionAngularVelocity;

    // ****************
    // * NEWTON WORLD *
    // ****************
    public:
        //! Get NewtonWorld
        NewtonWorld* getNewtonWorld() { return this->pNewtonWorld; }
        //! Set NewtonWorld
        void setNewtonWorld(NewtonWorld* pNewtonWorld) { this->pNewtonWorld = pNewtonWorld; }

    protected:
        // Newton World
        NewtonWorld* pNewtonWorld;

    // ********
    // * MESH * (used by the debugger)
    // ********
    public:
        //! Get Mesh
        virtual void* getMesh() { return this->pMesh; }
        //! Set Mesh
        virtual void setMesh(void* pMesh) { this->pMesh = pMesh; }

    protected:
        // Pointer to the mesh
        void* pMesh;

    // ************
    // * BINDINGS *
    // ************
    public:
        //! Bind this class to a luaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // PHYSICSCOLLISIONFRAME_H
