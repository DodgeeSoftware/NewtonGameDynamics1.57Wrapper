/**
  * @file   GamePhysics.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  GamePhysics is the main header that incorporates the functionality
  * of the NewtonGameDynamics Wrapper
*/

/** @mainpage GamePhysics (NewtonGameDynamicsWrapper)
  *
  * @section intro_sec Introduction
  *
  * The GamePhysics NewtonGameDynamicsWrapper is an easy to use c++ wrapper
  * around core features of NewtonGameDynamics. Be sure to place your callbacks
  * as static in your Game class and route traffic to a specifical class using the
  * pUserData pointers to a local callback specific to the class. The wrapper comes
  * in several parts and is principally a c++ wrappup of the library. I have included
  * a visual debugger for the Irrlicht Rendering engine as a sample along with a
  * PhysicsBodyScene Node from Irrlicht so that you get an idea how to integrate this
  * in your framework (which will be no easy task)
  *
  * The PhysicsWorld class is a wrapper around the NewtonWorld and that is the place where
  * all the joints, vehicles, ragdolls and physics bodies exist. It is where we set gravity,
  * buoyancy planes, interpolate to the next frame and set the world size. The PhysicsVehicle
  * and PhysicsVehicleTire classes are wrappers around Newton Objects for tires and vehicles.
  * If you wish to use those create a Custom VehicleSceneNode and use either an inheritance or
  * composition make up for that class. Be sure to put your vehicle callbacks in your game class
  * and route callback traffice to a specific instance of your vehicle
  *
  * Th Utilities folder contains a number of helper classes that this wrapper uses to simply
  * our our dealings with newton. Small things like mathematical vectors, matrices and mass matrices.
  * Most importantly the NewtonGlobalScale which you need to setup if your physics scale is differnt to
  * your renderscale.
  *
  * The Triggers folder contrains enough easy to use information to quickly implement your own area triggers.
  * I use the 'genertic' collision system in NewtonGameDynamics to implement triggers, this avoids any
  * physics being applied to the player or trigger and simply focuses on contact information.
  *
  * The Rays Folder contains all the classs related to firing rays through the physics world, after you make th
  * physicsworld and put in some geometry you should be able to get combinations of all impacts the furthest impact
  * or the closes impact by firing the ray and examining inpact data.
  *
  * @section install_sec Installation
  *
  * @subsection step1 Step 1: Dependencies
  * This project is dependant on NewtonGameDynamics 1.53 (I am aware this version is old but I have had no need
  * to  upgrade or write a new wrapper in all this time
  * http://newtondynamics.com/forum/newton.php
  *
  * @subsection step2 Step 2: Search Paths
  * You will need to add search paths to the folders where the headers and implementation files are
  * to your project. Paths such as "GamePhysics" "GamePhysics\World" "GamePhysics\Body" etc because
  * I don't prefix includes in this library with the locations of these headers (this may be changed later)
  *
  * @subsection step3 Step 3: Use
  * You need to make custom scenenodes. In the same way you would make custom scenenodes for sound emitting nodes
  * you would do the same for those that have collision frames too. This also applies to ragdolls, vehicles, tires and joints.
  * there is so very much to cover in how to use Newton Game Dynamics. When you set up a player object you need
  * to set friction between your player material and your level material to 0 but max out the linear damping, that way
  * your player will not slide away, you need to make sure you turnon the collision between the materials too. You need
  * so set any object you want to move with a mass above 0, otherwise NewtonGameDyamics assumes its a stable static object
  * and it will be unmoveable. To facilitate creation of masses and mass matrix I provde a MassMatrix Class. To facilitate
  * the creation of materials I provide a Physics material manager. To faciliate the creation of PhysicsBodies I provide a
  * body factory. To faciliate the creation of physicscollisionframes I provide a physicscollisionsframefactory. These creator
  * classes should all exist at your game class scope along with your debugger.
  *
  * @section Credits Credits
  * Wrapper was developed by Sergeant Neipo of Dodgee Software 2016
  * Project is release under GPLv3
  **/

#ifndef GAMEPHYSICS_H
#define GAMEPHYSICS_H

#include "Body/PhysicsBody.h"
#include "Body/PhysicsBodyTypes.h"
#include "Buoyancy/PhysicsBuoyancyPlane.h"
#include "Collision/Frames/PhysicsCollisionFrame.h"
#include "Collision/Generic/PhysicsCollisionFrameClosestPoint.h"
#include "Collision/Generic/PhysicsCollisionFrameCollide.h"
#include "Collision/Factory/PhysicsCollisionFrameFactory.h"
#include "Collision/Rays/PhysicsCollisionFrameRayImpactData.h"
#include "Collision/Frames/PhysicsCollisionFrameTypes.h"
#include "Collision/Generic/PhysicsGenericCollision.h"
#include "Debugger/IPhysicsDebugger.h"
#include "Joints/IPhysicsJoint.h"
#include "Joints/PhysicsBallAndSocketJoint.h"
#include "Joints/PhysicsCorkscrewJoint.h"
#include "Joints/PhysicsCustomJoint.h"
#include "Joints/PhysicsHingeJoint.h"
#include "Joints/PhysicsSliderJoint.h"
#include "Joints/PhysicsUniversalJoint.h"
#include "Joints/PhysicsUpVectorJoint.h"
#include "Joints/Factory/PhysicsJointFactory.h"
#include "Materials/PhysicsMaterial.h"
#include "Materials/Factory/PhysicsMaterialFactory.h"
#include "Rays/IPhysicsRay.h"
#include "Rays/PhysicsRayClosest.h"
#include "Rays/PhysicsRayDefault.h"
#include "Rays/PhysicsRayFurthest.h"
#include "Triggers/IPhysicsTrigger.h"
#include "Utilities/NewtonAABB.h"
#include "Utilities/NewtonFreezeThreshold.h"
#include "Utilities/NewtonMassMatrix.h"
#include "Utilities/NewtonMatrix4.h"
#include "Utilities/NewtonVector3.h"
#include "Vehicle/IPhysicsVehicle.h"
#include "Vehicle/PhysicsVehicle.h"
#include "Vehicle/PhysicsVehicleTire.h"
#include "World/PhysicsWorld.h"

#endif // GAMEPHYSICS_H
