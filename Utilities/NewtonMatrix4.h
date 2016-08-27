/**
  * @file   Matrix4x4.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  Matrix is a mathematical Matrix used to transform
  * and describe the transformation of joints, vehicles and physics bodies
**/

#ifndef NEWTONMATRIX4_H
#define NEWTONMATRIX4_H

// LUA BIND INCLUDES
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

// C++ Includes
#include <cmath>
#include <cstddef>

// NEWTON GAME DYNAMICS Includes
#include <Newton.h>

// GAMEPHYSICS INCLUDES
#include "NewtonVector3.h"

/** The NewtonMatrix4 class is a math structure representing a 4x4 matrix. This matrices are in row major format. Which
    may seem at odds with how the matrix indices are accessed. This is because when you encoding a row major matrix
    in a c/c++ array you need to transpose it, this means row major will appear when references the array as a column
    major matrix. The reason the matrix is in row major format is because this matrix class has been designed with
    Newton in mind which stores matrices in row major format and this wrapper is primarily aimed at irrlicht which
    also stores it matrices in row major format. Please consider this matrix class has been designed to mirror
    the Irrlicht1.8 Matrix4 class and as such has some deliberately broken functions I list them here:
    * Calling SetScale will corrupt your rotation matrix
    * Calling SetRotationDegrees/Radians will remove your scale
    **/
class NewtonMatrix4
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        NewtonMatrix4()
        {
            // Reset the matrix
            for(int i = 0; i < 16; i++)
                this->matrix[i] = 0.0f;
            // Make sure the default matrix is an indentity matrix
            this->matrix[0]  = 1.0f;
            this->matrix[5]  = 1.0f;
            this->matrix[10] = 1.0f;
            this->matrix[15] = 1.0f;
        }
        //! Constructor
        NewtonMatrix4(const dFloat* matrix)
        {
            // Build a matrix from an incoming array
            for(int i = 0; i < 16; i++)
                this->matrix[i] = matrix[i];
        }
        //! Copy Constructor
        NewtonMatrix4(const NewtonMatrix4& other)
        {
            // Copy the 'other' matrix to this object
            for(int i = 0; i < 16; i++)
                this->matrix[i] = other.matrix[i];
        }
        //! Destructor
        virtual ~NewtonMatrix4() {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        //! Assignment Operator
        NewtonMatrix4& operator=(const NewtonMatrix4& rhs)
        {
            // Assign the contents of matrix array to that of the incoming matrix
            for(int i = 0; i < 16; i++)
                this->matrix[i] = rhs.matrix[i];
            // Return a reference to this matrix
            return *this;
        }
        //! Simple operator for linearly accessing every element of the matrix.
        dFloat& operator[](unsigned index)
        {
            // Return a reference to the index in the matrix
            return this->matrix[index];
        }
        //! Multiplication Operator
        NewtonMatrix4 operator*(const dFloat& other) const
        {
            // Create a temporary matrix
            NewtonMatrix4 temp;
            // Multiply this matrix by the incoming matrix
            for(int i = 0; i < 16; i++)
                temp.matrix[i] = this->matrix[i] * other;
            // Return a copy of the newly concatenated matrix
            return temp;
        }
        //! Multiplication Operator for Vectors
        NewtonVector3 operator*(const NewtonVector3& vec)
        {
            // Creat a container for the result of the multiplacation of this vector with this matrix
            NewtonVector3 result;
            // Multiple the matrix and this vector placing the results into the result vector
            result.setX(matrix[0] * vec.getX() + matrix[4] * vec.getY() + matrix[8] * vec.getZ() + matrix[12] * 1.0f);
            result.setY(matrix[1] * vec.getX() + matrix[5] * vec.getY() + matrix[9] * vec.getZ() + matrix[13] * 1.0f);
            result.setZ(matrix[2] * vec.getX() + matrix[6] * vec.getY() + matrix[10] * vec.getZ() + matrix[14] * 1.0f);
            // Return a copy of the new matrix
            return result;
        }
        //! Multiplication Operator for Matrices
        NewtonMatrix4 operator*(const NewtonMatrix4& other) const
        {
            // Create an array to contain our temporary matrix
            dFloat temp[16];
            // Multiply our matrices
            for(unsigned int i = 0; i < 4; i++)
                for(unsigned int j = 0; j < 4; j++)
                    for(unsigned int k = 0; k < 4; k++)
                        temp[i + j * 4] += (this->matrix[i + k * 4] * other.matrix[k + j * 4]);
            // Return a copy of the concatenated matrices
            return NewtonMatrix4(temp);
        }
        //! Multiplication Operator
        NewtonMatrix4& operator*=(const NewtonMatrix4& other)
        {
            // Use the internal overloaded * operator to multiply these matrices
            (*this) = (*this) * other;
            // Return a reference to the concatenated matrices
            return (*this);
        }
        //! Add another matrix.
        NewtonMatrix4 operator+(const NewtonMatrix4& other) const
        {
            // Create an array to contain our temporary matrix
            dFloat temp[16];
            // Add this matrix the other
            for(int i = 0; i < 16; i++)
                temp[i] = this->matrix[i] + other.matrix[i];
            // Return a copy of the concatenated matrices
            return NewtonMatrix4(temp);
        }
        //! Add another matrix.
        NewtonMatrix4& operator+=(const NewtonMatrix4& other)
        {
            // Add this matrix to the other
            for(int i = 0; i < 16; i++)
                this->matrix[i] += other.matrix[i];
            // return a reference to the new matrix
            return *this;
        }
        //! Subtract another matrix.
        NewtonMatrix4 operator-(const NewtonMatrix4& other) const
        {
            // Create an array to contain our temporary matrix
            dFloat temp[16];
            // Subtract other from this matrix
            for(int i = 0; i < 16; i++)
                temp[i] = this->matrix[i] - other.matrix[i];
            // Return a copy of the concatenated matrices
            return temp;
        }
        //! Subtract another matrix.
        NewtonMatrix4 operator-=(const NewtonMatrix4& other)
        {
            // Subtract other from this matrix
            for(int i = 0; i < 16; i++)
                this->matrix[i] -= other.matrix[i];
            // return a reference to the new matrix
            return *this;
        }

    public:
        //! Returns true if other matrix is equal to this matrix.
        bool operator==(const NewtonMatrix4& other) const
        {
            // Compare this matrix to other (matrices that are close to identical will also return true, tolerance depends on the type dFloat is aka either a float or a double)
            for (int i = 0; i < 16; i++)
                if (!(this->isEqual(this->matrix[i], other.matrix[i])))
                    return false; // matrices are not equal
            // matrices are equal
            return true;
        }
        //! Returns true if other matrix is not equal to this matrix.
        bool operator!=(const NewtonMatrix4& other) const
        {
            // return true when the matrices are not equal
            return !(*this == other);
        }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Get a Pointer the Matrix
        virtual dFloat* getPointer()
        {
            // Return a pointer to the matrix array
            return &(this->matrix[0]);
        }
        //! Set the Matrix
        virtual void setMatrix(dFloat* matrix)
        {
            // Set this matrix to equal the contents of the incoming matrix array
            for(int i = 0; i < 16; i++)
                this->matrix[i] = matrix[i];
        }

    public:
        //! Get the Translation
        virtual const NewtonVector3 getTranslation() const
        {
            // Return the translation component of this matrix
            return NewtonVector3(this->matrix[12], this->matrix[13], this->matrix[14]);
        }
        //! Set the Translation
        virtual void setTranslation(dFloat x, dFloat y, dFloat z)
        {
            // Set the translation component of this matrix
            this->matrix[12] = x;
            this->matrix[13] = y;
            this->matrix[14] = z;
        }
        //! Set the Translation
        virtual void setTranslation(NewtonVector3 translation)
        {
            // Set the translation component of this matrix
            this->setTranslation(translation.getX(), translation.getY(), translation.getZ());
        }

    public:
        //! Get the RotationDegrees
        virtual const NewtonVector3 getRotationDegrees()
        {
             // An array to contain our euler angles
             dFloat rotation[3] = {0.0f, 0.0f, 0.0f};
             // The NewtonGetEulerAngle function returns Euler angles in radians
             NewtonGetEulerAngle(this->matrix, rotation);
             // Convert from radians to degrees and return the Euler angles
             return NewtonVector3(rotation[0] * 180.0f / M_PI, rotation[1] * 180.0f / M_PI, rotation[2] * 180.0f / M_PI);
        }
        //! Set the Rotation in degrees
        virtual void setRotationDegrees(dFloat x, dFloat y, dFloat z)
        {
            // Convert the degrees into radians
            this->setRotationRadians(x * M_PI / 180, y * M_PI / 180, z * M_PI / 180);
        }
        //! Set the Rotation in degrees
        virtual void setRotationDegrees(NewtonVector3 rotation)
        {
            this->setRotationDegrees(rotation.getX(), rotation.getY(), rotation.getZ());
        }
        //! Get Rotation in radians
        virtual const NewtonVector3 getRotationRadians()
        {
             dFloat rotation[3] = {0.0f, 0.0f, 0.0f};
             NewtonGetEulerAngle(this->matrix, rotation);
             return NewtonVector3(rotation[0], rotation[1], rotation[2]);
        }
        //! Set the Rotation in radians (calling this function will remove scale from the matrix)
        virtual void setRotationRadians(dFloat x, dFloat y, dFloat z)
        {
            // Get Translation Components from the Matrix
            float xTranslation = this->matrix[12];
            float yTranslation = this->matrix[13];
            float zTranslation = this->matrix[14];
            // Make an array containing the roll(x), pitch(y) and yaw(z) Euler angles
            dFloat rotation[3] = {x, y, z};
            // Make the local matrix a concatenated rotation matrix
            NewtonSetEulerAngle(rotation, this->matrix);
            // Put translation components back into the matrix
            this->matrix[12] = xTranslation;
            this->matrix[13] = yTranslation;
            this->matrix[14] = zTranslation;
        }
        //! Set the Rotation in radians
        virtual void setRotationRadians(NewtonVector3 rotation)
        {
            this->setRotationRadians(rotation.getX(), rotation.getY(), rotation.getZ());
        }

    public:
        //! Get the Scale (scale will always be positive as I haven't decomposed the matrix to a high enough degree to deal with negative scale)
        virtual const NewtonVector3 getScale()
        {
            return NewtonVector3(sqrtf(this->matrix[0] * this->matrix[0] + this->matrix[1] * this->matrix[1] + this->matrix[2] * this->matrix[2]),
                                sqrtf(this->matrix[4] * this->matrix[4] + this->matrix[5] * this->matrix[5] + this->matrix[6] * this->matrix[6]),
                                sqrtf(this->matrix[8] * this->matrix[8] + this->matrix[9] * this->matrix[9] + this->matrix[10] * this->matrix[10]));

        }
        //! Set the Scale (calling this function will corrupt any rotation components to this matrix)
        virtual void setScale(dFloat x, dFloat y, dFloat z)
        {
            /* WARNING: Calling this function after setting the euler angles will destroy parts of the rotation matrix*/
            this->matrix[0] = x; this->matrix[5] = y; this->matrix[10] = z;
        }
        //! Set the Scale
        virtual void setScale(NewtonVector3 scale)
        {
            this->setScale(scale.getX(), scale.getY(), scale.getZ());
        }

    public:
        //! Make Identity
        virtual void makeIdentity()
        {
            for(int i = 0; i < 16; i++)
                matrix[i] = 0.0f;
            this->matrix[0]  = 1.0f;
            this->matrix[5]  = 1.0f;
            this->matrix[10] = 1.0f;
            this->matrix[15] = 1.0f;
        }
        //! Invert Matrix
        virtual void makeInverse()
        {
            // TODO: Find out how to invert a matrix
        }
        //! Transpose Matrix
        virtual void transpose()
        {
            NewtonMatrix4 temp(*this);
            this->matrix[0] = temp[0];
            this->matrix[1] = temp[4];
            this->matrix[2] = temp[8];
            this->matrix[3] = temp[12];
            this->matrix[4] = temp[1];
            this->matrix[5] = temp[5];
            this->matrix[6] = temp[9];
            this->matrix[7] = temp[13];
            this->matrix[8] = temp[2];
            this->matrix[9] = temp[6];
            this->matrix[10] = temp[10];
            this->matrix[11] = temp[14];
            this->matrix[12] = temp[3];
            this->matrix[13] = temp[7];
            this->matrix[14] = temp[11];
            this->matrix[15] = temp[15];
        }
        //! Build a Roll (rotation around x axis) Matrix
        virtual NewtonMatrix4 buildRollMatrix(float radians)
        {
            NewtonMatrix4 rollMatrix;
            rollMatrix.makeIdentity();
            rollMatrix[5] = cos(radians);
            rollMatrix[6] = sin(radians);
            rollMatrix[9] = -sin(radians);
            rollMatrix[10] = -cos(radians);
            return rollMatrix;
        }
        //! Build a Pitch (rotation around y axis) Matrix
        virtual NewtonMatrix4 buildPitchMatrix(float radians)
        {
            NewtonMatrix4 pitchMatrix;
            pitchMatrix.makeIdentity();
            pitchMatrix[0] = cos(radians);
            pitchMatrix[2] = -sin(radians);
            pitchMatrix[8] = sin(radians);
            pitchMatrix[10] = cos(radians);
            return pitchMatrix;
        }
        //! Build a Yaw (rotation around z axis) Matrix
        virtual NewtonMatrix4 buildYawMatrix(float radians)
        {
            NewtonMatrix4 yawMatrix;
            yawMatrix.makeIdentity();
            yawMatrix[0] = cos(radians);
            yawMatrix[1] = sin(radians);
            yawMatrix[4] = -sin(radians);
            yawMatrix[5] = cos(radians);
            return yawMatrix;
        }
    protected:
        //! Is this value 0 (or near based an the approximation value)
        virtual const bool isZero(dFloat value) const
        {
            #ifndef __USE_DOUBLE_PRECISION__
                return fabsf(value) <= (float)(0.000001f);
            #else
                return fabs(value) <= (double)(0.00000001);
            #endif
        }
        //! Is this value equal to the other (or nearly equal based on the approximation value)
        virtual const bool isEqual(dFloat value1, dFloat value2) const
        {
            #ifndef __USE_DOUBLE_PRECISION__
                return (value1 + (double)(0.00000001) >= value2) && (value1 - (double)(0.00000001) <= value2);
            #else
                return (value1 + (float)(0.000001f) >= value2) && (value1 - (float)(0.000001f) <= value2);
            #endif
        }

    protected:
        // The matrix array
        dFloat matrix[16];

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

#endif // NEWTONMATRIX4_H
