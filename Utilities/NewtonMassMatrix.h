/**
  * @file   MassMatrix.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  A Mass Matrix is a special mathematical Matrix used in analytical
  * mechanics. In NewtonGameDynamics there is a physical structure to an object
  * and a centre of mass for a physics body, a mass matrix sets how mass is distributed
  * across the volume **/

#ifndef NEWTONMASSMATRIX_H
#define NEWTONMASSMATRIX_H

// C++ Includes
#include <cstddef>

// LUA Includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
// LUABIND Includes
#include <luabind/luabind.hpp>

// NEWTON GAME DYNAMICS Includes
#include <newton.h>

/** @class NewtonMassMatrix
  * @brief The NewtonMassMatrix class is a container for the Moment of inertia for NewtonBodies
  * @detail A Mass Matrix is a special mathematical Matrix used in analytical
  * mechanics. In NewtonGameDynamics there is a physical structure to an object
  * and a centre of mass for a physics body, a mass matrix sets how mass is distributed
  * across the volume **/
class NewtonMassMatrix
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        NewtonMassMatrix()
        {
            this->mass = 0.0f;
            this->iX = 0.0f;
            this->iY = 0.0f;
            this->iZ = 0.0f;
        }
        //! Constructor
        NewtonMassMatrix(dFloat mass, dFloat iX, dFloat iY, dFloat iZ)
        {
            this->mass = mass;
            this->iX = iX;
            this->iY = iY;
            this->iZ = iZ;
        }
        //! Destructor
        virtual ~NewtonMassMatrix() {}

    protected:
        // methods and members

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Methods and Members

    protected:
        // Methods and Members

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Clear this MassMatrix
        virtual void clear()
        {
            this->mass = this->iX = this->iY = this->iZ = 0.0f;
        }

    public:
        //! Get the Mass
        virtual const dFloat getMass() const { return this->mass; }
        //! Set the Mass
        virtual void setMass(dFloat mass) { this->mass = mass; }
        //! Get the moment of inertia on the x axis
        virtual const dFloat getIX() const { return iX; }
        //! Set the moment of inertia on the x axis
        virtual void setIX(dFloat iX) { this->iX = iX; }
        //! Get the moment of inertia on the y axis
        virtual const dFloat getIY() const { return iY; }
        //! Set the moment of inertia on the y axis
        virtual void setIY(dFloat iY) { this->iY = iY; }
        //! Get the moment of inertia on the z axis
        virtual const dFloat getIZ() { return iZ; }
        //! Set the moment of inertia on the z axis
        virtual void setIZ(dFloat iZ) { this->iZ = iZ; }

    public:
        //! Calculate the moment of inertia for a solid box shape
        virtual void makeBoxSolid(dFloat mass, dFloat sizeX, dFloat sizeY, dFloat sizeZ)
        {
			this->mass = mass;
			this->iX = (mass * ((sizeY * sizeY) + (sizeZ * sizeZ))) / 12.0f;
			this->iY = (mass * ((sizeX * sizeX) + (sizeZ * sizeZ))) / 12.0f;
			this->iZ = (mass * ((sizeY * sizeY) + (sizeX * sizeX))) / 12.0f;
        }
        //! Calculate the moment of inertia for a hollow box shape
        virtual void makeBoxHollow(dFloat mass, dFloat sizeX, dFloat sizeY, dFloat sizeZ)
        {
			// TODO: Implement Me
			this->mass = mass;
			this->iX = 0.0f;
			this->iY = 0.0f;
			this->iZ = 0.0f;
        }
        //! Calculate the moment of inertia for a solid sphere shape
        virtual void makeSphereSolid(dFloat mass, dFloat radius)
        {
            this->mass = mass;
			this->iX = (2.0f * mass * (radius * radius)) / 5.0f;
			this->iY = (2.0f * mass * (radius * radius)) / 5.0f;
			this->iZ = (2.0f * mass * (radius * radius)) / 5.0f;
        }
        //! Calculate the moment of inertia for a Hollow sphere shape
        virtual void makeSphereHollow(dFloat mass, dFloat radius)
        {
            this->mass = mass;
			this->iX = (2.0f * mass * (radius * radius)) / 3.0f;
			this->iY = (2.0f * mass * (radius * radius)) / 3.0f;
			this->iZ = (2.0f * mass * (radius * radius)) / 3.0f;
        }
        //! Calculate the moment of inertia for a solid ellipsoid shape
        virtual void calculateMassMatrixEllipsoidSolid(dFloat mass, dFloat sizeX, dFloat sizeY, dFloat sizeZ)
        {
            this->mass = mass;
			this->iX = 0.2f * mass * ((sizeY * sizeY) + (sizeZ * sizeZ));
			this->iY = 0.2f * mass * ((sizeX * sizeX) + (sizeZ * sizeZ));
			this->iZ = 0.2f * mass * ((sizeX * sizeX) + (sizeY * sizeY));
        }
        //! Calculate the moment of inertia for a hollow ellipsoid shape
        virtual void calculateMassMatrixEllipsoidHollow(dFloat mass, dFloat sizeX, dFloat sizeY, dFloat sizeZ)
        {
			// TODO: Implement Me
			this->mass = mass;
			this->iX = 0.0f;
			this->iY = 0.0f;
			this->iZ = 0.0f;
        }
        //! Calculate the moment of inertia for a solid cone shape
        virtual void calculateMassMatrixConeSolid(dFloat mass, dFloat radius, dFloat height)
        {
            this->mass = mass;
			this->iX = (3.0f * mass * (radius * radius)) / 10.0f;
			this->iY = (mass * (12.0f * (radius * radius) + 3.0f * (height * height))) / 80.0f;
			this->iZ = (mass * (12.0f * (radius * radius) + 3.0f * (height * height))) / 80.0f;
        }
        //! Calculate the moment of inertia for a hollow cone shape
        virtual void calculateMassMatrixConeHollow(dFloat mass, dFloat radius, dFloat height)
        {
			// TODO: Implement Me
			this->mass = mass;
			this->iX = 0.0f;
			this->iY = 0.0f;
			this->iZ = 0.0f;
        }

        //! Calculate the moment of inertia for a solid Capsule
        virtual void calculateMassMatrixCapsuleSolid(dFloat mass, dFloat radius, dFloat height)
        {
			// TODO: Implement Me
			this->mass = mass;
			this->iX = 0.0f;
			this->iY = 0.0f;
			this->iZ = 0.0f;
        }
        //! Calculate the moment of inertia for a hollow Capsule
        virtual void calculateMassMatrixCapsuleHollow(dFloat mass, dFloat radius, dFloat height)
        {
			// TODO: Implement Me
			this->mass = mass;
			this->iX = 0.0f;
			this->iY = 0.0f;
			this->iZ = 0.0f;
        }
        //! Calculate the moment of inertia for a solid cylinder shape
        virtual void calculateMassMatrixCylinderSolid(dFloat mass, dFloat radius, dFloat height)
        {
			this->mass = mass;
			this->iX = (mass * ((3.0f * (radius * radius)) + (height * height))) / 12.0f;
			this->iY = (mass * ((3.0f * (radius * radius)) + (height * height))) / 12.0f;
			this->iZ = (mass * (radius * radius)) / 2.0f;
        }
        //! Calculate the moment of inertia for a hollow cylinder shape
        virtual void calculateMassMatrixCylinderHollow(dFloat mass, dFloat radius, dFloat height)
        {
			// TODO: Implement Me
			this->mass = mass;
			this->iX = 0.0f;
			this->iY = 0.0f;
			this->iZ = 0.0f;
        }
        //! Calculate the moment of inertia for a solid Chamfer Cylinder
        virtual void calculateMassMatrixChamferCylinderSolid(dFloat mass, dFloat radius, dFloat height)
        {
			// TODO: Implement Me
			this->mass = mass;
			this->iX = 0.0f;
			this->iY = 0.0f;
			this->iZ = 0.0f;
        }
        //! Calculate the moment of inertia for a hollow Chamfer Cylinder
        virtual void calculateMassMatrixChamferCylinderHollow(dFloat mass, dFloat radius, dFloat height)
        {
			// TODO: Implement Me
			this->mass = mass;
			this->iX = 0.0f;
			this->iY = 0.0f;
			this->iZ = 0.0f;
        }
        //! Calculate the moment of inertia for a convex hull
        virtual void calculateMassMatrixConvexHull(dFloat mass, NewtonCollision* pNewtonCollision)
        {
            dFloat inertia[3] = {0.0};
            dFloat origin[3] = {0.0};
            NewtonConvexCollisionCalculateInertialMatrix(pNewtonCollision, inertia, origin);
            this->mass = mass;
            this->iX = inertia[0];
            this->iY = inertia[1];
            this->iZ = inertia[2];
        }

    protected:
        dFloat mass;
        dFloat iX;
        dFloat iY;
        dFloat iZ;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState)
        {
            // TODO: implement me
        }
};

#endif // NEWTONMASSMATRIX_H
