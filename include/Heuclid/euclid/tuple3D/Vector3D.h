#pragma once
#ifndef __VECTOR__3D__
#define __VECTOR__3D__

#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace mathlib{
#define _LJH_EUCLID_LIB_END }}

_LJH_EUCLID_LIB_BEGIN
/**
 * A 3D vector represents a physical quantity with a magnitude and a direction in the XY-plane. For
 * instance, it can be used to represent a 3D velocity, force, or translation from one 3D point to
 * another.
 */
template<typename dataType>
class Vector3D
{
public:
    Vector3D():x(dataType(0)),y(dataType(0)),z(dataType(0)){};
    Vector3D(dataType _x, dataType _y, dataType _z):x(_x),y(_y),z(_z){};
    Vector3D(const Vector3D& other):x(other.x),y(other.y),z(other.z){};

    void setX(const dataType& _x){if(this->x!=_x) this->x = _x;};
    void setY(const dataType& _y){if(this->y!=_y) this->y = _y;};
    void setZ(const dataType& _z){if(this->z!=_z) this->z = _z;};
    dataType getX() const {return this->x;};
    dataType getY() const {return this->y;};
    dataType getZ() const {return this->z;};

    bool operator==(const Vector2D& other) const
    {return (this->x == other.x&&this->y==other.y&&this->z==other.z);};
    
private:
    dataType x;
    dataType y;
    dataType z;
};

_LJH_EUCLID_LIB_END

#endif