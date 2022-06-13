#pragma once
#ifndef __UNIT__VECTOR__2D__
#define __UNIT__VECTOR__2D__

#include <cmath>
#include <Heuclid/euclid/interfaces/ZeroTestEpsilon.h>
#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace mathlib{
#define _LJH_EUCLID_LIB_END }}

_LJH_EUCLID_LIB_BEGIN
/**
 * Implementation for a 2 dimensional unit-length vector.
 * <p>
 * This unit vector shares the same API as a regular vector 2D while ensuring it is normalized when
 * accessing directly or indirectly its individual components, i.e. when invoking either
 * {@link #getX()} or {@link #getY()}.
 *
 * When the values of this vector are set to zero, the next time it is normalized it will be reset
 * to (1.0, 0.0).
 * */
template<typename dataType>
class UnitVector2D
{
public:
    // SetZero means set the vector refer to X(1,0) axis 
    UnitVector2D():x(dataType(1)),y(dataType(0)),dirty(true){};
    UnitVector2D(dataType _x, dataType _y):x(_x),y(_y),dirty(true){};
    UnitVector2D(const UnitVector2D& other);

    inline void absolute(){this->x = std::abs(this->x);this->y = std::abs(this->y);};
    inline void negate(){this->x = - this->x;this->y = - this->y;};
    void normalize();
    //bool operator==(const dataType& epsl) const {return (this->x == epsl && this->y == epsl);};
   
    bool operator==(const UnitVector2D& other) const
    {return (this->x==other.x&&this->y=other.y);};

    bool equals(const dataType& epsl) const
    {return (std::abs(this->x) <= epsl && std::abs(this->y) <= epsl);};

    inline void markAsDirty() {this->dirty = true;};
    inline bool isDirty() const {return this->dirty;};

    void setX(dataType _x);
    void setY(dataType _y);
    dataType getRawX() const {return this->x;};
    dataType getRawY() const {return this->y;};
    
    bool epsilonEquals(const UnitVector2D<dataType>& other, double epsilon);
private:
    bool dirty;
    dataType x;
    dataType y;

    

};

template<typename dataType>
UnitVector2D<dataType>::UnitVector2D(const UnitVector2D& other)
{
    this->x = other.x;
    this->y = other.y;
    this->dirty = other.dirty;
}

template<typename dataType>
void UnitVector2D<dataType>::normalize()
{
    if(dirty)
    {
        if(this->equals(dataType(ZERO_TEST_EPSILON)))
        {
            this->x = dataType(1);
            this->y = dataType(0);
        }
        else
        {
            dataType norminverse = dataType(1)/sqrt(this->x * this->x + this->y * this->y);
            x *= norminverse;
            y *= norminverse;
        }    
        dirty = false;  
    }
}

template<typename dataType>
void UnitVector2D<dataType>::setX(dataType _x)
{
    if(this->x != _x)
    {
        this->x = _x;
        markAsDirty();
    }   
}

template<typename dataType>
void UnitVector2D<dataType>::setY(dataType _y)
{
    if(this->y != _y)
    {
        this->y = _y;
        markAsDirty();
    }   
}

// template<typename dataType>
// dataType UnitVector2D<dataType>::getRawX()
// {
//     return this->x;
// }

// template<typename dataType>
// dataType UnitVector2D<dataType>::getRawY()
// {
//     return this->y;
// }

template<typename dataType>
bool UnitVector2D<dataType>:: epsilonEquals(const UnitVector2D<dataType>& other, double epsilon)
{
    return (std::abs(this->getRawX()-other.getRawX())<epsilon && std::abs(this->getRawY()-other.getRawY())<epsilon);
}

_LJH_EUCLID_LIB_END

#endif