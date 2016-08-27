/**
  * @file   EPlatformArchitecture.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  E_PLATFORM_ARCHITECTURE is an enumeration for the Platform Architecture
  * the Physics world will use. This has to do with using a floating point processor
  * or a not and is provided when the target machine might not have a dedicated unit
*/

#ifndef EPLATFORMARCHITECTURE_H
#define EPLATFORMARCHITECTURE_H

/** An enumeration used by the PhysicsWorld to determin
  * which platform architecture to adopt **/
enum E_PLATFORM_ARCHITECTURE
{
    EPA_DEFAULT = 0, /** force the hardware lower common denominator for the running platform. **/
    EPA_MEDIUM = 1,  /** will try to use common floating point enhancement like spacial
                       * instruction set on the specific architecture. This mode made lead to result
                       * that differ from mode 1 and 2 as the accumulation round off errors maybe different. **/
    EPA_BEST = 2     /** the engine will try to use the best possible hardware setting found in the current
                       * platform this is the default configuration. This mode made lead to result that differ
                       * from mode 1 and 2 as the accumulation round off errors maybe different. **/
};

#endif // EPLATFORMARCHITECTURE_H
