#include "PhysicsDebugger.h"

void PhysicsDebugger::drawWorldBoundaries()
{
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    // If the world boundaries aren't visible then return
    if (this->visibleWorldBoundaries == false)
        return;
    irr::scene::ICameraSceneNode* pCamera = pIrrlichtDevice->getSceneManager()->getActiveCamera();
    if (pCamera == 0)
        return;
    // Density of world boundary grid
    float density = 500;
    // Grab the Physics world from the Newton World
    PhysicsWorld* pPhysicsWorld = (PhysicsWorld*) NewtonWorldGetUserData(this->pNewtonWorld);
    // get the size of the physics world
    NewtonAABB worldSize = pPhysicsWorld->getWorldSize();
    // Cache the current camera matrix and the current world matrix
    irr::core::matrix4 previous_camera = pCamera->getViewMatrix();
    irr::core::matrix4 previous_world = pIrrlichtDevice->getVideoDriver()->getTransform(irr::video::ETS_WORLD);
    // Build a view matrix so that lines are drawn correctly
    irr::core::matrix4 mat;
    mat.setScale(irr::core::vector3df(NewtonToRenderScale, NewtonToRenderScale, NewtonToRenderScale));
    mat.setRotationDegrees(pCamera->getViewMatrix().getRotationDegrees());
    mat.setTranslation(pCamera->getViewMatrix().getTranslation());
    // Set the world view projection matrix
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
    // Set the Material
    pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
    // draw top and bottom lines parallel to the z-axis
    //for(float u = worldSize.getMinEdgeX(); u <= worldSize.getMaxEdgeX(); u+=((worldSize.getMaxEdgeX()-worldSize.getMinEdgeX()) / 25))
    for(float u = worldSize.getMinEdgeX(); u <= worldSize.getMaxEdgeX(); u += density)
    {
        irr::core::vector3df start;
        irr::core::vector3df end;

        start = irr::core::vector3df(u, worldSize.getMinEdgeY(), worldSize.getMinEdgeZ());
        end = irr::core::vector3df(u, worldSize.getMinEdgeY(), worldSize.getMaxEdgeZ());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
        pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
        pIrrlichtDevice->getVideoDriver()->draw3DLine(start,end, irr::video::SColor(255, 128, 128, 128));

        start = irr::core::vector3df(u, worldSize.getMaxEdgeY(), worldSize.getMinEdgeZ());
        end = irr::core::vector3df(u, worldSize.getMaxEdgeY(), worldSize.getMaxEdgeZ());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
        pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
        pIrrlichtDevice->getVideoDriver()->draw3DLine(start,end, irr::video::SColor(255, 128, 128, 128));
    }
    // draw top and bottom lines parallel to the x-axis
    //for(float u = worldSize.getMinEdgeZ(); u <= worldSize.getMaxEdgeZ(); u+=((worldSize.getMaxEdgeZ()-worldSize.getMinEdgeZ()) / 25))
    for(float u = worldSize.getMinEdgeZ(); u <= worldSize.getMaxEdgeZ(); u += density)
    {
        irr::core::vector3df start;
        irr::core::vector3df end;

        start = irr::core::vector3df(worldSize.getMinEdgeX(), worldSize.getMinEdgeY(), u);
        end = irr::core::vector3df(worldSize.getMaxEdgeX(), worldSize.getMinEdgeY(), u);
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
        pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
        pIrrlichtDevice->getVideoDriver()->draw3DLine(start,end, irr::video::SColor(255, 128, 128, 128));

        start = irr::core::vector3df(worldSize.getMinEdgeX(), worldSize.getMaxEdgeY(), u);
        end = irr::core::vector3df(worldSize.getMaxEdgeX(), worldSize.getMaxEdgeY(), u);
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
        pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
        pIrrlichtDevice->getVideoDriver()->draw3DLine(start,end, irr::video::SColor(255, 128, 128, 128));
    }
    // draw left and right lines parallel to the z-axis
    //for(float u = worldSize.getMinEdgeY(); u <= worldSize.getMaxEdgeY(); u+=((worldSize.getMaxEdgeY()-worldSize.getMinEdgeY()) / 25))
    for(float u = worldSize.getMinEdgeY(); u <= worldSize.getMaxEdgeY(); u += density)
    {
        irr::core::vector3df start;
        irr::core::vector3df end;

        start = irr::core::vector3df(worldSize.getMinEdgeX(), u, worldSize.getMinEdgeZ());
        end = irr::core::vector3df(worldSize.getMinEdgeX(),u, worldSize.getMaxEdgeZ());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
        pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
        pIrrlichtDevice->getVideoDriver()->draw3DLine(start,end, irr::video::SColor(255, 128, 128, 128));

        start = irr::core::vector3df(worldSize.getMaxEdgeX(), u, worldSize.getMinEdgeZ());
        end = irr::core::vector3df(worldSize.getMaxEdgeX(), u, worldSize.getMaxEdgeZ());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
        pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
        pIrrlichtDevice->getVideoDriver()->draw3DLine(start,end, irr::video::SColor(255, 128, 128, 128));
    }
    // draw left and right lines parallel to the y-axis
    //for(float u = worldSize.getMinEdgeZ(); u <= worldSize.getMaxEdgeZ(); u+=((worldSize.getMaxEdgeZ()-worldSize.getMinEdgeZ()) / 25))
    for(float u = worldSize.getMinEdgeZ(); u <= worldSize.getMaxEdgeZ(); u += density)
    {
        irr::core::vector3df start;
        irr::core::vector3df end;

        start = irr::core::vector3df(worldSize.getMinEdgeX(), worldSize.getMinEdgeY(), u);
        end = irr::core::vector3df(worldSize.getMinEdgeX(), worldSize.getMaxEdgeY(), u);
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
        pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
        pIrrlichtDevice->getVideoDriver()->draw3DLine(start,end, irr::video::SColor(255, 128, 128, 128));

        start = irr::core::vector3df(worldSize.getMaxEdgeX(), worldSize.getMinEdgeY(), u);
        end = irr::core::vector3df(worldSize.getMaxEdgeX(), worldSize.getMaxEdgeY(), u);
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
        pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
        pIrrlichtDevice->getVideoDriver()->draw3DLine(start,end, irr::video::SColor(255, 128, 128, 128));
    }
    // draw front and back lines parallel to the y-axis
    //for(float u = worldSize.getMinEdgeX(); u <= worldSize.getMaxEdgeX(); u+=((worldSize.getMaxEdgeX()-worldSize.getMinEdgeX()) / 25))
    for(float u = worldSize.getMinEdgeX(); u <= worldSize.getMaxEdgeX(); u += density)
    {
        irr::core::vector3df start;
        irr::core::vector3df end;

        start = irr::core::vector3df(u, worldSize.getMinEdgeY(), worldSize.getMinEdgeZ());
        end = irr::core::vector3df(u, worldSize.getMaxEdgeY(), worldSize.getMinEdgeZ());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
        pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
        pIrrlichtDevice->getVideoDriver()->draw3DLine(start,end, irr::video::SColor(255, 128, 128, 128));

        start = irr::core::vector3df(u, worldSize.getMinEdgeY(), worldSize.getMaxEdgeZ());
        end = irr::core::vector3df(u, worldSize.getMaxEdgeY(), worldSize.getMaxEdgeZ());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
        pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
        pIrrlichtDevice->getVideoDriver()->draw3DLine(start,end, irr::video::SColor(255, 128, 128, 128));
    }
    // draw left and right lines parallel to the z-axis
    //for(float u = worldSize.getMinEdgeY(); u <= worldSize.getMaxEdgeY(); u+=((worldSize.getMaxEdgeY()-worldSize.getMinEdgeY()) / 25))
    for(float u = worldSize.getMinEdgeY(); u <= worldSize.getMaxEdgeY(); u += density)
    {
        irr::core::vector3df start;
        irr::core::vector3df end;

        start = irr::core::vector3df(worldSize.getMinEdgeX(), u, worldSize.getMinEdgeZ());
        end = irr::core::vector3df(worldSize.getMaxEdgeX(),u, worldSize.getMinEdgeZ());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
        pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
        pIrrlichtDevice->getVideoDriver()->draw3DLine(start,end, irr::video::SColor(255, 128, 128, 128));

        start = irr::core::vector3df(worldSize.getMinEdgeX(), u, worldSize.getMaxEdgeZ());
        end = irr::core::vector3df(worldSize.getMaxEdgeX(),u, worldSize.getMaxEdgeZ());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
        pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
        pIrrlichtDevice->getVideoDriver()->draw3DLine(start,end, irr::video::SColor(255, 128, 128, 128));
    }

    // restore the veiw matrix and the world matrix
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, previous_camera);
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, previous_world);
}

void PhysicsDebugger::drawBodies()
{
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    // Process Every NewtonBody in the Physics World
    NewtonWorldForEachBodyDo(this->pNewtonWorld, this->pForEachBodyCallBack);
}

void PhysicsDebugger::drawRays()
{
    //std::cout << "drawRays" << std::endl;
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    irr::scene::ICameraSceneNode* pCamera = pIrrlichtDevice->getSceneManager()->getActiveCamera();
    if (pCamera == 0)
        return;
    // Cache the current camera matrix and the current world matrix
    irr::core::matrix4 previous_camera = pCamera->getViewMatrix();
    irr::core::matrix4 previous_world = pIrrlichtDevice->getVideoDriver()->getTransform(irr::video::ETS_WORLD);
    // Build a view matrix so that lines are drawn correctly
    irr::core::matrix4 mat;
    mat.setTranslation(pCamera->getViewMatrix().getTranslation() * RenderScaleToNewton);
    mat.setRotationDegrees(pCamera->getViewMatrix().getRotationDegrees());
    // Build the world view projection matrix
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
    // Set the material
    pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
    // Go through each
    for (std::vector<IPhysicsRay*>::iterator iter = this->rays.begin(); iter != this->rays.end(); iter++)
    {
        // Get the start position of the ray and transform into render scale
        irr::core::vector3df start = irr::core::vector3df((*iter)->getStart().getX(), (*iter)->getStart().getY(), (*iter)->getStart().getZ());
        // Get the end position of the ray and transform into render scale
        irr::core::vector3df end = irr::core::vector3df((*iter)->getEnd().getX(), (*iter)->getEnd().getY(), (*iter)->getEnd().getZ());
        // Set Material
        pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
        // Draw the 3d line representing the physics ray
        pIrrlichtDevice->getVideoDriver()->draw3DLine(start, end, irr::video::SColor(255, 255, 255, 255));
        // draw Ray cast information
        for (std::vector<PhysicsRayImpactData>::iterator diter = (*iter)->getImpactDataVector().begin();
        diter != (*iter)->getImpactDataVector().end(); diter++)
        {
            NewtonVector3 dstart = diter->getPosition();
            NewtonVector3 dend = diter->getPosition() + diter->getNormal() * 5.0f;
            pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
            pIrrlichtDevice->getVideoDriver()->draw3DLine(irr::core::vector3df(dstart.getX(), dstart.getY(), dstart.getZ()), irr::core::vector3df(dend.getX(), dend.getY(), dend.getZ()), irr::video::SColor(255, 255, 0, 0));
        }
    }
    // restore the veiw matrix and the world matrix
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, previous_camera);
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, previous_world);
}

void PhysicsDebugger::drawJoints()
{
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    if (this->jointsVisible == false)
        return;
    for(std::vector<IPhysicsJoint*>::iterator iter = this->joints.begin(); iter != this->joints.end(); iter++)
    {
        IPhysicsJoint* pPhysicsJoint = (*iter);
        if (pPhysicsJoint->getType() == JT_BALL_AND_SOCKET)
            this->drawBallAndSocketJoint((PhysicsBallAndSocketJoint*)pPhysicsJoint);
        if (pPhysicsJoint->getType() == JT_CORK_SCREW)
            this->drawCorkscrewJoint((PhysicsCorkscrewJoint*)pPhysicsJoint);
        if (pPhysicsJoint->getType() == JT_CUSTOM)
            this->drawCustomJoint((PhysicsCustomJoint*)pPhysicsJoint);
        if (pPhysicsJoint->getType() == JT_HINGE)
            this->drawHingeJoint((PhysicsHingeJoint*)pPhysicsJoint);
        if (pPhysicsJoint->getType() == JT_SLIDER)
            this->drawSliderJoint((PhysicsSliderJoint*)pPhysicsJoint);
        if (pPhysicsJoint->getType() == JT_UNIVERSAL)
            this->drawUniversalJoint((PhysicsUniversalJoint*)pPhysicsJoint);
        if (pPhysicsJoint->getType() == JT_UP)
            this->drawUpVectorJoint((PhysicsUpVectorJoint*)pPhysicsJoint);
    }
}

void PhysicsDebugger::drawVehicles()
{
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    // TODO: Implement me
}

void PhysicsDebugger::drawTriggers()
{
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    // Only draw if triggers are visible
    if (this->triggersVisible == false)
        return;
    // Get the VideoDriver
    irr::video::IVideoDriver* pVideoDriver = this->pIrrlichtDevice->getVideoDriver();
    for(std::vector<IPhysicsTrigger*>::iterator i = this->triggers.begin(); i != this->triggers.end(); i++)
    {
        IPhysicsTrigger* pPhysicsTrigger = *i;
        irr::scene::IMesh* pMesh = (irr::scene::IMesh*)pPhysicsTrigger->getMesh();
        if (pMesh != 0)
        {
            // Grab the Newton Matrix
            NewtonMatrix4 newtonMatrix = *(pPhysicsTrigger->getNewtonCollisionMatrix());
            // Convert the NewtonMatrix
            irr::core::matrix4 triggerTransformMatrix = Utils::convertNewtonMatrixToMatrix4(newtonMatrix);
            // Set Transform
            pVideoDriver->setTransform(irr::video::ETS_WORLD, triggerTransformMatrix);
            // Create a material for rendering the collision frame
            irr::video::SMaterial material;
            material.Lighting = false;
            material.AmbientColor = irr::video::SColor(255, 128, 128, 128);
            material.DiffuseColor = irr::video::SColor(255, 128, 128, 128);
            material.EmissiveColor = irr::video::SColor(255, 128, 128, 128);
            material.SpecularColor = irr::video::SColor(255, 128, 128, 128);
            material.BackfaceCulling = false;
            material.AntiAliasing = false;
            material.FogEnable = false;
            material.FrontfaceCulling = false;
            material.Shininess = 1.0f;
            material.Thickness = 1.0f;
            material.UseMipMaps = false;
            material.Wireframe = true;
            // Render geometry
            for (unsigned int i = 0; i < pMesh->getMeshBufferCount(); i++)
            {
                irr::scene::IMeshBuffer* pMeshBuffer = pMesh->getMeshBuffer(i);
                // Set the material
                pVideoDriver->setMaterial(material);
                // Draw the meshBuffer
                pVideoDriver->drawMeshBuffer(pMeshBuffer);
            }
            // Draw the axis aligned bounding box around the mesh
            pVideoDriver->draw3DBox(pMesh->getBoundingBox(), irr::video::SColor(255, 255, 255, 255));
        }
    }
}

void PhysicsDebugger::drawCollisionFrames()
{
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    // TODO: Implement me
}

void PhysicsDebugger::drawBuoyancyPlane()
{
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    irr::scene::ICameraSceneNode* pCamera = pIrrlichtDevice->getSceneManager()->getActiveCamera();
    if (pCamera == 0)
        return;
    // Cache the current camera matrix and the current world matrix
    irr::core::matrix4 previous_camera = pCamera->getViewMatrix();
    irr::core::matrix4 previous_world = pIrrlichtDevice->getVideoDriver()->getTransform(irr::video::ETS_WORLD);
    // Build a view matrix so that lines are drawn correctly
    irr::core::matrix4 mat;
    mat.setTranslation(pCamera->getViewMatrix().getTranslation() * RenderScaleToNewton);
    mat.setRotationDegrees(pCamera->getViewMatrix().getRotationDegrees());
    // Build the world view projection matrix
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
    // Set the material
    pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
    // Grab the Physics world from the Newton World
    PhysicsWorld* pPhysicsWorld = (PhysicsWorld*) NewtonWorldGetUserData(this->pNewtonWorld);
    // get the size of the physics world
    NewtonAABB worldSize = pPhysicsWorld->getWorldSize();
    // Go through each buoyancy plane
    for (std::vector<PhysicsBuoyancyPlane>::iterator iter = this->buoyancyPlanes.begin(); iter != this->buoyancyPlanes.end(); iter++)
    {
        PhysicsBuoyancyPlane& buoyancyPlane = (*iter);
        // TODO: Draw the Plane so that it touches the walls of World Size
        // TODO: Rotate the plane so it is positioned correctly
        NewtonVector3 normal = buoyancyPlane.getNormal();
        normal.normalise();
        //irr::core::matrix4 offset;
        //offset.makeIdentity();
        //NewtonVector2 euler = normal.getAngleRadians();

        // Set the number of divisions in the buoyancy grid
        float density = 25;
        for(float v = 0; v <= 1 + (1.0f / density); v += (1.0f / density))
        {
            irr::core::vector3df start = irr::core::vector3df(worldSize.getMinEdgeX(), 0.0f, worldSize.getMinEdgeZ() + worldSize.getMaxEdgeZ() * v * 2.0f);
            irr::core::vector3df end = irr::core::vector3df(worldSize.getMaxEdgeX(), 0.0f, worldSize.getMinEdgeZ() + worldSize.getMaxEdgeZ() * v * 2.0f);
            pIrrlichtDevice->getVideoDriver()->draw3DLine(start * RenderScaleToNewton, end * RenderScaleToNewton, this->buoyancyPlaneColour);
        }
        for(float u = 0; u <= 1 + (1.0f / density); u += (1.0f / density))
        {
            irr::core::vector3df start = irr::core::vector3df(worldSize.getMinEdgeX() + worldSize.getMaxEdgeX() * u * 2.0f, 0.0f, worldSize.getMinEdgeZ());
            irr::core::vector3df end = irr::core::vector3df(worldSize.getMinEdgeX() + worldSize.getMaxEdgeX() * u * 2.0f, 0.0f, worldSize.getMaxEdgeZ());
            pIrrlichtDevice->getVideoDriver()->draw3DLine(start * RenderScaleToNewton, end * RenderScaleToNewton, this->buoyancyPlaneColour);
        }
    }
    // restore the veiw matrix and the world matrix
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, previous_camera);
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, previous_world);
}

void PhysicsDebugger::drawBallAndSocketJoint(PhysicsBallAndSocketJoint* pPhysicsBallAndSocketJoint)
{
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    // Get the Camera
    irr::scene::ICameraSceneNode* pCamera = pIrrlichtDevice->getSceneManager()->getActiveCamera();
    // Verify the camera
    if (pCamera == 0)
        return;
    // Cache the current camera matrix and the current world matrix
    irr::core::matrix4 previous_camera = pCamera->getViewMatrix();
    irr::core::matrix4 previous_world = pIrrlichtDevice->getVideoDriver()->getTransform(irr::video::ETS_WORLD);

    // Build a view matrix so that lines are drawn correctly
    irr::core::matrix4 mat;
    mat.setTranslation(pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix().getTranslation() * RenderScaleToNewton);
    mat.setRotationDegrees(pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix().getRotationDegrees());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);

    // Make a pointer to the parent NewtonBody
    NewtonBody* pParentNewtonBody = 0;
    // Make a pointer to the child NewtonBody
    NewtonBody* pChildNewtonBody = 0;
    // Make a container for the parent body matrix
    NewtonMatrix4 parentBodyMatrix;
    // Make a container for the child body matrix
    NewtonMatrix4 childBodyMatrix;
    // Make a container for the parent position
    NewtonVector3 parentPosition;
    // Make a container for the child position
    NewtonVector3 childPosition;

    // Get the Newton Body for the Parent Joint
    pParentNewtonBody = pPhysicsBallAndSocketJoint->getParentNewtonBody();
    if (pParentNewtonBody != 0)
    {
        // Get the Parent Body Matrix
        NewtonBodyGetMatrix(pParentNewtonBody, parentBodyMatrix.getPointer());
        // Get the Parent Body Position
        parentPosition = parentBodyMatrix.getTranslation();
    }

    // Get the Newton Body for the child Joint
    pChildNewtonBody = pPhysicsBallAndSocketJoint->getChildNewtonBody();
    if (pChildNewtonBody != 0)
    {
        // Get the child Body Matrix
        NewtonBodyGetMatrix(pChildNewtonBody, childBodyMatrix.getPointer());
        // Get the child Body Position
        childPosition = childBodyMatrix.getTranslation();
    }

    // Set the material
    pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);

    /* TODO: replace me with a proper method of drawing the ball and socket, sometimes there is no parent
        also need proper ball and socket geometry */
    if (pParentNewtonBody != 0)
    {
        irr::core::vector3df start = irr::core::vector3df(parentPosition.getX(), parentPosition.getY(), parentPosition.getZ());
        irr::core::vector3df end = irr::core::vector3df(childPosition.getX(), childPosition.getY(), childPosition.getZ()); ;
        pIrrlichtDevice->getVideoDriver()->draw3DLine(start, end, irr::video::SColor(255, 0, 255, 0));
    }

    // restore the veiw matrix and the world matrix
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, previous_camera);
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, previous_world);
}

void PhysicsDebugger::drawCorkscrewJoint(PhysicsCorkscrewJoint* pPhysicsCorkscrewJoint)
{
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    // Get the Camera
    irr::scene::ICameraSceneNode* pCamera = pIrrlichtDevice->getSceneManager()->getActiveCamera();
    // Verify the camera
    if (pCamera == 0)
        return;
    // Cache the current camera matrix and the current world matrix
    irr::core::matrix4 previous_camera = pCamera->getViewMatrix();
    irr::core::matrix4 previous_world = pIrrlichtDevice->getVideoDriver()->getTransform(irr::video::ETS_WORLD);

    // Build a view matrix so that lines are drawn correctly
    irr::core::matrix4 mat;
    mat.setTranslation(pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix().getTranslation() * RenderScaleToNewton);
    mat.setRotationDegrees(pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix().getRotationDegrees());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);

    // Get the Newton Body for the Joint
    NewtonBody* pNewtonBody = pPhysicsCorkscrewJoint->getChildNewtonBody();
    // Make a container for the body matrix
    NewtonMatrix4 bodyMatrix;
    // Get the Body Matrix
    NewtonBodyGetMatrix(pNewtonBody, bodyMatrix.getPointer());
    // Get the Body Position
    NewtonVector3 position = bodyMatrix.getTranslation();
    // Get the Joint Pin
    NewtonVector3 pin = pPhysicsCorkscrewJoint->getPin();

    // Set the material
    pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);

    irr::core::vector3df start = irr::core::vector3df(position.getX(), position.getY(), position.getZ());
    irr::core::vector3df end = start + irr::core::vector3df(pin.getX(), pin.getY(), pin.getZ()) * 100.0f;
    pIrrlichtDevice->getVideoDriver()->draw3DLine(start, end, irr::video::SColor(255, 0, 255, 0));
    end = start - irr::core::vector3df(pin.getX(), pin.getY(), pin.getZ()) * 100.0f;
    pIrrlichtDevice->getVideoDriver()->draw3DLine(start, end, irr::video::SColor(255, 0, 255, 0));

    // restore the veiw matrix and the world matrix
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, previous_camera);
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, previous_world);
}

void PhysicsDebugger::drawCustomJoint(PhysicsCustomJoint* pPhysicsCustomJoint)
{
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    // Get the Camera
    irr::scene::ICameraSceneNode* pCamera = pIrrlichtDevice->getSceneManager()->getActiveCamera();
    // Verify the camera
    if (pCamera == 0)
        return;
    // Cache the current camera matrix and the current world matrix
    irr::core::matrix4 previous_camera = pCamera->getViewMatrix();
    irr::core::matrix4 previous_world = pIrrlichtDevice->getVideoDriver()->getTransform(irr::video::ETS_WORLD);

    // Build a view matrix so that lines are drawn correctly
    irr::core::matrix4 mat;
    mat.setTranslation(pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix().getTranslation() * RenderScaleToNewton);
    mat.setRotationDegrees(pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix().getRotationDegrees());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);

//    // Get the Newton Body for the Joint
//    NewtonBody* pNewtonBody = pPhysicsBallAndSocketJoint->getNewtonBody();
//    // Make a container for the body matrix
//    NewtonMatrix4 bodyMatrix;
//    // Get the Body Matrix
//    NewtonBodyGetMatrix(pNewtonBody, bodyMatrix.getPointer());
//    // Get the Body Position
//    NewtonVector3 position = bodyMatrix.getTranslation();
//    // Get the Joint Pin
//    NewtonVector3 pin = pPhysicsBallAndSocketJoint->getPin();
//
//    // Set the material
//    pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
//
//    irr::core::vector3df start = irr::core::vector3df(position.getX(), position.getY(), position.getZ());
//    irr::core::vector3df end = start + irr::core::vector3df(pin.getX(), pin.getY(), pin.getZ()) * 100.0f;
//    pIrrlichtDevice->getVideoDriver()->draw3DLine(start, end, irr::video::SColor(255, 0, 255, 0));

    // restore the veiw matrix and the world matrix
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, previous_camera);
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, previous_world);
}

void PhysicsDebugger::drawHingeJoint(PhysicsHingeJoint* pPhysicsHingeJoint)
{
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    // Get the Camera
    irr::scene::ICameraSceneNode* pCamera = pIrrlichtDevice->getSceneManager()->getActiveCamera();
    // Verify the camera
    if (pCamera == 0)
        return;
    // Cache the current camera matrix and the current world matrix
    irr::core::matrix4 previous_camera = pCamera->getViewMatrix();
    irr::core::matrix4 previous_world = pIrrlichtDevice->getVideoDriver()->getTransform(irr::video::ETS_WORLD);

    // Build a view matrix so that lines are drawn correctly
    irr::core::matrix4 mat;
    mat.setTranslation(pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix().getTranslation() * RenderScaleToNewton);
    mat.setRotationDegrees(pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix().getRotationDegrees());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);

//    // Get the Newton Body for the Joint
//    NewtonBody* pNewtonBody = pPhysicsBallAndSocketJoint->getNewtonBody();
//    // Make a container for the body matrix
//    NewtonMatrix4 bodyMatrix;
//    // Get the Body Matrix
//    NewtonBodyGetMatrix(pNewtonBody, bodyMatrix.getPointer());
//    // Get the Body Position
//    NewtonVector3 position = bodyMatrix.getTranslation();
//    // Get the Joint Pin
//    NewtonVector3 pin = pPhysicsBallAndSocketJoint->getPin();
//
//    // Set the material
//    pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
//
//    irr::core::vector3df start = irr::core::vector3df(position.getX(), position.getY(), position.getZ());
//    irr::core::vector3df end = start + irr::core::vector3df(pin.getX(), pin.getY(), pin.getZ()) * 100.0f;
//    pIrrlichtDevice->getVideoDriver()->draw3DLine(start, end, irr::video::SColor(255, 0, 255, 0));

    // restore the veiw matrix and the world matrix
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, previous_camera);
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, previous_world);
}

void PhysicsDebugger::drawSliderJoint(PhysicsSliderJoint* pPhysicsSliderJoint)
{
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    // Get the Camera
    irr::scene::ICameraSceneNode* pCamera = pIrrlichtDevice->getSceneManager()->getActiveCamera();
    // Verify the camera
    if (pCamera == 0)
        return;
    // Cache the current camera matrix and the current world matrix
    irr::core::matrix4 previous_camera = pCamera->getViewMatrix();
    irr::core::matrix4 previous_world = pIrrlichtDevice->getVideoDriver()->getTransform(irr::video::ETS_WORLD);

    // Build a view matrix so that lines are drawn correctly
    irr::core::matrix4 mat;
    mat.setTranslation(pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix().getTranslation() * RenderScaleToNewton);
    mat.setRotationDegrees(pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix().getRotationDegrees());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);

    // Get the Newton Body for the Joint
    NewtonBody* pNewtonBody = pPhysicsSliderJoint->getChildNewtonBody();
    // Make a container for the body matrix
    NewtonMatrix4 bodyMatrix;
    // Get the Body Matrix
    NewtonBodyGetMatrix(pNewtonBody, bodyMatrix.getPointer());
    // Get the Body Position
    NewtonVector3 position = bodyMatrix.getTranslation();
    // Get the Joint Pin
    NewtonVector3 pin = pPhysicsSliderJoint->getPin();

    // Set the material
    pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);

    irr::core::vector3df start = irr::core::vector3df(position.getX(), position.getY(), position.getZ());
    irr::core::vector3df end = start + irr::core::vector3df(pin.getX(), pin.getY(), pin.getZ()) * 100.0f;
    pIrrlichtDevice->getVideoDriver()->draw3DLine(start, end, irr::video::SColor(255, 0, 255, 0));
    end = start - irr::core::vector3df(pin.getX(), pin.getY(), pin.getZ()) * 100.0f;
    pIrrlichtDevice->getVideoDriver()->draw3DLine(start, end, irr::video::SColor(255, 0, 255, 0));

    // restore the veiw matrix and the world matrix
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, previous_camera);
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, previous_world);
}

void PhysicsDebugger::drawUniversalJoint(PhysicsUniversalJoint* pPhysicsUniversalJoint)
{
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    // Get the Camera
    irr::scene::ICameraSceneNode* pCamera = pIrrlichtDevice->getSceneManager()->getActiveCamera();
    // Verify the camera
    if (pCamera == 0)
        return;
    // Cache the current camera matrix and the current world matrix
    irr::core::matrix4 previous_camera = pCamera->getViewMatrix();
    irr::core::matrix4 previous_world = pIrrlichtDevice->getVideoDriver()->getTransform(irr::video::ETS_WORLD);

    // Build a view matrix so that lines are drawn correctly
    irr::core::matrix4 mat;
    mat.setTranslation(pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix().getTranslation() * RenderScaleToNewton);
    mat.setRotationDegrees(pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix().getRotationDegrees());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);

//    // Get the Newton Body for the Joint
//    NewtonBody* pNewtonBody = pPhysicsBallAndSocketJoint->getNewtonBody();
//    // Make a container for the body matrix
//    NewtonMatrix4 bodyMatrix;
//    // Get the Body Matrix
//    NewtonBodyGetMatrix(pNewtonBody, bodyMatrix.getPointer());
//    // Get the Body Position
//    NewtonVector3 position = bodyMatrix.getTranslation();
//    // Get the Joint Pin
//    NewtonVector3 pin = pPhysicsBallAndSocketJoint->getPin();
//
//    // Set the material
//    pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);
//
//    irr::core::vector3df start = irr::core::vector3df(position.getX(), position.getY(), position.getZ());
//    irr::core::vector3df end = start + irr::core::vector3df(pin.getX(), pin.getY(), pin.getZ()) * 100.0f;
//    pIrrlichtDevice->getVideoDriver()->draw3DLine(start, end, irr::video::SColor(255, 0, 255, 0));

    // restore the veiw matrix and the world matrix
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, previous_camera);
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, previous_world);
}

void PhysicsDebugger::drawUpVectorJoint(PhysicsUpVectorJoint* pPhysicsUpVectorJoint)
{
    // Validate the irrlicht device
    if (this->pIrrlichtDevice == 0)
        return;
    // Get the Camera
    irr::scene::ICameraSceneNode* pCamera = pIrrlichtDevice->getSceneManager()->getActiveCamera();
    // Verify the camera
    if (pCamera == 0)
        return;
    // Cache the current camera matrix and the current world matrix
    irr::core::matrix4 previous_camera = pCamera->getViewMatrix();
    irr::core::matrix4 previous_world = pIrrlichtDevice->getVideoDriver()->getTransform(irr::video::ETS_WORLD);

    // Build a view matrix so that lines are drawn correctly
    irr::core::matrix4 mat;
    mat.setTranslation(pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix().getTranslation() * RenderScaleToNewton);
    mat.setRotationDegrees(pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix().getRotationDegrees());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);

    // Get the Newton Body for the Joint
    NewtonBody* pNewtonBody = pPhysicsUpVectorJoint->getNewtonBody();
    // Make a container for the body matrix
    NewtonMatrix4 bodyMatrix;
    // Get the Body Matrix
    NewtonBodyGetMatrix(pNewtonBody, bodyMatrix.getPointer());
    // Get the Body Position
    NewtonVector3 position = bodyMatrix.getTranslation();
    // Get the Joint Pin
    NewtonVector3 pin = pPhysicsUpVectorJoint->getPin();

    // Set the material
    pIrrlichtDevice->getVideoDriver()->setMaterial(this->material);

    irr::core::vector3df start = irr::core::vector3df(position.getX(), position.getY(), position.getZ());
    irr::core::vector3df end = start + irr::core::vector3df(pin.getX(), pin.getY(), pin.getZ()) * (100.0f * RenderScaleToNewton);
    pIrrlichtDevice->getVideoDriver()->draw3DLine(start, end, irr::video::SColor(255, 0, 255, 0));

    // restore the veiw matrix and the world matrix
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, previous_camera);
    pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, previous_world);
}
