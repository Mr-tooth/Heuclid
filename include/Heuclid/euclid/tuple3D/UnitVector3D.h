#pragma once
#ifndef __UNIT__VECTOR__3D__
#define __UNIT__VECTOR__3D__

#include <cmath>
#include <Heuclid/euclid/interfaces/ZeroTestEpsilon.h>
#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace mathlib{
#define _LJH_EUCLID_LIB_END }}

_LJH_EUCLID_LIB_BEGIN
/**
 * Implementation for a 3 dimensional unit-length vector.
 * 
 * This unit vector shares the same API as a regular vector 3D while ensuring it is normalized when
 * accessing directly or indirectly its individual components, i.e. when invoking either
 * {@link #getX()}, {@link #getY()}, or {@link #getZ()}.
 *
 * When the values of this vector are set to zero, the next time it is normalized it will be reset
 * to (1.0, 0.0, 0.0).
 * */
template<typename dataType>
class UnitVector3D
{
public:
    UnitVector3D():x(dataType(0)),y(dataType(0)),z(dataType(0)),dirty(true){};
    UnitVector3D(dataType _x, dataType _y, dataType _z):x(_x),y(_y),z(_z),dirty(true){};
    UnitVector3D(const UnitVector3D& other):x(other.x),y(other.y),z(other.z),dirty(other.dirty){};

    inline void absolute(){this->x = std::abs(this->x);
                           this->y = std::abs(this->y);
                           this->z = std::abs(this->z);};

    inline void negate(){this->x = - this->x;
                         this->y = - this->y;
                         this->z = - this->z;};
    
    void normalize();
    // bool operator==(const dataType& epsl) const 
    // {return (this->x == epsl && this->y == epsl && this->z == epsl);};

    bool operator==(const UnitVector3D& other) const
    {return (this->x==other.x && this->y=other.y && this->z=other.z);};

    bool equals(const dataType& epsl) const
    {return (std::abs(this->x) <= epsl && std::abs(this->y) <= epsl && std::abs(this->z) <= epsl);};

    inline void markAsDirty() {this->dirty = true;};
    inline bool isDirty() const {return this->dirty;};

    void setX(dataType _x);
    void setY(dataType _y);
    void setZ(dataType _z);
    dataType getRawX() const {return this->x;};
    dataType getRawY() const {return this->y;};
    dataType getRawZ() const {return this->z;};

private:
    bool dirty;
    dataType x;
    dataType y;
    dataType z;
};

template<typename dataType>
void UnitVector3D<dataType>::normalize()
{
    if(dirty)
    {
        if(this->equals(dataType(ZERO_TEST_EPSILON)))
        {
            this->x = dataType(1);
            this->y = dataType(0);
            this->z = dataType(0);
        }
        else
        {
            dataType norminverse = dataType(1)/sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
            x *= norminverse;
            y *= norminverse;
            z *= norminverse;
        }
        dirty = false;
    }
}

template<typename dataType>
void UnitVector3D<dataType>::setX(dataType _x)
{
    if(this->x != _x)
    {
        this->x = _x;
        markAsDirty();
    }   
}

template<typename dataType>
void UnitVector3D<dataType>::setY(dataType _y)
{
    if(this->y != _y)
    {
        this->y = _y;
        markAsDirty();
    }   
}

template<typename dataType>
void UnitVector3D<dataType>::setZ(dataType _z)
{
    if(this->z != _z)
    {
        this->z = _z;
        markAsDirty();
    }   
}

_LJH_EUCLID_LIB_END

#endif