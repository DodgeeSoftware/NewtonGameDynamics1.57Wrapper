/**
  * @file   EFrictionModel.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  E_FRICTION_MODEL is an enumeration for the Friction Model
  * the Physics world will use. This has to do with optimising calculations
  * when two bodies with materials collide
*/

#ifndef EFRICTIONMODEL_H
#define EFRICTIONMODEL_H

/** An enumeration used by the PhysicsWorld to
  * determine how friction should be modelled **/
enum E_FRICTION_MODEL
{
    EFM_EXACT = 0,    /** Is the exact model. Friction forces are calculated in each frame. This model is good for
                        * applications where precision is more important than speed, ex: realistic simulation. **/
    EFM_ADAPTIVE = 1  /** Is the adaptive model. Here values from previous frames are used to determine the
                        * maximum friction values of the current frame. This is about 10% faster than the exact
                        * model however it may introduce strange friction behaviors. For example a bouncing object
                        * tumbling down a ramp will act as a friction less object because the contacts do not have
                        * continuity. In general each time a new contact is generated the friction value is zero,
                        * only if the contact persist a non zero friction values is used. The second effect is that
                        * if a normal force is very strong, and if the contact is suddenly destroyed, a very strong
                        * friction force will be generated at the contact point making the object react in a non-familiar way. **/
};

#endif // EFRICTIONMODEL_H
