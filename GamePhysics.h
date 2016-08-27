/**
  * @file   GamePhysics.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  GamePhysics is the main header that incorporates the functionality
  * of the NewtonGameDynamics Wrapper
*/

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
