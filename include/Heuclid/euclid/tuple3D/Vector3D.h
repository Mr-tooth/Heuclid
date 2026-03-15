/**
 * @file Vector3D.h
 * @brief 3D vector with arithmetic operations.
 * @author Junhang Lai (赖俊杭)
 */

#pragma once
#ifndef __VECTOR__3D__
#define __VECTOR__3D__

#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace heuclid{
#define _LJH_EUCLID_LIB_END }}

_LJH_EUCLID_LIB_BEGIN

/**
 * @brief A 3D vector representing magnitude and direction in 3D space.
 *
 * @tparam dataType The scalar type (e.g., double, float).
 *
 * Can represent physical quantities such as velocity, force, or displacement
 * in 3D space.
 *
 * @note This class is minimal. Consider extending with arithmetic operators
 *       as needed (see Point3D for reference).
 */
template<typename dataType>
class Vector3D
{
public:
    /** @brief Default constructor. Initializes to zero vector. */
    Vector3D():x(dataType(0)),y(dataType(0)),z(dataType(0)){};

    /** @brief Construct from x, y, z components. */
    Vector3D(dataType _x, dataType _y, dataType _z):x(_x),y(_y),z(_z){};

    /** @brief Copy constructor. */
    Vector3D(const Vector3D& other):x(other.x),y(other.y),z(other.z){};

    /** @name Getters */
    ///@{
    dataType getX() const {return this->x;};
    dataType getY() const {return this->y;};
    dataType getZ() const {return this->z;};
    ///@}

    /** @name Setters */
    ///@{
    void setX(const dataType& _x){if(this->x!=_x) this->x = _x;};
    void setY(const dataType& _y){if(this->y!=_y) this->y = _y;};
    void setZ(const dataType& _z){if(this->z!=_z) this->z = _z;};
    ///@}

    /** @brief Equality comparison. */
    bool operator==(const Vector3D& other) const
    {return (this->x == other.x&&this->y==other.y&&this->z==other.z);};

private:
    dataType x; ///< X component
    dataType y; ///< Y component
    dataType z; ///< Z component
};

_LJH_EUCLID_LIB_END

#endif
