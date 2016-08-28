/**
  * @file   NewtonAABB.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  NewtonAABB is a simple class defining a Newton Axis Aligned Bounding Box
*/

#ifndef NEWTONAABB_H
#define NEWTONAABB_H

// LUA Includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
// LUA BIND Includes
#include <luabind/luabind.hpp>

// C++ Includes
#include <cstddef>
#include <cmath>

// NEWTON Includes
#include <newton.h>

/** @class NewtonAABB
  * @brief An simple container for an Axis Aligned bounding box
  * @detail This is used to define the size of the physics world along
  * with get the bounding boxes of NewtonBodies. it describes an
  * Axis-Aligned Bounding Box by two points which make up two
  * diagonally opposite vertices of the box **/
class NewtonAABB
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        NewtonAABB()
        {
            MinEdge[0] = MinEdge[1] = MinEdge[2] = 0.0f;
            MaxEdge[0] = MaxEdge[1] = MaxEdge[2] = 0.0f;
        }
        //! Constructor taking 6 floats
        NewtonAABB(dFloat x0, dFloat y0, dFloat z0, dFloat x1, dFloat y1, dFloat z1)
        {
            MinEdge[0] = x0;
            MinEdge[1] = y0;
            MinEdge[2] = z0;
            MaxEdge[0] = x1;
            MaxEdge[1] = y1;
            MaxEdge[2] = z1;
            this->fix();
        }
        //! Destructor
        virtual ~NewtonAABB() {}

    protected:
        // Methods and Members

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Methods and Members

    protected:
        // Methods and Members

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        /** @brief Get Min Edge X
          * @return minimum edge x **/
        virtual const dFloat getMinEdgeX() const { return MinEdge[0]; }
        /** @brief Set Min Edge X
          * @param x Min Edge X **/
        virtual void setMinEdgeX(dFloat x) { MinEdge[0] = x; this->fix(); }
        /** @brief Get Min Edge Y
          * @return y Min Edge Y **/
        virtual const dFloat getMinEdgeY() const { return MinEdge[1]; }
        /** @brief Set Min Edge Y
          * @param y Min Edge Y **/
        virtual void setMinEdgeY(dFloat y) { MinEdge[1] = y; this->fix(); }
        /** @brief Get Min Edge Z
          * @return Min Egde Z **/
        virtual const dFloat getMinEdgeZ() const { return MinEdge[2]; }
        /** @brief Set Min Edge Z
          * @param z Min Edge Z **/
        virtual void setMinEdgeZ(dFloat z) { MinEdge[2] = z; this->fix(); }
        /** @brief Get Max Edge X
          * @return x Max Edge **/
        virtual const dFloat getMaxEdgeX() const { return MaxEdge[0]; }
        /** @brief Set Max Edge X
          * @param x Max Edge X **/
        virtual void setMaxEdgeX(dFloat x) { MaxEdge[0] = x; this->fix(); }
        /** @brief Get Max Edge Y
          * @return Max Edge Y **/
        virtual const dFloat getMaxEdgeY() const { return MaxEdge[1]; }
        /** @brief Set Max Edge Y
          * @param y Max Edge Z **/
        virtual void setMaxEdgeY(dFloat y) { MaxEdge[1] = y; this->fix(); }
        /** @brief Get Max Edge Z
          * @return Max Edge Z **/
        virtual const dFloat getMaxEdgeZ() const { return MaxEdge[2]; }
        /** @brief Set Max Edge Z
          * @param z Max Edge Z **/
        virtual void setMaxEdgeZ(dFloat z) { MaxEdge[2] = z; this->fix(); }
        /** @brief Get MinEdge
          * @return Min Edge as a dFloat[3] array **/
        virtual dFloat* getMinEdge() { return &(MinEdge[0]); }
        /** @brief Set MinEdge
          * @param x Min Edge X
          * @param y Min Edge Y
          * @param z Min Edge Z **/
        virtual void setMinEdge(dFloat x, dFloat y, dFloat z) { MinEdge[0] = x; MinEdge[1] = y; MinEdge[2] = z; this->fix(); }
        /** @brief Get MaxEdge
          * @return MaxEdge as a dFloat[3] array **/
        virtual dFloat* getMaxEdge() { return &(MaxEdge[0]); }
        /** @brief Set MaxEdge
          * @param x Max Edge X
          * @param y Max Edge Y
          * @param z Max Edge z **/
        virtual void setMaxEdge(dFloat x, dFloat y, dFloat z) { MaxEdge[0] = x; MaxEdge[1] = y; MaxEdge[2] = z; this->fix(); }
        /** @brief Make sure that the MinEdge is the Min Edge and the MaxEdge is the MaxEdge **/
        virtual void fix()
        {
            // Swap Co-ordinates if the edges are incorrect
            if (MinEdge[0] > MaxEdge[0])
                { dFloat temp = MinEdge[0]; MinEdge[0] = MaxEdge[0]; MaxEdge[0] = temp; }
            // Swap Co-ordinates if the edges are incorrect
            if (MinEdge[1] > MaxEdge[1])
                { dFloat temp = MinEdge[1]; MinEdge[1] = MaxEdge[1]; MaxEdge[1] = temp; }
            // Swap Co-ordinates if the edges are incorrect
            if (MinEdge[2] > MaxEdge[2])
                { dFloat temp = MinEdge[2]; MinEdge[2] = MaxEdge[2]; MaxEdge[2] = temp; }
        }

    protected:
        // MinEgde is made of of three floats which make up a point in space
        dFloat MinEdge[3];
        // MaxEdge is made of of three floats which make up a point in space
        dFloat MaxEdge[3];

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a LuaState
        static void bindToLua(lua_State* pLuaState)
        {
            // TODO: implement me
        }
};

#endif // NEWTONAABB_H
