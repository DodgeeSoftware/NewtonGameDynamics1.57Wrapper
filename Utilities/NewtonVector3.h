/**
  * @file   NewtonVector3.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  NewtonVector3 is a mathematical vector composed of
  * an x, y and z co-ordinate and provides typical vector operations
  * such as cross product, dot product, normalisation and magnitude
**/

#ifndef NEWTONVECTOR3_H
#define NEWTONVECTOR3_H

// LUA BIND INCLUDES
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

// C++ INCLUDES
#include <cmath>
#include <cstddef>

// NEWTON INCLUDES
#include <newton.h>

// NEWTON WRAPPER INCLUDES
#include "NewtonVector2.h"

/** @class NewtonVector3
  * @brief An simple container for an mathematical 3d vector
  * @detail The NewtonVector3 class is a minimalistic description of a vector with three components x, y **/
class NewtonVector3
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        NewtonVector3()
        {
            for(int i = 0; i < 3; i++)
                this->point[i] = 0.0;
        }
        //! Constructor
        NewtonVector3(dFloat x, dFloat y, dFloat z)
        {
            point[0] = x;
            point[1] = y;
            point[2] = z;
        }
        //! Copy Constructor
        NewtonVector3(const NewtonVector3& other)
        {
            for(int i = 0; i < 3; i++)
                this->point[i] = other.point[i];
        }
        //! Destructor
        virtual ~NewtonVector3() {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        //! Assignment Operator
        NewtonVector3& operator=(const NewtonVector3& rhs)
        {
            for(int i = 0; i < 3; i++)
                this->point[i] = rhs.point[i];
            return *this;
        }
        //! Addition Operator
        NewtonVector3 operator+(const NewtonVector3& other) const
        {
            NewtonVector3 temp;
            for(int i = 0; i < 3; i++)
                temp.point[i] = this->point[i] + other.point[i];
            return temp;
        }
        //! Addition Operator
        NewtonVector3& operator+=(const NewtonVector3& other)
        {
            for(int i = 0; i < 3; i++)
                this->point[i] = this->point[i] + other.point[i];
            return *this;
        }
        //! Negation Operator
        NewtonVector3 operator-() const
        {
            return NewtonVector3(-point[0], -point[1], -point[2]);
        }
        //! Subtraction Operator
        NewtonVector3 operator-(const NewtonVector3& other) const
        {
            NewtonVector3 temp;
            for(int i = 0; i < 3; i++)
                temp.point[i] = this->point[i] - other.point[i];
            return temp;
        }
        //! Subtraction Operator
        NewtonVector3& operator-=(const NewtonVector3& other)
        {
            for(int i = 0; i < 3; i++)
                this->point[i] = this->point[i] - other.point[i];
            return *this;
        }
        //! Multiplication Operator
        NewtonVector3 operator*(const dFloat& other) const
        {
            NewtonVector3 temp;
            for(int i = 0; i < 3; i++)
                temp.point[i] = this->point[i] * other;
            return temp;
        }
        //! Multiplication Operator
        NewtonVector3& operator*=(const dFloat& other)
        {
            for(int i = 0; i < 3; i++)
                this->point[i] = this->point[i] * other;
            return *this;
        }
        //! Quotient Operator
        NewtonVector3 operator/(const dFloat& other) const
        {
            NewtonVector3 temp;
            for(int i = 0; i < 3; i++)
                temp.point[i] = this->point[i] / other;
            return temp;
        }
        //! Quotient Operator
        NewtonVector3& operator/=(const dFloat& other)
        {
            for(int i = 0; i < 3; i++)
                this->point[i] = this->point[i] / other;
            return *this;
        }

    public:
        //! Boolean Equality  Operator
        bool operator==(const NewtonVector3& other)
        {
            return ((this->isEqual(this->getX(), other.getX())) && (this->isEqual(this->getY(), other.getY())) && (this->isEqual(this->getZ(), other.getZ())));
        }
        //! Boolean Equality  Operator
        bool operator!=(const NewtonVector3& other)
        {
            return !((this->isEqual(this->getX(), other.getX())) && (this->isEqual(this->getY(), other.getY())) && (this->isEqual(this->getZ(), other.getZ())));
        }

    protected:
        // Methods and Members

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Get the length of the vector
        virtual dFloat getLength()
        {
            return (dFloat)(sqrt( (this->getX() * this->getX()) + (this->getY() * this->getY()) + (this->getZ() * this->getZ())));
        }
        //! Get the dot product of this NewtonVector3 and another
        virtual dFloat dotProduct(const NewtonVector3& other)
        {
            return this->getX() * other.getX() + this->getY() * other.getY() + this->getZ() * other.getZ();
        }
        //! Get the cross product of this NewtonVector3 and antoher
        virtual NewtonVector3 crossProduct(const NewtonVector3& other)
        {
            return NewtonVector3(this->getY() * other.getZ() - this->getZ() * other.getY(),
                                this->getZ() * other.getX() - this->getX() * other.getZ(),
                                this->getX() * other.getY() - this->getY() * other.getX());
        }
        //! Normalise this Vector
        virtual void normalise()
        {
            dFloat length = this->getLength();
            point[0] = point[0] / length;
            point[1] = point[1] / length;
            point[2] = point[2] / length;
        }
        //! Get the angle in Radians
        virtual NewtonVector2 getAngleRadians()
        {
            dFloat length = this->getLength();
            NewtonVector2 angle(0.0, 0.0);
            if (length > 0.0)
            {
                if (this->getX() != 0.0)
                {
                    angle.setY(atan2(this->getZ(), this->getX()));
                }
                else if (this->getZ() < 0.0)
                {
                    angle.setY(M_PI);
                }
                angle.setX(acos(this->getY() / length));
            }
            return angle;
        }
        //! Get the angle in Degrees
        virtual NewtonVector2 getAngleDegrees()
        {
            dFloat length = this->getLength();
            NewtonVector2 angle(0.0, 0.0);
            if (length > 0.0)
            {
                if (this->getX() != 0)
                {
                    angle.setY(atan2(this->getZ(), this->getX()));
                }
                else if (this->getZ() < 0)
                {
                    angle.setY(M_PI);
                }
                angle.setX(acos(this->getY() / length));
                angle = angle / M_PI * 180.0;
            }
            return angle;
        }

    public:
        //! Get X
        virtual const dFloat getX() const { return point[0]; }
        //! Set X
        virtual void setX(dFloat x) { point[0] = x; }
        //! Get Y
        virtual const dFloat getY() const { return point[1]; }
        //! Set Y
        virtual void setY(dFloat y) { point[1] = y; }
        //! Get Z
        virtual const dFloat getZ() const { return point[2]; }
        //! Set Z
        virtual void setZ(dFloat z) { point[2] = z; }
        //! Set the position of this vector
        virtual void setPosition(dFloat x, dFloat y, dFloat z) { point[0] = x; point[1] = y; point[2] = z; }

    public:
        //! Get the position of this vector
        virtual dFloat* getPointer() { return &(this->point[0]); }

    protected:
        // The Co-orindates for this vector
        dFloat point[3];

    protected:
        //! Is this value 0 (or near based on the approximation value)
        virtual bool isZero(dFloat value)
        {
            #ifndef __USE_DOUBLE_PRECISION__
                return fabsf(value) <= (float)(0.000001f);
            #else
                return fabs(value) <= (double)(0.00000001);
            #endif
        }
        //! Is this value equal to the other (or nearly equal based on the approximation value)
        virtual bool isEqual(dFloat value1, dFloat value2)
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

#endif // NEWTONVECTOR3_H
