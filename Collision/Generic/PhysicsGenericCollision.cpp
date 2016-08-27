#include "PhysicsGenericCollision.h"

//int PhysicsGenericCollision::collide(PhysicsCollisionFrame* pPhysicsCollisionFrame1, PhysicsCollisionFrame* pPhysicsCollisionFrame2, int maxContacts, std::vector<PhysicsCollisionFrameCollide>& collisionData)
//{
//    // If there is no collision frame in this class or the incoming class then return 0 contact points
//    if (pPhysicsCollisionFrame1 == 0 || pPhysicsCollisionFrame2 == 0)
//        return 0;
//    // Clear any exiting information in the collisionDataVector
//    collisionData.clear();
//    // Create arrays to hold information about the collision
//    dFloat contacts[maxContacts * 3];
//    dFloat normals[maxContacts * 3];
//    dFloat penetration[maxContacts];
//    // Collide this CollisionFrame with the incoming CollisionFrame
//    int totalContacts = NewtonCollisionCollide(this->pNewtonWorld, maxContacts,
//                                               pPhysicsCollisionFrame1->getNewtonCollision(), pPhysicsCollisionFrame1->getNewtonCollisionMatrix()->getPointer(),
//                                               pPhysicsCollisionFrame2->getNewtonCollision(), pPhysicsCollisionFrame2->getNewtonCollisionMatrix()->getPointer(),
//                                               &contacts[0], &normals[0], &penetration[0]);
//    // If the total contacts greater than 0 then a collision happened so populate the collisionData vector with information
//    if (totalContacts > 0)
//    {
//        // Go through the collision data one element at a time
//        for(int i = 0; i < totalContacts; i++)
//        {
//            // Create the data which will contain a single point of collision
//            PhysicsCollisionFrameCollide data;
//            // Build the CollisionData
//            data.setPosition(contacts[0] * NewtonToRenderScale, contacts[1] * NewtonToRenderScale, contacts[2] * NewtonToRenderScale);
//            data.setNormal(normals[0], normals[1], normals[2]);
//            data.setPenetration(penetration[0] * NewtonToRenderScale);
//            // Save the collision data to the vector
//            collisionData.push_back(data);
//        }
//    }
//    // Return the total number of contacts
//    return totalContacts;
//}
//
//bool PhysicsGenericCollision::rayCast(PhysicsCollisionFrame* pPhysicsCollisionFrame, float x0, float y0, float z0, float x1, float y1, float z1, PhysicsCollisionFrameRayImpactData& rayCastData)
//{
//    // If there is no collision frame then return false
//    if (pPhysicsCollisionFrame == 0)
//        return false;
//    // Starting point of the ray (in local space)
//    NewtonVector3 startPoint(x0 * RenderScaleToNewton, y0 * RenderScaleToNewton, z0 * RenderScaleToNewton);
//    // Ending point of the ray (in local space)
//    NewtonVector3 endPoint(x1 * RenderScaleToNewton, y1 * RenderScaleToNewton, z1 * RenderScaleToNewton);
//    // Point of Collision
//    NewtonVector3 hitPoint(0.0f, 0.0f, 0.0f);
//    // Normal at point of Collision
//    NewtonVector3 normal(0.0f, 0.0f, 0.0f);
//    // Index of the polygon struct by the ray
//    int attribute;
//    /* Cast a ray through the CollisionFrame
//        The intersection is in the range 0.0f - 1.0f. The parametric equations for the ray are as follows:
//        x' = x0 + ((x1 - x0) / sqrt((x1 - x0) *(x1 - x0) + (y1 - y0) * (y1 - y0) + (z1 - z0))) * t;
//        y' = y0 + ((y1 - y0) / sqrt((x1 - x0) *(x1 - x0) + (y1 - y0) * (y1 - y0) + (z1 - z0))) * t;
//        z' = z0 + ((z1 - z0) / sqrt((x1 - x0) *(x1 - x0) + (y1 - y0) * (y1 - y0) + (z1 - z0))) * t;
//        t - is interpolated from 0.0f to 1.0f and the line will travel from the point (x0, y0, z0) to (x1, y1, z1)
//        x0 - is the starting x position of the ray
//        y0 - is the starting y position of the ray
//        z0 - is the starting z position of the ray
//        x1 - is the starting x position of the ray
//        y1 - is the starting y position of the ray
//        z1 - is the starting z position of the ray
//        The terms contained inside the squareroot calculate the length of the ray (x0, y0, z0) - (x1, y1, z1)
//        When an intersection between that line and geometry happens, the ray will return t. If t is outside the
//        range of 0.0f - 1.0f then the ray didn't hit the collision frame
//        */
//    float t = NewtonCollisionRayCast(pPhysicsCollisionFrame->getNewtonCollision(), startPoint.getPointer(), endPoint.getPointer(), normal.getPointer(), &attribute);
//    if (t >= 0.0f && t <= 1.0f)
//    {
//        NewtonVector3 position;
//        position.setX(x0 + ((x1 - x0) / sqrt((x1 - x0) *(x1 - x0) + (y1 - y0) * (y1 - y0) + (z1 - z0))) * t * NewtonToRenderScale);
//        position.setY(y0 + ((y1 - y0) / sqrt((x1 - x0) *(x1 - x0) + (y1 - y0) * (y1 - y0) + (z1 - z0))) * t * NewtonToRenderScale);
//        position.setZ(z0 + ((z1 - z0) / sqrt((x1 - x0) *(x1 - x0) + (y1 - y0) * (y1 - y0) + (z1 - z0))) * t * NewtonToRenderScale);
//        rayCastData.setPosition(position);
//        rayCastData.setNormal(normal);
//        rayCastData.setFaceIndex(attribute);
//        // Ray Hit
//        return true;
//    }
//    // No Ray Hit
//    return false;
//}
//
//bool PhysicsGenericCollision::closestPointQuery(PhysicsCollisionFrame* pPhysicsCollisionFrame1, PhysicsCollisionFrame* pPhysicsCollisionFrame2, PhysicsCollisionFrameClosestPoints* closestPointsData)
//{
//    // If there is no collision frame then return false
//    if (pPhysicsCollisionFrame1 == 0 || pPhysicsCollisionFrame2 == 0)
//        return false;
//    // TODO: Convert these between render scale and newton scale
//    return NewtonCollisionClosestPoint(this->pNewtonWorld,
//                                        pPhysicsCollisionFrame1->getNewtonCollision(), pPhysicsCollisionFrame1->getNewtonCollisionMatrix()->getPointer(),
//                                        pPhysicsCollisionFrame2->getNewtonCollision(), pPhysicsCollisionFrame2->getNewtonCollisionMatrix()->getPointer(),
//                                        closestPointsData->getClosestPointToThisObject().getPointer(),
//                                        closestPointsData->getClosestPointToTheOtherObject().getPointer(),
//                                        closestPointsData->getSeperationVector().getPointer());
//}
//
//bool PhysicsGenericCollision::closestPointQuery(PhysicsCollisionFrame* pPhysicsCollisionFrame, float x, float y, float z, PhysicsCollisionFrameClosestPoint* closestPointData)
//{
//    if (pPhysicsCollisionFrame == 0)
//        return false;
//    NewtonVector3 testPoint(x, y, z);
//    // TODO: Convert these between render scale and newton scale
//    return NewtonCollisionPointDistance(this->pNewtonWorld,
//                                 testPoint.getPointer(),
//                                 pPhysicsCollisionFrame->getNewtonCollision(),
//                                 pPhysicsCollisionFrame->getNewtonCollisionMatrix()->getPointer(),
//                                 closestPointData->getClosestPoint().getPointer(),
//                                 closestPointData->getSeperationVector().getPointer());
//}
//
//float PhysicsGenericCollision::collideContinue(int maxContacts, float timeStep, PhysicsCollisionFrame* pPhysicsCollisionFrame, PhysicsCollisionFrameClosestPoint* closestPointData)
//{
//    /* TODO: Implement me NewtonCollisionCollideContinue
//                this requires a very large data structure
//                some of these functions make be better off in a
//                new class so that they act upon Collision frames
//                rather than relating one to the other. Guess what I mean is
//                a new interface that would favor recursion.
//                for(ColisionBody p in ColisionBodies)
//                {
//                    if (collideContinue(frame1, frame2, std::vector<data>) == true)
//                    {
//                        process collisions
//                    }
//                }
//                I feel that implementing this function here is a poor design choice
//                    */
//    return 0.0f;
//}
//
