#include "PhysicsMaterial.h"

void PhysicsMaterial::makeCollidable()
{
    NewtonMaterialSetDefaultCollidable(this->pNewtonWorld, this->group0, this->group1, 1);
    //std::cout << "Make Collidable: " << this->group0 << " " << this->group1 << std::endl;
    this->collidable = true;
}

void PhysicsMaterial::makeUncollidable()
{
    NewtonMaterialSetDefaultCollidable(this->pNewtonWorld, this->group0, this->group1, 0);
    this->collidable = false;
}

void PhysicsMaterial::makeContinuousCollide()
{
    NewtonMaterialSetContinuousCollisionMode(this->pNewtonWorld, this->group0, this->group1, 1);
    this->continuousCollide = true;
}

void PhysicsMaterial::makeUncontinuousCollide()
{
    NewtonMaterialSetContinuousCollisionMode(this->pNewtonWorld, this->group0, this->group1, 0);
    this->continuousCollide = false;
}

void PhysicsMaterial::setFriction(dFloat staticFriction, dFloat kineticFriction)
{
    NewtonMaterialSetDefaultFriction(this->pNewtonWorld, this->group0, this->group1, staticFriction, kineticFriction);
    this->staticFriction = staticFriction;
    this->kineticFriction = kineticFriction;
}

void PhysicsMaterial::setElasticity(dFloat elasticCoef)
{
    NewtonMaterialSetDefaultElasticity(this->pNewtonWorld, this->group0, this->group1, elasticCoef);
    this->elasticCoef = elasticCoef;
}

void PhysicsMaterial::setSoftness(dFloat softnessCoef)
{
    NewtonMaterialSetDefaultSoftness(this->pNewtonWorld, this->group0, this->group1, softnessCoef);
    this->softnessCoef = softnessCoef;
}
