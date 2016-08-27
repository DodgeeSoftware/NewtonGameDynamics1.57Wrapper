/**
  * @file   PhysicsCollisionFrameFactory.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsCollisionFrameFactory is a factory which
  * provides a number of functions that produces
  * PhysicsCollisionFrames based on given parametres
**/

#ifndef PHYSICSCOLLISIONFRAMEFACTORY_H
#define PHYSICSCOLLISIONFRAMEFACTORY_H

// C++ Includes
#include <string>
#include <cstddef>
#include <newton.h>

// LUA Includes
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
// LUABIND Includes
#include "luabind/luabind.hpp"

// GAMEPHYSICS Includes
#include "NewtonAABB.h"
#include "NewtonFreezeThreshold.h"
#include "NewtonGlobalScale.h"
#include "NewtonMassMatrix.h"
#include "NewtonMatrix4.h"
#include "NewtonVector3.h"
#include "PhysicsCollisionFrameTypes.h"

/* NOTE: VERY VERY IMPORTANT NOTE!!!
    If you try factoring in a scale component into your offset matrix, Newton doesn't recalulate the AABBs for the collision frame.
    The effect of this is that the broad phase collision testing (AABB to AABB) will break down. DO NOT USE OFFSET MATRICES TO
    SCALE YOUR OBJECTS
    NewtonCollisionCalculateAABB is able to calculate the AABB and return it as two points but the method
    doesn't set the AABB for the collision frame. To the best of my knowledge there is no way to set the AABB for a collision frame
    in Newton 1.53 */
/**
  * @brief The PhysicsCollisionFrameFactory makes collision frames for PhysicsBodies.
  * Each function automatically scales primitives to the size of the render. This
  * scaling factor is set in NewtonGlobalScale.h
  * @author Shem Taylor
  **/
class PhysicsCollisionFrameFactory
{
    public:
        //! Default constructor
        PhysicsCollisionFrameFactory()
        {
            this->pNewtonWorld = 0;
        }
        //! Destructor
        virtual ~PhysicsCollisionFrameFactory() {}

//    public:
//        //! Initialise the physics collision frames factory
//        /**
//          * @return true if successful
//          **/
//        virtual bool init();
//        //! Free the physics collision frames factory
//        /**
//          * @return nothing
//          **/
//        virtual void free();

    public:
        //! Get the NewtonWorld
        const NewtonWorld* getNewtonWorld()
        {
            return this->pNewtonWorld;
        }
        //! Set the NewtonWorld
        virtual void setNewtonWorld(NewtonWorld* pNewtonWorld)
        {
            this->pNewtonWorld = pNewtonWorld;
        }

    public:
        //! Create a null collision frame
        /**
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createNullCollisionFrame();
        //! Create a box collision frame
        /**
          * @brief Uses default offset matrix if none is provided
          * @param size The size of the box collision frame
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createBoxCollisionFrame(float sizeX, float sizeY, float sizeZ);
        //! Create a box collision frame - with offset matrix
        /**
          * @param size The size of the box collision frame
          * @param offset The offset matrix for collision frame construction
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createBoxCollisionFrame(float sizeX, float sizeY, float sizeZ, NewtonMatrix4 offset);
        //! Create a sphere collision frame
        /**
          * @brief Uses default offset matrix if none is provided
          * @param size The size of the sphere collision frame
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createSphereCollisionFrame(float size);
        //! Create a sphere collision frame
        /**
          * @brief Uses default offset matrix if none is provided
          * @param size The size of the sphere collision frame
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createSphereCollisionFrame(float sizeX, float sizeY, float sizeZ);
        //! Create a sphere collision frame - with offset matrix
        /**
          * @param size The size of the sphere collision frame
          * @param offset The offset matrix for collision frame construction
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createSphereCollisionFrame(float sizeX, float sizeY, float sizeZ, NewtonMatrix4 offset);
        //! Create a cone collision frame
        /**
          * @brief Uses default offset matrix if none is provided
          * @param radius The radius of the cone
          * @param height The height of the cone
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createConeCollisionFrame(float radius, float height);
        //! Create a cone collision frame - with offset matrix
        /**
          * @param radius The radius of the cone
          * @param height The height of the cone
          * @param offset The offset matrix for collision frame construction
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createConeCollisionFrame(float radius, float height, NewtonMatrix4 offset);
        //! Create a capsule collision frame
        /**
          * @brief Uses default offset matrix if none is provided
          * @param radius The radius of the capsule
          * @param height The height of the capsule
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createCapsuleCollisionFrame(float radius, float height);
        //! Create a capsule collision frame - with offset matrix
        /**
          * @param radius The radius of the capsule
          * @param height The height of the capsule
          * @param offset The offset matrix for collision frame construction
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createCapsuleCollisionFrame(float radius, float height, NewtonMatrix4 offset);
        //! Create a cylinder collision frame
        /**
          * @brief Uses default offset matrix if none is provided
          * @param radius The radius of the cylinder
          * @param height The height of the cylinder
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createCylinderCollisionFrame(float radius, float height);
        //! Create a cylinder collision frame - with offset matrix
        /**
          * @param radius The radius of the cylinder
          * @param height The height of the cylinder
          * @param offset The offset matrix for collision frame construction
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createCylinderCollisionFrame(float radius, float height, NewtonMatrix4 offset);
        //! Create a camphor cylinder collision frame
        /**
          * @brief Uses default offset matrix if none is provided
          * @param radius The radius of the camphor cylinder
          * @param height The height of the camphor cylinder
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createChampherCylinderCollisionFrame(float radius, float height);
        //! Create a camphor cylinder collision frame - with offset matrix
        /**
          * @param radius The radius of the camphor cylinder
          * @param height The height of the camphor cylinder
          * @param offset The offset matrix for collision frame construction
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createChampherCylinderCollisionFrame(float radius, float height, NewtonMatrix4 offset);
        //! Create a convex Hull collision frame from a vertex array
        /**
          * @brief Uses default offset matrix
          * @param vertexCount The number of verticies to use
          * @param vertexArray An array of verticies to construct the convex hull from
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createConvexHullCollisionFrame(int vertexCount, float* vertexArray);
        //! Create a convex Hull collision frame from a vertex array
        /**
          * @brief Uses default offset matrix
          * @param vertexCount The number of verticies to use
          * @param vertexArray An array of verticies to construct the convex hull from
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createConvexHullCollisionFrame(int vertexCount, float* vertexArray, NewtonMatrix4 offset);

    public:
        //! Create a compound collision frame from an array of convex hulls
        /**
          * @param array An array of newton convex hull collisions
          * @param numberOfHullsInArray An array of newton convex hull collisions
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* createCompoundCollisionFrame(NewtonCollision* array[], int numberOfHullsInArray);
        //! Convert to a convex hull
        /**
          * @brief Converts a newton collision to a convex hull
          * @param collisionFrame The collision frame to convert
          * @return A newly created NewtonCollision pointer
          **/
        virtual NewtonCollision* convertToConvexHullCollisionFrame(NewtonCollision* pCollisionFrame);

    public:
        //! Release a collision Frame
        /**
          * @brief Releases a NewtonCollision
          * @param a pointer to the NewtonCollision frame to release
          * @return nothing
        **/
        virtual void realeaseCollisionFrame(NewtonCollision* pNewtonCollision);

    protected:
        //! Maintain a pointer to the Newton world
        NewtonWorld* pNewtonWorld;

};

#endif // PHYSICSCOLLISIONFRAMEFACTORY_H
