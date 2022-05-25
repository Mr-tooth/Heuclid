#pragma once
#ifndef __Point__3D__
#define __Point__3D__

#include <cmath>
#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace mathlib{
#define _LJH_EUCLID_LIB_END }}

_LJH_EUCLID_LIB_BEGIN
/**
 * A 3D point represents the 3D coordinates of a location in space.
 * <p>
 * */
template<typename dataType>
class Point3D
{

public:
    Point3D():x(dataType(0)),y(dataType(0)),z(dataType(0)){};
    Point3D(dataType _x, dataType _y, dataType _z):x(_x),y(_y),z(_z){};
    Point3D(const Point3D& other):x(other.x),y(other.y),z(other.z){};

    inline dataType getX() const {return this->x;};
    inline dataType getY() const {return this->y;};
    inline dataType getZ() const {return this->z;};
    inline void setX(dataType _x) {this->x = _x;};
    inline void setY(dataType _y) {this->y = _y;};
    inline void setZ(dataType _z) {this->z = _z;};
    inline void setPoint3D(const dataType& _x,const dataType& _y,const dataType& _z) {this->x = _x;this->y = _y;this->z = _z;};
    inline void setPoint3D(const Point3D& other) {this->x =other.x;this->y = other.y;this->z = other.z;};

    inline bool operator==(const Point3D& other) const 
    {return (this->getX()==other.getX()&&
             this->getY()==other.getY()&&
             this->getZ()==other.getZ());};

    bool epsilonEquals(const Point3D& other, const double& epsilon);
    bool geometricallyEquals(const Point3D& other, const double& epsilon);
    bool epsilonZero(const double& epsilon);
    inline void operator= (const Point3D& other) {this->x = other.x;this->y = other.y;this->z = other.z;};
    

private:
    dataType x;
    dataType y;
    dataType z;    
};

template<typename dataType>
bool Point3D<dataType>::epsilonEquals(const Point3D& other, const double& epsilon)
{
    return (std::abs(this->getX()-other.getX())<=epsilon &&
            std::abs(this->getY()-other.getY())<=epsilon &&
            std::abs(this->getZ()-other.getZ())<=epsilon);
}

template<typename dataType>
bool Point3D<dataType>::geometricallyEquals(const Point3D& other, const double& epsilon)
{
    double dx = this->getX()-other.getX();
    double dy = this->getY()-other.getY();
    double dz = this->getZ()-other.getZ();

    return(sqrt(dx*dx+dy*dy+dz*dz)<=epsilon);
}

template<typename dataType>
bool Point3D<dataType>::epsilonZero(const double& epsilon)
{
    return (std::abs(this->getX())<=epsilon &&
            std::abs(this->getY())<=epsilon &&
            std::abs(this->getZ())<=epsilon);
}

_LJH_EUCLID_LIB_END

#endif

