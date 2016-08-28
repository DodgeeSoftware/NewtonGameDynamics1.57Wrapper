/**
  * @file   NewtonVector2.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  NewtonVector2 is a mathematical vector composed of
  * an x, y co-ordinate and provides typical vector operations
  * such as dot product, normalisation and magnitude
**/

#ifndef NEWTONVECTOR2_H
#define NEWTONVECTOR2_H

// LUA BIND INCLUDES
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

#include <cmath>
#include <cstddef>
#include <newton.h>

/** @class NewtonVector2
  * @brief An simple container for an mathematical 2d vector
  * @detail The NewtonVector3 class is a minimalistic description of a vector with three components x, y **/
class NewtonVector2
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        NewtonVector2()
        {
            this->point[0] = 0.0;
            this->point[1] = 0.0;
        }
        //! Constructor
        NewtonVector2(dFloat x, dFloat y)
        {
            point[0] = x;
            point[1] = y;
        }
        //! Copy Constructor
        NewtonVector2(const NewtonVector2& other)
        {
            for(int i = 0; i < 2; i++)
                this->point[i] = other.point[i];
        }
        //! Destructor
        virtual ~NewtonVector2() {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        //! Assignment Operator
        NewtonVector2& operator=(const NewtonVector2& rhs)
        {
            for(int i = 0; i < 2; i++)
                this->point[i] = rhs.point[i];
            return *this;
        }
        //! Addition Operator
        NewtonVector2 operator+(const NewtonVector2& other) const
        {
            NewtonVector2 temp;
            for(int i = 0; i < 2; i++)
                temp.point[i] = this->point[i] + other.point[i];
            return temp;
        }
        //! Addition Operator
        NewtonVector2& operator+=(const NewtonVector2& other)
        {
            for(int i = 0; i < 2; i++)
                this->point[i] = this->point[i] + other.point[i];
            return *this;
        }
        //! Negation Operator
        NewtonVector2 operator-() const
        {
            return NewtonVector2(-point[0], -point[1]);
        }
        //! Subtraction Operator
        NewtonVector2 operator-(const NewtonVector2& other) const
        {
            NewtonVector2 temp;
            for(int i = 0; i < 2; i++)
                temp.point[i] = this->point[i] - other.point[i];
            return temp;
        }
        //! Subtraction Operator
        NewtonVector2& operator-=(const NewtonVector2& other)
        {
            for(int i = 0; i < 2; i++)
                this->point[i] = this->point[i] - other.point[i];
            return *this;
        }
        //! Multiplication Operator
        NewtonVector2 operator*(const dFloat& other) const
        {
            NewtonVector2 temp;
            for(int i = 0; i < 2; i++)
                temp.point[i] = this->point[i] * other;
            return temp;
        }
        //! Multiplication Operator
        NewtonVector2& operator*=(const dFloat& other)
        {
            for(int i = 0; i < 2; i++)
                this->point[i] = this->point[i] * other;
            return *this;
        }
        //! Quotient Operator
        NewtonVector2 operator/(const dFloat& other) const
        {
            NewtonVector2 temp;
            for(int i = 0; i < 2; i++)
                temp.point[i] = this->point[i] / other;
            return temp;
        }
        //! Multiplication Operator
        NewtonVector2& operator/=(const dFloat& other)
        {
            for(int i = 0; i < 2; i++)
                this->point[i] = this->point[i] / other;
            return *this;
        }
    public:
        //! Boolean Equality  Operator
        bool operator==(const NewtonVector2& other)
        {
            return ((this->isEqual(this->getX(), other.getX())) && (this->isEqual(this->getY(), other.getY())));
        }
        //! Boolean Equality  Operator
        bool operator!=(const NewtonVector2& other)
        {
            return !((this->isEqual(this->getX(), other.getX())) && (this->isEqual(this->getY(), other.getY())));
        }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Get the length of the vector
        dFloat getLength()
        {
            return (dFloat)(sqrt( (this->getX() * this->getX()) + (this->getY() * this->getY())));
        }
        //! Get the dot product of this NewtonVector2 and another
        dFloat dotProduct(const NewtonVector2& other)
        {
            return this->getX() * other.getX() + this->getY() * other.getY();
        }
        //! Get the cross product of this NewtonVector2 and antoher
        dFloat crossProduct(const NewtonVector2& other)
        {
            return (this->getX() * other.getY() - this->getY() * other.getX());

        }
        //! Normalise this Vector
        void normalise()
        {
            dFloat length = this->getLength();
            point[0] = point[0] / length;
            point[1] = point[1] / length;
        }
        //! Get AngleRadians
        dFloat getAngleRadians()
        {
            dFloat length = this->getLength();
            float x = point[0] / length;
            float y = point[1] / length;
            return atan2(y, x);
        }
        //! Get AngleRadians
        dFloat getAngleDegrees()
        {
            dFloat length = this->getLength();
            float x = point[0] / length;
            float y = point[1] / length;
            return atan2(y, x) / M_PI * 180.0;
        }

    public:
        //! Get X
        const dFloat getX() const { return point[0]; }
        //! Set X
        void setX(dFloat x) { point[0] = x; }
        //! Get Y
        const dFloat getY() const { return point[1]; }
        //! Set Y
        void setY(dFloat y) { point[1] = y; }
        //! Set the position of this vector
        void setPosition(dFloat x, dFloat y) { point[0] = x; point[1] = y; }

    public:
        //! Get the position of this vector
        dFloat* getPointer() { return &(this->point[0]); }

    protected:
        //! The Co-orindates for this vector
        dFloat point[2];

    protected:
        //! Is this value 0 (or near based on the approximation value)
        bool isZero(dFloat value)
        {
            #ifndef __USE_DOUBLE_PRECISION__
                return fabsf(value) <= (float)(0.000001f);
            #else
                return fabs(value) <= (double)(0.00000001);
            #endif
        }
        //! Is this value equal to the other (or nearly equal based on the approximation value)
        bool isEqual(dFloat value1, dFloat value2)
        {
            #ifndef __USE_DOUBLE_PRECISION__
                return (value1 + (double)(0.00000001) >= value2) && (value1 - (double)(0.00000001) <= value2);
            #else
                return (value1 + (float)(0.000001f) >= value2) && (value1 - (float)(0.000001f) <= value2);
            #endif
        }
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

#endif // NEWTONVECTOR2_H
