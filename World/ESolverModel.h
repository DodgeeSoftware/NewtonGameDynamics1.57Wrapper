/**
  * @file   ESolverModel.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  E_SOLVER_MODEL is an enumeration for the Solver Model
  * the PhysicsWorld will use when solving physical interactions
*/

#ifndef ESOLVERMODEL_H
#define ESOLVERMODEL_H

/** An enumeration used by the PhysicsWorld to
  * determine which solver model to use **/
enum E_SOLVER_MODEL
{
    ESM_EXACT = 0,    /** Is the exact mode. This is good for application where precision is more important than speed, ex: realistic simulation. **/
    ESM_ADAPTIVE = 1, /** Is the adaptive mode, the solver is not as exact but the simulation will still maintain a high degree of accuracy.
                          This mode is good for applications were a good degree of stability is important but not as important as speed. **/
    ESM_LINEAR = 2    /** Linear mode. The solver will not try to reduce the joints relative acceleration errors to below some limit, instead it
                          will perform up to n passes over the joint configuration each time reducing the acceleration error, but it will terminate
                          when the number of passes is exhausted regardless of the error magnitude. In general this is the fastest mode and is is
                          good for applications where speed is the only important factor, ex: video games. **/
};

#endif // ESOLVERMODEL_H
