#pragma once
#ifndef __Point__2D__
#define __Point__2D__

#include <cmath>
#include <Eigen/Dense>
#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace heuclid{
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
    Point2D(const Eigen::Matrix<dataType,2,1>& other):x(other(0)),y(other(1)){};

    inline dataType getX() const {return this->x;};
    inline dataType getY() const {return this->y;};
    inline void setX(const dataType& _x) {this->x = _x;};
    inline void setY(const dataType& _y) {this->y = _y;};
    inline void setPoint2D(const dataType& _x,const dataType& _y) {this->x = _x;this->y = _y;};
    inline void setPoint2D(const Point2D& other) {this->x =other.x;this->y = other.y;};
    inline void setPoint2D(const Eigen::Matrix<dataType,2,1>& other) {this->x =other(0);this->y = other(1);};

    //inline bool operator==(dataType _null) {return (this->x==_null&&this->y==_null);};
    
    inline bool operator==(const Point2D& other) const
    {
        return (this->x == other.x && this->y == other.y);
    };

    // 兼容Eigen库
    inline bool operator==(const Eigen::Matrix<dataType,2,1>& other) const
    {
        return (this->x == other(0) && this->y == other(1));
    };

    // {return (this->getX()==other.getX()&&
    //          this->getY()==other.getY());};

    // inline Point2D<dataType> operator=(const Point2D<dataType> & other)
    // {
    //     Point2D<dataType> point;
    //     point.setX(other.getX() );
    //     point.setY(other.getY() );
    //     return point;
    // }

    // 重载运算符 + - * /
    
    

    inline Point2D<dataType> operator+(const Point2D<dataType> & other) const
    {
        Point2D<dataType> point;
        point.setX(this->getX() + other.getX() );
        point.setY(this->getY() + other.getY() );
        return point;
    }

    // 兼容Eigen库
    inline Point2D<dataType> operator+(const Eigen::Matrix<dataType,2,1>& other) const
    {
        Point2D<dataType> point;
        point.setX(this->getX() + other(0) );
        point.setY(this->getY() + other(1) );
        return point;
    }

    inline Point2D<dataType> operator*(const dataType& scale) const
    {
        Point2D<dataType> point;
        point.setX(this->getX() * scale);
        point.setY(this->getY() * scale);
        return point;
    }

    // 兼容Eigen库
    inline Point2D<dataType> operator*(const Eigen::Matrix<dataType,2,1>& scale) const
    {
        Point2D<dataType> point;
        point.setX(this->getX() * scale(0));
        point.setY(this->getY() * scale(1));
        return point;
    }

    inline Point2D<dataType> operator-(const Point2D<dataType> & other) const
    {
        Point2D<dataType> point;
        point.setX(this->getX() - other.getX() );
        point.setY(this->getY() - other.getY() );
        return point;
    }

    // 兼容Eigen库
    inline Point2D<dataType> operator-(const Eigen::Matrix<dataType,2,1>& other) const
    {
        Point2D<dataType> point;
        point.setX(this->getX() - other(0) );
        point.setY(this->getY() - other(1) );
        return point;
    }

    inline Point2D<dataType> operator/(const dataType& scale) const
    {
        Point2D<dataType> point;
        point.setX(this->getX() / scale);
        point.setY(this->getY() / scale);
        return point;
    }

    // 兼容Eigen库
    inline Point2D<dataType> operator/(const Eigen::Matrix<dataType,2,1>& scale) const
    {
        Point2D<dataType> point;
        point.setX(this->getX() / scale(0));
        point.setY(this->getY() / scale(1));
        return point;
    }

    inline Point2D<dataType> operator+=(const Point2D<dataType> & other)
    {
        this->setPoint2D(this->getX() + other.getX(), this->getY() + other.getY());
        return *this;
    }

    // 兼容Eigen库
    inline Point2D<dataType> operator+=(const Eigen::Matrix<dataType,2,1>& other)
    {
        this->setPoint2D(this->getX() + other(0), this->getY() + other(1));
        return *this;
    }

    inline Point2D<dataType> operator-=(const Point2D<dataType> & other)
    {
        this->setPoint2D(this->getX() - other.getX(), this->getY() - other.getY());
        return *this;
    }

    // 兼容Eigen库
    inline Point2D<dataType> operator-=(const Eigen::Matrix<dataType,2,1>& other)
    {
        this->setPoint2D(this->getX() - other(0), this->getY() - other(1));
        return *this;
    }

    inline Point2D<dataType> operator*=(const dataType& scale)
    {
        this->setPoint2D(this->getX() * scale, this->getY() * scale);
        return *this;
    }

    // 兼容Eigen库
    inline Point2D<dataType> operator*=(const Eigen::Matrix<dataType,2,1>& scale)
    {
        this->setPoint2D(this->getX() * scale(0), this->getY() * scale(1));
        return *this;
    }

    inline Point2D<dataType> operator/=(const dataType& scale)
    {
        this->setPoint2D(this->getX() / scale, this->getY() / scale);
        return *this;
    }

    // 兼容Eigen库
    inline Point2D<dataType> operator/=(const Eigen::Matrix<dataType,2,1>& scale)
    {
        this->setPoint2D(this->getX() / scale(0), this->getY() / scale(1));
        return *this;
    }

    inline Point2D<dataType> operator-() const
    {
        Point2D<dataType> point;
        point.setX(-this->getX());
        point.setY(-this->getY());
        return point;
    }

    inline Point2D<dataType> operator+() const
    {
        Point2D<dataType> point;
        point.setX(this->getX());
        point.setY(this->getY());
        return point;
    }

    inline Point2D<dataType> operator=(const Point2D<dataType> & other)
    {
        this->setPoint2D(other.getX(), other.getY());
        return *this;
    }

    // 兼容Eigen库
    inline Point2D<dataType> operator=(const Eigen::Matrix<dataType,2,1>& other)
    {
        this->setPoint2D(other(0), other(1));
        return *this;
    }

    // get the distance between two points, return the data type of the point
    dataType distance(const Point2D& other) const
    {
        double dx = this->getX()-other.getX();
        double dy = this->getY()-other.getY();
        return ::std::sqrt(dx*dx+dy*dy);
    }


    bool epsilonEquals(const Point2D& other, const double& epsilon) const;
    bool geometricallyEquals(const Point2D& other, const double& epsilon) const;
    bool epsilonZero(const double& epsilon);
    // inline void operator= (const Point2D& other) {this->x =other.x;this->y = other.y;};
    // inline void operator= (const Eigen::Matrix<dataType,2,1>& other) {this->x =other(0);this->y = other(1);};

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