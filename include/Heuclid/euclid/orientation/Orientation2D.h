#pragma once
#ifndef __Orientation__2D__
#define __Orientation__2D__

#include <cmath>
#define pi_o 3.1415926535
#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace mathlib{
#define _LJH_EUCLID_LIB_END }}

_LJH_EUCLID_LIB_BEGIN
class Orientation2D
{
public:
    Orientation2D():yaw(0.0){};
    Orientation2D(double _yaw){this->yaw = this->shiftProperYaw(_yaw);};

    void setYaw(const double& _yaw);
    inline double getYaw() const {return this->yaw;};

    bool epsilonEquals(const Orientation2D& other, const double& epsilon) const;
    bool geometricallyEquals(const Orientation2D& other, const double& epsilon);
    bool epsilonZero(const double& epsilon);

    double shiftProperYaw(double _yaw);

    inline void operator=(const Orientation2D& other) {this->yaw = other.yaw;};
    inline bool operator==(const Orientation2D& other) const {return (this->yaw==other.yaw);};
private:
    double yaw;
};

_LJH_EUCLID_LIB_END

#endif