/**
  * @file   PhysicsVehicle.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsVehicle is a wrapper for a special type of NewtonBody
  * which we can attach tires to
*/

#ifndef PHYSICSVEHICLE_H
#define PHYSICSVEHICLE_H

// LUA BIND INCLUDES
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

// C++ Includes
#include <cstddef>
// NEWTON GAME DYNAMICS INCLUDES
#include <newton.h>

// GAMEPHYSICS INCLUDES
#include "NewtonVector3.h"
#include "NewtonMatrix4.h"

// TODO: We need a vehicle control system, so that the callback has data to apply to the tires

/** @class PhysicsVehicle
  * @brief The PhysicsVehicle is a wrapper around the NewtonVehicle
  * @detail Must call setTireCallBack first so that there is a callback to handle vehicle updates **/
class PhysicsVehicle
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        PhysicsVehicle()
        {
            this->pNewtonWorld = 0;
            this->pNewtonBody = 0;
            this->pNewtonVehicle = 0;
        }
        //! Destructor
        virtual ~PhysicsVehicle() {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // methods and members

    protected:
        // methods and members

    // ****************
    // * NEWTON WORLD *
    // ****************
    public:
        //! Get World
        virtual const NewtonWorld* getNewtonWorld() const { return this->pNewtonWorld; }
        //! Set NewtonWorld
        virtual void setNewtonWorld(NewtonWorld* pNewtonWorld) { this->pNewtonWorld = pNewtonWorld; }

    protected:
        // Pointer to the Physics World
        NewtonWorld* pNewtonWorld;

    // ***************
    // * NEWTON BODY *
    // ***************
    public:
        //! Get the Newton Body
        virtual NewtonBody* getNewtonBody() { return this->pNewtonBody; }

    protected:
        // NewtonBody
        NewtonBody* pNewtonBody;

    // ******************************
    // * BUILD AND FREE THE VEHICLE *
    // ******************************
    public:
        //! Initialise the vehicle
        virtual bool build(NewtonVector3 upVector, NewtonBody* pNewtonBody)
        {
            if (this->pNewtonWorld == 0)
                return false;
            if (pNewtonBody == 0)
                return false;
            // Create the vehicle
            this->pNewtonVehicle = NewtonConstraintCreateVehicle(this->pNewtonWorld, upVector.getPointer(), pNewtonBody);
            // Keep a local reference to the NewtonBody
            this->pNewtonBody = pNewtonBody;
            // Success
            return true;
        }
        //! Get the Vehicle Joint
        virtual NewtonJoint* getVehicleJoint()
        {
            return this->pNewtonVehicle;
        }
        //! Reset the vehicle (Reset all tires velocities to zero)
        virtual void reset()
        {
            // If the vehicle is null then return
            if (this->pNewtonVehicle == 0)
                return;
            // Reset the vehicle
            NewtonVehicleReset(this->pNewtonVehicle);
        }
        //! Free the vehicle
        virtual void free()
        {
            // If the vehicle is null then return
            if (this->pNewtonVehicle == 0 || this->pNewtonWorld == 0)
                return;
            // Destroy the vehicle joint
            NewtonDestroyJoint(this->pNewtonWorld, this->pNewtonVehicle);
            // Clear local reference to the NewtonBody
            this->pNewtonBody = 0;
        }
        //! Add a tire to the vehicle
        virtual void* addTire(NewtonMatrix4 localMatrix, NewtonVector3 pin, dFloat mass, dFloat width, dFloat radius, dFloat suspensionShock, dFloat suspensionSpring, dFloat suspesionLength)
        {
            // Validate incoming parameters
            if (this->pNewtonWorld == 0 || this->pNewtonBody == 0 || this->pNewtonVehicle == 0)
                return 0;
            // Normalise the pin
            pin.normalise();
            /* Return (TODO: unknown return value, not documented, TireID???) TODO: Also collisionID needs to be set to a vehicle type)
                the tire user information should probably be a PhysicsVehicleTire
                we probably need a list of tires and a new/delete to create new tires */
            return NewtonVehicleAddTire(this->pNewtonVehicle, localMatrix.getPointer(), pin.getPointer(), mass, width, radius, suspensionShock, suspensionSpring, suspesionLength, this, 0);
        }
        //! Remove a tire from the vehicle
        virtual void removeTire(void* tireID)
        {
            // Validate incoming parameters
            if (this->pNewtonWorld == 0 || this->pNewtonBody == 0 || this->pNewtonVehicle == 0 || tireID == 0)
                return;
            // Remove the Tire corresponding with TireID
            NewtonVehicleRemoveTire(this->pNewtonVehicle, tireID);
        }
        //! Get First tire
        virtual void* getFirstTire()
        {
            // Validate incoming parameters
            if (this->pNewtonWorld == 0 || this->pNewtonBody == 0 || this->pNewtonVehicle == 0)
                return 0;
            // Get the first tire
            return NewtonVehicleGetFirstTireID(this->pNewtonVehicle);
        }
        //! Get Next tire
        virtual void* getNextTire(void* tireID)
        {
            // Validate incoming parameters
            if (this->pNewtonWorld == 0 || this->pNewtonBody == 0 || this->pNewtonVehicle == 0)
                return 0;
            // Get the next tire
            return NewtonVehicleGetNextTireID(this->pNewtonVehicle, tireID);
        }
        //! Get Tire User Data
        virtual void* getTireUserData(void* tireID)
        {
            // Validate incoming parameters
            if (this->pNewtonWorld == 0 || this->pNewtonBody == 0 || this->pNewtonVehicle == 0 || tireID == 0)
                return 0;
            // Get the tire UserData
            return NewtonVehicleGetTireUserData(this->pNewtonVehicle, tireID);
        }
        //! Get Tire Matrix
        virtual NewtonMatrix4 getTireMatrix(void* tireID)
        {
            // A container to hold the tire matrix
            NewtonMatrix4 matrix;
            // Get the tire matrix
            NewtonVehicleGetTireMatrix(this->pNewtonVehicle, tireID, matrix.getPointer());
            // Return the tire matrix
            return matrix;
        }

    protected:
        // NewtonVehicle Joint
        NewtonJoint* pNewtonVehicle;

    // *************
    // * CALLBACKS *
    // *************
    public:
        //! Get the Tire CallBack
        virtual NewtonVehicleTireUpdate getTireCallBack() { return this->pTireCallBack; }
        //! Set the Tire CallBack
        virtual void setTireCallBack(NewtonVehicleTireUpdate pCallBack) { this->pTireCallBack = pCallBack; }

    protected:
        // Local Reference to the TireCallBack
        NewtonVehicleTireUpdate pTireCallBack;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState);
};

#endif // PHYSICSVEHICLE_H
