#pragma once
#ifndef __Point__2D__
#define __Point__2D__

#include <cmath>
#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace mathlib{
#define _LJH_EUCLID_LIB_END }}

_LJH_EUCLID_LIB_BEGIN
/*
* A 2D point represents the 2D coordinates of a location on the XY-plane.
* */
template<typename dataType>
class Point2D
{

public:
    Point2D():x(dataType(0)),y(dataType(0)){};
    Point2D(dataType _x,dataType _y):x(_x),y(_y){};
    Point2D(const Point2D& other):x(other.x),y(other.y){};
    inline dataType getX() const {return this->x;};
    inline dataType getY() const {return this->y;};
    inline void setX(const dataType& _x) {this->x = _x;};
    inline void setY(const dataType& _y) {this->y = _y;};
    inline void setPoint2D(const dataType& _x,const dataType& _y) {this->x = _x;this->y = _y;};
    inline void setPoint2D(const Point2D& other) {this->x =other.x;this->y = other.y;};

    //inline bool operator==(dataType _null) {return (this->x==_null&&this->y==_null);};
    
    inline bool operator==(const Point2D& other) const
    {
        return (this->x == other.x && this->y == other.y);
    };
    // {return (this->getX()==other.getX()&&
    //          this->getY()==other.getY());};

    bool epsilonEquals(const Point2D& other, const double& epsilon) const;
    bool geometricallyEquals(const Point2D& other, const double& epsilon) const;
    bool epsilonZero(const double& epsilon);
    inline void operator= (const Point2D& other) {this->x =other.x;this->y = other.y;};
    //inline void operator==(const Point2D& other) {return (this->x==other.x&&this->y==other.y);};

private:
    dataType x;
    dataType y;
};

template<typename dataType>
bool Point2D<dataType>::epsilonEquals(const Point2D& other, const double& epsilon) const
{
    return (std::abs(this->getX()-other.getX())<=epsilon && std::abs(this->getY()-other.getY())<=epsilon);
}

template<typename dataType>
bool Point2D<dataType>::geometricallyEquals(const Point2D& other, const double& epsilon) const
{
    double dx = this->getX()-other.getX();
    double dy = this->getY()-other.getY();

    return(sqrt(dx*dx+dy*dy)<=epsilon);
}

template<typename dataType>
bool Point2D<dataType>::epsilonZero(const double& epsilon)
{
    return (std::abs(this->getX())<=epsilon && std::abs(this->getY())<=epsilon);
}






_LJH_EUCLID_LIB_END

#endif