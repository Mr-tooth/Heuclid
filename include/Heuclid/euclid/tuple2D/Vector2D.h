#pragma once
#ifndef __VECTOR__2D__
#define __VECTOR__2D__

#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace mathlib{
#define _LJH_EUCLID_LIB_END }}

_LJH_EUCLID_LIB_BEGIN
/**
 * A 2D vector represents a physical quantity with a magnitude and a direction in the XY-plane. For
 * instance, it can be used to represent a 2D velocity, force, or translation from one 2D point to
 * another.
 */
template<typename dataType>
class Vector2D
{
public:
    Vector2D():x(dataType(0)),y(dataType(0)){};
    Vector2D(dataType _x, dataType _y):x(_x),y(_y){};
    Vector2D(const Vector2D& other):x(other.x),y(other.y){};

    void setX(const dataType& _x){if(this->x!=_x) this->x = _x;};
    void setY(const dataType& _y){if(this->y!=_y) this->y = _y;};
    dataType getX() const {return this->x;};
    dataType getY() const {return this->y;};

    bool operator==(const Vector2D& other) const
    {return (this->x == other.x&&this->y==other.y);};


private:
    dataType x;
    dataType y;
};

// template<typename dataType>
// Vector2D<dataType>::Vector2D(const Vector2D& other)
// {
//     this->x = other.x;
//     this->y = other.y;
// }

// template<typename dataType>
// void Vector2D<dataType>::setX(const dataType& _x)
// {
//     if(this->x != _x)
//         this->x = _x;
// }

// template<typename dataType>
// void Vector2D<dataType>::setY(const dataType& _y)
// {
//     if(this->y != _y)
//         this->y = _y;
// }

// template<typename dataType>
// dataType Vector2D<dataType>::getX()
// {
//     return this->x;
// }

// template<typename dataType>
// dataType Vector2D<dataType>::getY()
// {
//     return this->y;
// }



_LJH_EUCLID_LIB_END

#endif
