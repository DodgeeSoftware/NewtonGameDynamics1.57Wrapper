/**
  * @file   PhysicsBuoyancyPlane.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsBuoyancyPlane is a simple class
  * that defines the characteristics of a buoyancy plane
  * and is used by the physics world and associated callbacks
  * to implement a plane of water in your physics world which
  * physics bodies may interact with
**/

#ifndef PHYSICSBUOYANCYPLANE_H
#define PHYSICSBUOYANCYPLANE_H

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

// NEWTON WRAPPER
#include "NewtonVector3.h"

/** @class PhysicsBuoyancyPlane
  * @brief The PhysicsBuoyancyPlane is a container for a Buoyancy Plane
  * @detail A PhysicsBuoyancyPlane is used by the PhysicsWorld to create an infinite water plan **/
class PhysicsBuoyancyPlane
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        PhysicsBuoyancyPlane()
        {
            this->plane[0] = 0.0;
            this->plane[1] = 1.0;
            this->plane[2] = 0.0;
            this->plane[3] = 0.0;
            this->fluidDensity = 0.5; // TODO: We need to know what default values to use here
            this->fluidLinearViscosity = 0.5; // TODO: We need to know what default values to use here
            this->fluidAngularViscosity = 0.5; // TODO: We need to know what default values to use here
        }
        //! Destructor
        virtual ~PhysicsBuoyancyPlane() {}

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Get Normal
        NewtonVector3 getNormal() { return NewtonVector3(plane[0], plane[1], plane[2]); }
        //! Set Normal
        void setNormal(dFloat x, dFloat y, dFloat z)
        {
            // Find the length of the normal
            float length = sqrt(x * x + y * y + z * z);
            // Normal Cannot have a length of 0
            if (length == 0)
                return;
            // Set and Normalise the normal (make it a unit vector i.e. length of one)
            this->plane[0] = (x / length);
            this->plane[1] = (y / length);
            this->plane[2] = (z / length);
        }
        //! Set Normal
        void setNormal(NewtonVector3 normal)
        {
            // Normalise the incoming normal (make it a unit vector of length 1)
            normal.normalise();
            // Set the Plane
            this->plane[0] = normal.getX(); this->plane[1] = normal.getY(); this->plane[2] = normal.getZ();
        }
        //! Get the Distance of the plane from the origin
        float getDistanceFromOrigin() { return this->plane[4]; }
        //! Set Distance from Origin
        void setDistanceFromOrigin(dFloat distance) { this->plane[4] = distance; } // TODO: Do I have to scale this to the render scale?
        //! Get a Pointer to the Plane
        dFloat* getPointer() { return &(this->plane[0]); }
        //! Get Fluid Density
        dFloat getFluidDensity() { return this->fluidDensity; }
        //! Set Fluid Density
        void setFluidDensity(dFloat value) { this->fluidDensity = value; }
        //! Get Fluid Linear Viscosity
        dFloat getFluidLinearViscosity() { return this->fluidLinearViscosity; }
        //! Set Fluid Linear Viscosity
        void setFluidLinearViscosity(dFloat value) { this->fluidLinearViscosity = value; }
        //! Get Fluid Angular Viscosity
        dFloat getFluidAngularViscosity() { return this->fluidAngularViscosity; }
        //! Set Fluid Angular Viscosity
        void setFluidAngularViscosity(dFloat value) { this->fluidAngularViscosity = value; }

    protected:
        //! Array for the buoyance plane [0][1][2] are x, y,z for the plane normal and [4] is the distance along that normal to the origin
        dFloat plane[4];
        dFloat fluidDensity;
        dFloat fluidLinearViscosity;
        dFloat fluidAngularViscosity;

    // ************
    // * BINDINGS *
    // ************
    public:
        //! Bind this class to a luaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // PHYSICSBUOYANCYPLANE_H
