/**
  * @file   PhysicsCollisionFrame.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  E_PHYSICS_COLLISIONFRAME_TYPE is an enumeration
  * which describes the type of collision frame
**/

#ifndef PHYSICSCOLLISIONFRAMETYPES_H
#define PHYSICSCOLLISIONFRAMETYPES_H

/**
  * @brief An enumeration to hold all the different types of NewtonBodies
  * the numbers here for each member must match those in BodyTypes
  **/
enum E_PHYSICS_COLLISIONFRAME_TYPE
{
    PCFT_NOT_SET, /** No Collision Frame **/
    PCFT_NULL, /** Null Type Collision Frame (this is a collision frame just no polygons) **/
    PCFT_BOX, /** Box Type Collision Frame **/
    PCFT_SPHERE,/** Sphere Type Collision Frame **/
    PCFT_CONE, /** Cone Type Collision Frame **/
    PCFT_CAPSULE,/** Capsule Type Collision Frame **/
    PCFT_CYLINDER, /** Cylinder Type Collision Frame **/
    PCFT_CHAMPHER_CYLINDER, /** Champher Cylinder Type Collision Frame would appear as a torus with the ends capped at the highest points **/
    PCFT_CONVEX_HULL, /** ConvexHull Type Collision Frame is a type that would appear like plastic wrap stretched over the 3d model **/
    PCFT_COMPOUND, /** Compound Type Collision Frame is composed of a composite of Collision Frames **/
    PCFT_TREE,   /** Tree Type Collision Frame (not a literal tree rather a fixed collection of polygons) **/
    PCFT_VEHICLE /** Vehicle Type Collision Frame **/
};

#endif // PHYSICSCOLLISIONFRAMETYPES_H
