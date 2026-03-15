#pragma once
/**
 * @file Point3D.h
 * @brief 3D point representation with arithmetic operations.
 * @author Junhang Lai (赖俊杭)
 */
#ifndef __Point__3D__
#define __Point__3D__

#include <cmath>
#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace heuclid{
#define _LJH_EUCLID_LIB_END }}

_LJH_EUCLID_LIB_BEGIN
/**
 * @brief A 3D point representing coordinates in 3D space.
 *
 * @tparam dataType The scalar type (e.g., double, float).
 *
 * Provides 3D point operations including arithmetic (+, -, *, /),
 * distance computation, and Eigen::Matrix interoperability.
 */
template<typename dataType>
class Point3D
{

public:
    /** @brief Default constructor. Initializes to origin (0, 0, 0). */
    Point3D():x(dataType(0)),y(dataType(0)),z(dataType(0)){};
    /** @brief Construct from x, y, z coordinates. */
    Point3D(dataType _x, dataType _y, dataType _z):x(_x),y(_y),z(_z){};
    /** @brief Copy constructor. */
    Point3D(const Point3D& other):x(other.x),y(other.y),z(other.z){};

    /** @name Getters */
    ///@{
    inline dataType getX() const {return this->x;};
    inline dataType getY() const {return this->y;};
    inline dataType getZ() const {return this->z;};
    ///@}

    /** @name Setters */
    ///@{
    inline void setX(dataType _x) {this->x = _x;};
    inline void setY(dataType _y) {this->y = _y;};
    inline void setZ(dataType _z) {this->z = _z;};
    inline void setPoint3D(const dataType& _x,const dataType& _y,const dataType& _z) {this->x = _x;this->y = _y;this->z = _z;};
    inline void setPoint3D(const Point3D& other) {this->x =other.x;this->y = other.y;this->z = other.z;};
    ///@}

    /** @name Comparison operators */
    ///@{
    inline bool operator==(const Point3D& other) const 
    {return (this->getX()==other.getX()&&
             this->getY()==other.getY()&&
             this->getZ()==other.getZ());};
    ///@}

    /**
     * @brief Check equality within epsilon tolerance (component-wise).
     * @param other The point to compare.
     * @param epsilon The tolerance threshold.
     */
    bool epsilonEquals(const Point3D& other, const double& epsilon);

    /**
     * @brief Check geometric equality (Euclidean distance).
     * @param other The point to compare.
     * @param epsilon The distance threshold.
     */
    bool geometricallyEquals(const Point3D& other, const double& epsilon);

    /**
     * @brief Check if point is at origin within epsilon.
     * @param epsilon The tolerance threshold.
     */
    bool epsilonZero(const double& epsilon);

    /** @brief Assignment operator. */
    inline void operator= (const Point3D& other) {this->x = other.x;this->y = other.y;this->z = other.z;};
    
    // 重载运算符 + - * /
    inline Point3D<dataType> operator+(const Point3D<dataType> & other) const
    {
        Point3D<dataType> point;
        point.setX(this->getX() + other.getX());
        point.setY(this->getY() + other.getY());
        point.setZ(this->getZ() + other.getZ());
        return point;
    }

    inline Point3D<dataType> operator-(const Point3D<dataType> & other) const
    {
        Point3D<dataType> point;
        point.setX(this->getX() - other.getX());
        point.setY(this->getY() - other.getY());
        point.setZ(this->getZ() - other.getZ());
        return point;
    }

    inline Point3D<dataType> operator*(const dataType& scale) const
    {
        Point3D<dataType> point;
        point.setX(this->getX() * scale);
        point.setY(this->getY() * scale);
        point.setZ(this->getZ() * scale);
        return point;
    }

    inline Point3D<dataType> operator/(const dataType& scale) const
    {
        Point3D<dataType> point;
        point.setX(this->getX() / scale);
        point.setY(this->getY() / scale);
        point.setZ(this->getZ() / scale);
        return point;
    }

    // 重载运算符 += -= *= /=
    inline Point3D<dataType> operator+=(const Point3D<dataType> & other)
    {
        this->setX(this->getX() + other.getX());
        this->setY(this->getY() + other.getY());
        this->setZ(this->getZ() + other.getZ());
        return *this;
    }

    inline Point3D<dataType> operator-=(const Point3D<dataType> & other)
    {
        this->setX(this->getX() - other.getX());
        this->setY(this->getY() - other.getY());
        this->setZ(this->getZ() - other.getZ());
        return *this;
    }

    inline Point3D<dataType> operator*=(const dataType& scale)
    {
        this->setX(this->getX() * scale);
        this->setY(this->getY() * scale);
        this->setZ(this->getZ() * scale);
        return *this;
    }

    inline Point3D<dataType> operator/=(const dataType& scale)
    {
        this->setX(this->getX() / scale);
        this->setY(this->getY() / scale);
        this->setZ(this->getZ() / scale);
        return *this;
    }

    // 兼容Eigen库
    inline Point3D<dataType> operator+(const Eigen::Matrix<dataType,3,1>& other) const
    {
        Point3D<dataType> point;
        point.setX(this->getX() + other(0));
        point.setY(this->getY() + other(1));
        point.setZ(this->getZ() + other(2));
        return point;
    }

    inline Point3D<dataType> operator*(const Eigen::Matrix<dataType,3,1>& scale) const
    {
        Point3D<dataType> point;
        point.setX(this->getX() * scale(0));
        point.setY(this->getY() * scale(1));
        point.setZ(this->getZ() * scale(2));
        return point;
    }

    inline Point3D<dataType> operator-(const Eigen::Matrix<dataType,3,1>& other) const
    {
        Point3D<dataType> point;
        point.setX(this->getX() - other(0));
        point.setY(this->getY() - other(1));
        point.setZ(this->getZ() - other(2));
        return point;
    }

    inline Point3D<dataType> operator+=(const Eigen::Matrix<dataType,3,1>& other)
    {
        this->setX(this->getX() + other(0));
        this->setY(this->getY() + other(1));
        this->setZ(this->getZ() + other(2));
        return *this;
    }

    inline Point3D<dataType> operator-=(const Eigen::Matrix<dataType,3,1>& other)
    {
        this->setX(this->getX() - other(0));
        this->setY(this->getY() - other(1));
        this->setZ(this->getZ() - other(2));
        return *this;
    }

    inline Point3D<dataType> operator*=(const Eigen::Matrix<dataType,3,1>& scale)
    {
        this->setX(this->getX() * scale(0));
        this->setY(this->getY() * scale(1));
        this->setZ(this->getZ() * scale(2));
        return *this;
    }

    inline Point3D<dataType> operator/=(const Eigen::Matrix<dataType,3,1>& scale)
    {
        this->setX(this->getX() / scale(0));
        this->setY(this->getY() / scale(1));
        this->setZ(this->getZ() / scale(2));
        return *this;
    }

    // 重载运算符 <<
    friend std::ostream& operator<<(std::ostream& os, const Point3D& point)
    {
        os << "(" << point.getX() << "," << point.getY() << "," << point.getZ() << ")";
        return os;
    }
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

