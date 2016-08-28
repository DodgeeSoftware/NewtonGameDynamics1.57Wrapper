#ifndef PHYSICSBODYFACTORY_H
#define PHYSICSBODYFACTORY_H

/* This class has dependencies on Irrlicht so that we can load meshes using the SceneManager and transform them into
    NewtonBodies */
#include <cstddef>
#include <irrlicht.h>
#include <newton.h>
#include "NewtonAABB.h"
#include "NewtonMatrix4.h"
#include "NewtonVector.h"
#include "PhysicsCollisionFramesFactory.h"
#include "PhysicsBodyTypes.h"

/** @class PhysicsBodyFactory
  * @brief The PhysicsBodyFactory class factory that Produces
  * PhysicsBodies **/
class PhysicsBodyFactory
{
    // ****************
    // * CONSTRUCTORS *
    // ****************
    public:
        //! Default Constructor
        PhysicsBodyFactory()
        {
            this->pNewtonWorld = 0;
        }
        //! Destructor
        virtual ~PhysicsBodyFactory() {}

    protected:
        ////! Copy Constructor
        //PhysicsBodyFactory(PhysicsBodyFactory& other) {}

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Initialise the Factory
        virtual bool init(irr::IrrlichtDevice* pDevice, NewtonWorld* pNewtonWorld)
        {
            // Initialise the collision frames Factory
            if (this->physicsCollisionFramesFactory.init(pDevice, pNewtonWorld) == false)
            {
                // Failure
                return false;
            }
            // Store a local reference to the NewtonWorld
            this->pNewtonWorld = pNewtonWorld;
            // Success
            return true;
        }
        //! Free the Factory
        virtual void free()
        {
            // Free the Collision Frame Factory
            this->physicsCollisionFramesFactory.free();
            // Clean up pointer to the NewtonWorld
            this->pNewtonWorld = 0;
        }

    public:
        //! Create a null collision frame
        /**
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createNullBody();
        //! Create a box collision frame
        /**
          * @brief Uses default offset matrix if none is provided
          * @param size The size of the box collision frame
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createBoxBody(float sizeX, float sizeY, float sizeZ);
        //! Create a box collision frame - with offset matrix
        /**
          * @param size The size of the box collision frame
          * @param offset The offset matrix for collision frame construction
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createBoxBody(float sizeX, float sizeY, float sizeZ, irr::core::matrix4 offset);
        //! Create a sphere collision frame
        /**
          * @brief Uses default offset matrix if none is provided
          * @param size The size of the sphere collision frame
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createSphereBody(float sizeX, float sizeY, float sizeZ);
        //! Create a sphere collision frame - with offset matrix
        /**
          * @param size The size of the sphere collision frame
          * @param offset The offset matrix for collision frame construction
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createSphereBody(float sizeX, float sizeY, float sizeZ, irr::core::matrix4 offset);
        //! Create a cone collision frame
        /**
          * @brief Uses default offset matrix if none is provided
          * @param radius The radius of the cone
          * @param height The height of the cone
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createConeBody(float radius, float height);
        //! Create a cone collision frame - with offset matrix
        /**
          * @param radius The radius of the cone
          * @param height The height of the cone
          * @param offset The offset matrix for collision frame construction
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createConeBody(float radius, float height, irr::core::matrix4 offset);
        //! Create a capsule collision frame
        /**
          * @brief Uses default offset matrix if none is provided
          * @param radius The radius of the capsule
          * @param height The height of the capsule
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createCapsuleBody(float radius, float height);
        //! Create a capsule collision frame - with offset matrix
        /**
          * @param radius The radius of the capsule
          * @param height The height of the capsule
          * @param offset The offset matrix for collision frame construction
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createCapsuleBody(float radius, float height, irr::core::matrix4 offset);
        //! Create a cylinder collision frame
        /**
          * @brief Uses default offset matrix if none is provided
          * @param radius The radius of the cylinder
          * @param height The height of the cylinder
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createCylinderBody(float radius, float height);
        //! Create a cylinder collision frame - with offset matrix
        /**
          * @param radius The radius of the cylinder
          * @param height The height of the cylinder
          * @param offset The offset matrix for collision frame construction
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createCylinderBody(float radius, float height, irr::core::matrix4 offset);
        //! Create a camphor cylinder collision frame
        /**
          * @brief Uses default offset matrix if none is provided
          * @param radius The radius of the camphor cylinder
          * @param height The height of the camphor cylinder
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createChampherCylinderBody(float radius, float height);
        //! Create a camphor cylinder collision frame - with offset matrix
        /**
          * @param radius The radius of the camphor cylinder
          * @param height The height of the camphor cylinder
          * @param offset The offset matrix for collision frame construction
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createChampherCylinderBody(float radius, float height, irr::core::matrix4 offset);
        //! Create a convex Hull collision frame from a vertex array
        /**
          * @brief Uses default offset matrix
          * @param vertexCount The number of verticies to use
          * @param vertexArray An array of verticies to construct the convex hull from
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createConvexHullBody(int vertexCount, float* vertexArray);
        //! Create a convex Hull collision frame from file
        /**
          * @brief Uses default offset matrix
          * @param filename The filename of the mesh
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createConvexHullBody(const char* filename);
        //! Create a convex Hull collision frame from mesh
        /**
          * @brief Uses default offset matrix
          * @param mesh A pointer to an irrlicht mesh
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createConvexHullBody(irr::scene::IMesh* pMesh);
        //! Create a tree collision frame from a file
        /**
          * @brief Uses default offset matrix
          * @param filename The filename of the mesh
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createTreeBody(const char* filename);
        //! Create a tree collision frame from a mesh
        /**
          * @brief Uses default offset matrix
          * @param mesh A pointer to an irrlicht mesh
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createTreeBody(irr::scene::IMesh* pMesh);
        //! Create a compound collision frame from an array of convex hulls
        /**
          * @param array An array of newton convex hull collisions
          * @param numberOfHullsInArray An array of newton convex hull collisions
          * @return A newly created NewtonBody pointer
          **/
        virtual NewtonBody* createCompoundBody(NewtonCollision* array[], int numberOfHullsInArray);

    protected:
        //! Make Body
        virtual NewtonBody* makeBody(NewtonCollision* pCollisionFrame);

    protected:
        //! Newton World
        NewtonWorld* pNewtonWorld;
        //! A factory to create the collision frames
        PhysicsCollisionFramesFactory physicsCollisionFramesFactory;

};

#endif // PHYSICSBODYFACTORY_H
