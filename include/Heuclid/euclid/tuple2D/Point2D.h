// Copyright 2024-2026 Junhang Lai (赖俊杭)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
/**
 * @file Point2D.h
 * @brief 2D point representation with arithmetic operations and Eigen interop.
 * @author Junhang Lai (赖俊杭)
 */

#pragma once
#ifndef __Point__2D__
#define __Point__2D__

#include <cmath>
#include <Eigen/Dense>

#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace heuclid{
#define _LJH_EUCLID_LIB_END }}

_LJH_EUCLID_LIB_BEGIN

/**
 * @brief A 2D point representing coordinates on the XY-plane.
 *
 * @tparam dataType The scalar type (e.g., double, float).
 *
 * Provides basic 2D point operations including arithmetic (+, -, *, /),
 * distance computation, norm, and full Eigen::Matrix interoperability.
 *
 * @code
 * Point2D<double> p1(1.0, 2.0);
 * Point2D<double> p2(3.0, 4.0);
 * double dist = p1.distance(p2);
 * Eigen::Vector2d ev = Eigen::Vector2d(5.0, 6.0);
 * Point2D<double> p3 = p1 + ev;  // Eigen interop
 * @endcode
 */
template<typename dataType>
class Point2D
{

public:
    /** @brief Default constructor. Initializes to origin (0, 0). */
    Point2D():x(dataType(0)),y(dataType(0)){};

    /** @brief Construct from x and y coordinates. */
    Point2D(dataType _x,dataType _y):x(_x),y(_y){};

    /** @brief Copy constructor. */
    Point2D(const Point2D& other):x(other.x),y(other.y){};

    /** @brief Construct from an Eigen 2D vector. */
    Point2D(const Eigen::Matrix<dataType,2,1>& other):x(other(0)),y(other(1)){};

    /** @name Getters */
    ///@{
    inline dataType getX() const {return this->x;};
    inline dataType getY() const {return this->y;};
    ///@}

    /** @name Setters */
    ///@{
    inline void setX(const dataType& _x) {this->x = _x;};
    inline void setY(const dataType& _y) {this->y = _y;};
    inline void setPoint2D(const dataType& _x,const dataType& _y) {this->x = _x;this->y = _y;};
    inline void setPoint2D(const Point2D& other) {this->x =other.x;this->y = other.y;};
    inline void setPoint2D(const Eigen::Matrix<dataType,2,1>& other) {this->x =other(0);this->y = other(1);};
    ///@}

    /** @name Comparison operators */
    ///@{
    inline bool operator==(const Point2D& other) const
    {
        return (this->x == other.x && this->y == other.y);
    };
    /** @brief Eigen interoperability comparison. */
    inline bool operator==(const Eigen::Matrix<dataType,2,1>& other) const
    {
        return (this->x == other(0) && this->y == other(1));
    };
    ///@}

    /** @name Arithmetic operators */
    ///@{
    inline Point2D<dataType> operator+(const Point2D<dataType> & other) const
    {
        Point2D<dataType> point;
        point.setX(this->getX() + other.getX() );
        point.setY(this->getY() + other.getY() );
        return point;
    }

    /** @brief Eigen interoperability addition. */
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

    /** @brief Element-wise multiplication with Eigen vector. */
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

    /** @brief Eigen interoperability subtraction. */
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

    /** @brief Element-wise division with Eigen vector. */
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

    inline Point2D<dataType> operator=(const Eigen::Matrix<dataType,2,1>& other)
    {
        this->setPoint2D(other(0), other(1));
        return *this;
    }
    ///@}

    /**
     * @brief Compute Euclidean distance to another point.
     * @param other The target point.
     * @return The distance as dataType.
     */
    dataType distance(const Point2D& other) const
    {
        double dx = this->getX()-other.getX();
        double dy = this->getY()-other.getY();
        return ::std::sqrt(dx*dx+dy*dy);
    }

    /**
     * @brief Compute the Euclidean norm (distance to origin).
     * @return The norm as dataType.
     */
    dataType norm() const
    {
        return ::std::sqrt(this->getX()*this->getX()+this->getY()*this->getY());
    }

    /** @brief Stream output operator. */
    friend std::ostream& operator<<(std::ostream& os, const Point2D& point)
    {
        os << "(" << point.getX() << "," << point.getY() << ")";
        return os;
    }

    /**
     * @brief Check if two points are equal within an epsilon tolerance.
     * @param other The point to compare.
     * @param epsilon The tolerance threshold.
     * @return True if |dx| <= epsilon and |dy| <= epsilon.
     */
    bool epsilonEquals(const Point2D& other, const double& epsilon) const;

    /**
     * @brief Check if two points are geometrically equal (Euclidean distance).
     * @param other The point to compare.
     * @param epsilon The distance threshold.
     * @return True if distance <= epsilon.
     */
    bool geometricallyEquals(const Point2D& other, const double& epsilon) const;

    /**
     * @brief Check if point is at origin within epsilon.
     * @param epsilon The tolerance threshold.
     * @return True if both coordinates are within epsilon of zero.
     */
    bool epsilonZero(const double& epsilon);

private:
    dataType x; ///< X coordinate
    dataType y; ///< Y coordinate
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
