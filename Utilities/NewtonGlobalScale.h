/**
  * @file   NewtonGlobalScale.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  Some renderers (if not most) will use a differnt scale
  * to Newton Game Dynamics. The difference is usually 1.0f / 32.0f
  * This header provides scaling co-efficents to convert between
  * different scales of measurement */

#ifndef NEWTONGLOBALSCALE_H
#define NEWTONGLOBALSCALE_H

// C++ Includes
#include <cstddef>

// NEWTON GAME DYNAMICS Includes
#include <newton.h>
/* NOTE: When using the physics wrapper with different rendering engines
            there is often a discrepency in scale between them. For instance
            Irrlicht. The irrlicht world is 32.0f times the size of the newton
            world, so we have some handy globals to adjust everything. So
            when you are using this wrapper you may need to adjust the scale here
            so that your transformations in the rendering and physics world are
            identical */
const dFloat NewtonToRenderScale = (dFloat)32.0;            /** Value to convert Newton co-ordinate / vector to the rendering systems scale **/
const dFloat RenderScaleToNewton = (dFloat)(1.0 / 32.0);    /** Recipricol of NewtonToRenderScale so we can convert from rendering system scale back to newton scale **/

#endif // NEWTONGLOBALSCALE_H
