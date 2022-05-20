#pragma once
#ifndef __Pose__3D__
#define __Pose__3D__

#include <Heuclid/title/Title.h>
#include <Heuclid/euclid/tuple3D/Point3D.h>
#include <Heuclid/euclid/tuple4D/Quaternion.h>


_LJH_EUCLID_LIB_BEGIN

/**
 * A {@code Pose3D} represents a position and orientation in 3 dimensions.
 */
template<typename dataType>
class Pose3D
{
private: 
    Point3D<dataType> position;
    Quaternion<dataType> orientation;

public:
    Pose3D():position(),orientation(){};
    Pose3D(dataType _x,dataType _y, dataType _z, dataType _yaw, dataType _pitch, dataType _roll):position(_x,_y,_z),orientation(_yaw,_pitch,_roll){};
    Pose3D(const Pose3D& other):position(other.position),orientation(other.orientation){};

    Point3D<dataType> getPosition() const{return this->position;};
    Quaternion<dataType> getOrientation() const{return this->orientation;};

    void setX(const dataType& _x) {this->position.setX(_x);};
    void setY(const dataType& _y) {this->position.setY(_y);};
    void setZ(const dataType& _z) {this->position.setZ(_z);};

    void setYawPitchRoll(const dataType& _yaw, const dataType& _pitch, const dataType& _roll) {this->orientation.setYawPitchRoll(_yaw,_pitch,_roll);};
    //void setYaw(const double& _yaw) {this->orientation;};


    bool epsilonEquals(const Pose3D& other, const double epsilon);
    bool geometricallyEquals(const Pose3D& other, const double& epsilon);
    void operator=(const Pose3D& other);
};

template<typename dataType>
bool Pose3D<dataType>:: epsilonEquals(const Pose3D& other, const double epsilon)
{
    return (this->position.epsilonEquals(other.position,epsilon) &&
            this->orientation.epsilonEquals(other.orientation,epsilon));
}

template<typename dataType>
bool Pose3D<dataType>:: geometricallyEquals(const Pose3D& other, const double& epsilon)
{
    return (this->position.geometricallyEquals(other.position,epsilon) &&
            this->orientation.geometricallyEquals(other.orientation,epsilon));
}

template<typename dataType>
void Pose3D<dataType>:: operator=(const Pose3D& other)
{
    this->position = other.position;
    this->orientation = other.orientation;
}








_LJH_EUCLID_LIB_END


#endif
