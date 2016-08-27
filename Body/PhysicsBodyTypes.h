/**
  * @file   PhysicsBodyTypes.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  PhysicsBodyTypes is a small enumeration
  * which we allocate to a PhysicsBody on creation so
  * that we can know what type it is. This is important
  * because there are some special functions that
  * will only work on certain physics bodies and this
  * wrapper provides one common class interface for
  * physicsbodies
**/

#ifndef PHYSICS_BODY_TYPES_H
#define PHYSICS_BODY_TYPES_H

/**
  * @brief An enumeration to hold all the different types of NewtonBodies
  * the numbers here for each member must match those in CollisionFrameTypes
  **/
enum E_PHYSICS_BODY_TYPE
{
    PBT_NOT_SET,          /** No Physics Body **/
    PBT_NULL,             /** Null Physics Body (this is a body it just has no polygons) **/
    PBT_BOX,              /** A Box Physics Body **/
    PBT_SPHERE,           /** A Sphere Physics Body **/
    PBT_CONE,             /** A Cone Physics Body **/
    PBT_CAPSULE,          /** A Capsule Physics Body **/
    PBT_CYLINDER,         /** A Cylinder Physics Body **/
    PBT_CHAMPHER_CYLINDER, /** A Champher Cylinder Physics Body (think a torus that is capped on the top and bottom at the highest points
                             * so that there is a flat surface **/
    PBT_CONVEX_HULL,       /** A convex hull is the same as if you took a 3d object and folded plastic wrap around it,
                             * stretching it over every concave surface so that the plastic is flat and wrapping it tighly
                             * over covex areas. It forms a shell that has a larger volume but small surface area of polygons
                             * to collide and makes physics more efficient to compute **/
    PBT_COMPOUND,          /** Compound Convex Hull Type Body (means multiple convex hulls bound together into one object) **/
    PBT_TREE,              /** Tree Type Body (not an actual tree, a collection of polys) **/
    PBT_VEHICLE            /** Vehicle Type Body **/
};

#endif
