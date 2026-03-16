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
#pragma once
/**
 * @file Pose2D.h
 * @brief 2D pose (position + orientation).
 * @author Junhang Lai (赖俊杭)
 */
#ifndef __Pose__2D__
#define __Pose__2D__

#include <Heuclid/euclid/tuple2D/Point2D.h>
#include <Heuclid/euclid/orientation/Orientation2D.h>
#include <Heuclid/euclid/interfaces/ZeroTestEpsilon.h>
#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace heuclid{
#define _LJH_EUCLID_LIB_END }}

_LJH_EUCLID_LIB_BEGIN

/**
 * A {@code Pose2D} represents a position and orientation in the XY-plane.
 */
template<typename dataType>
/** @brief A 2D pose (position + orientation). */
class Pose2D
{
private:
    Point2D<dataType> position;
    Orientation2D orientation;
public:
    Pose2D():position(),orientation(){};
    Pose2D(dataType _x, dataType _y, double _yaw):position(_x,_y),orientation(_yaw){};
    Pose2D(const Pose2D& other):position(other.position),orientation(other.orientation){};

    Point2D<dataType> getPosition() const {return this->position;};
    Orientation2D getOrientation() const {return this->orientation;};

    void setX(const dataType& _x) {this->position.setX(_x);};
    void setY(const dataType& _y) {this->position.setY(_y);};
    void setYaw(const double& _yaw) {this->orientation.setYaw(_yaw);};
    void setPosition(const Point2D<dataType>& other) {this->position.setPoint2D(other);};
    void setPosition(const dataType& _x, const dataType& _y) {this->position.setX(_x); this->position.setY(_y);};
    void setOrientation(const Orientation2D& other) {this->orientation.setYaw(other.getYaw());};
    void setOrientation(const double& _yaw) {this->orientation.setYaw(_yaw);};

    void setPose2D(const Pose2D& other);                                                                         

    bool epsilonEquals(const Pose2D& other, const double& epsilon);
    bool geometricallyEquals(const Pose2D& other, const double& epsilon);
    bool epsilonZero(const double& epsilon) const
    {return (this->getPosition().epsilonZero(epsilon)&&this->getOrientation().epsilonZero(epsilon));};

    void operator=(const Pose2D& other);
    bool operator==(const Pose2D& other) const;
    //inline bool operator==(const dataType& _pos, const double& _yaw) {return (this->)}
    //inline bool operator==(const dataType& _position, const double& _yaw) const{return this->};
};

template<typename dataType>
void Pose2D<dataType>::setPose2D(const Pose2D& other)
{
    this->setPosition(other.getPosition());
    this->setOrientation(other.getOrientation());
    //this->position.setPoint2D(other.getPosition());
    //this->orientation.setYaw(other.getOrientation().getYaw()); 
}

template<typename dataType>
bool Pose2D<dataType>::epsilonEquals(const Pose2D& other, const double& epsilon)
{
    return (this->getPosition().epsilonEquals(other.getPosition(),ZERO_TEST_EPSILON) &&
            this->getOrientation().epsilonEquals(other.getOrientation(),ZERO_TEST_EPSILON));
}

template<typename dataType>
bool Pose2D<dataType>::geometricallyEquals(const Pose2D& other, const double& epsilon)
{
    return (this->getPosition().geometricallyEquals(other.getPosition(),ZERO_TEST_EPSILON)&&
            this->getOrientation().geometricallyEquals(other.getOrientation(),ZERO_TEST_EPSILON));
}

template<typename dataType>
void Pose2D<dataType>::operator=(const Pose2D& other)
{
    this->setPosition(other.getPosition());
    this->setOrientation(other.getOrientation());
}

template<typename dataType>
bool Pose2D<dataType>::operator==(const Pose2D& other) const
{
    return (this->position == other.position &&
            this->orientation == other.orientation);

}

_LJH_EUCLID_LIB_END

#endif