#pragma once

#include <Heuclid/title/Title.h>
#include <cmath>
_LJH_EUCLID_LIB_BEGIN
/**
 * Class used to represent unit-quaternions 
 * which are used to represent 3D orientations.
 * 
 * s + xi + yj + zk
 * 
 * @author Lai Junhang
 */
template<typename dataType>
class Quaternion
{
private:
    dataType x;
    dataType y;
    dataType z;
    dataType s;



public:
    /**
    * Sets this quaternion to the neutral quaternion representing a 'zero' rotation.
    */
    Quaternion():x(dataType(0)),y(dataType(0)),z(dataType(0)),s(dataType(1)){};
    Quaternion(dataType _x, dataType _y, dataType _z, dataType _s);
    Quaternion(const Quaternion& other):x(other.x),y(other.y),z(other.z),s(other.s){};

    // TODO: write this in RotateConversion.cpp
    // Given the Euler Angle ZYX, convert the Euler2Quaternion
    Quaternion(dataType _yaw, dataType _pitch, dataType _roll);

    inline dataType getX() const {return this->x;};
    inline dataType getY() const {return this->y;};
    inline dataType getZ() const {return this->z;};
    inline dataType getS() const {return this->s;};

    dataType getYaw() const;
    dataType getPitch() const;
    dataType getRoll() const;

    void setYawPitchRoll(double _yaw, double _pitch, double _roll);

    inline void setUnsafe(dataType _x, dataType _y, dataType _z, dataType _s)
        {this->x = _x;this->y = _y;this->z = _z;this->s = _s;};

    inline void operator=(const Quaternion& other)
        {this->x = other.x; this->y = other.y; this->z = other.z; this->s = other.s;};
    
    void absolute();
    void negate();
    void conjugate();
    void normalize();
    bool epsilonEquals(const Quaternion& other, const double& epsilon);
    bool geometricallyEquals(const Quaternion& other, const double& epsilon);
    bool epsilonZero(const double& epsilon);

    bool containsNaN();

    template<typename dType>
    friend void multiplyImpl(dType q1x, dType q1y, dType q1z, dType q1s, bool conjugateQ1,
                  dType q2x, dType q2y, dType q2z, dType q2s, bool conjugateQ2,
                  Quaternion<dType>& store);

};

template<typename dataType>
Quaternion<dataType>::Quaternion(dataType _x, dataType _y, dataType _z, dataType _s)
{
    this->setUnsafe(_x,_y,_z,_s);
    this->normalize();
}
template<typename dataType>
Quaternion<dataType>::Quaternion(dataType _yaw, dataType _pitch, dataType _roll)
{
    // from inner2outer
    /** q = / sin(roll/2)/    /   0         /     /   0       /
     *      |   0       |  *  | sin(pitch/2)|  * |   0        |   
     *      |   0       |     |   0         |    | sin(yaw/2) |
     *      | cos(roll/2)|    | cos(pitch/2)|    | cos(yaw/2) | 
    */
    double cyaw = cos(double(_yaw/2));
    double cpit = cos(double(_pitch/2));
    double crol = cos(double(_roll/2));

    double syaw = sin(double(_yaw/2));
    double spit = sin(double(_pitch/2));
    double srol = sin(double(_roll/2));

// for (qroll*qpitch*qyaw)
//    this->x =  cyaw*cpit*srol + syaw*spit*crol;
//    this->y =  cyaw*spit*crol - syaw*cpit*srol;
//    this->z =  syaw*cpit*crol + cyaw*spit*srol;
//    this->s =  cyaw*cpit*crol - syaw*spit*srol;

// The multiply order is the same with Rotate Matrix!
// for(qyaw*qpitch*qroll) finally....
    this->x = cyaw*cpit*srol - syaw*spit*crol;
    this->y = cyaw*spit*crol + syaw*cpit*srol;
    this->z = syaw*cpit*crol - cyaw*spit*srol;
    this->s = cyaw*cpit*crol + syaw*spit*srol;

}

template<typename dataType>
dataType Quaternion<dataType>::getYaw() const
{
    return dataType(atan2(2*(this->x*this->y + this->z*this->s), 1.0-2.0*(this->y*this->y + this->z*this->z)));
}

template<typename dataType>
dataType Quaternion<dataType>::getPitch() const
{
    double pitch = 2.0*(this->s*this->y - this->x*this->z);
    if(pitch > 1.0)
        pitch = 1.0;
    if(pitch < -1.0)
        pitch = -1.0;
    
    return dataType(asin(pitch)); 
}

template<typename dataType>
dataType Quaternion<dataType>::getRoll() const
{
    return dataType(atan2(2.0*(this->z*this->y + this->x*this->s), 1.0-2.0*(this->y*this->y + this->x*this->x)));
}

template<typename dataType>
void Quaternion<dataType>::setYawPitchRoll(double _yaw, double _pitch, double _roll)
{
    double cyaw = cos(double(_yaw/2));
    double cpit = cos(double(_pitch/2));
    double crol = cos(double(_roll/2));

    double syaw = sin(double(_yaw/2));
    double spit = sin(double(_pitch/2));
    double srol = sin(double(_roll/2));

    this->x = cyaw*cpit*srol - syaw*spit*crol;
    this->y = cyaw*spit*crol + syaw*cpit*srol;
    this->z = syaw*cpit*crol - cyaw*spit*srol;
    this->s = cyaw*cpit*crol + syaw*spit*srol;
}



template<typename dataType>
void Quaternion<dataType>::absolute()
{
    this->setUnsafe(std::abs(this->getX()),std::abs(this->getY()),std::abs(this->getZ()),std::abs(this->getS()));
}

template<typename dataType>
void Quaternion<dataType>::negate()
{
    this->setUnsafe(-(this->getX()),-(this->getY()),-(this->getZ()),-(this->getS()));
}

/**
* Sets this quaternion to its conjugate.
*
* <pre>
*      / -qx /
* q* = | -qy |
*      | -qz |
*      /  qs /
* </pre>
*/
template<typename dataType>
void Quaternion<dataType>::conjugate()
{
    this->setUnsafe(-(this->getX()),-(this->getY()),-(this->getZ()), (this->getS()));
}

template<typename dataType>
void Quaternion<dataType>::normalize()
{
    if(this->containsNaN())
        return;
    
    double invNorm = sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->s * this->s);
    if(invNorm == dataType(0))
    {
        this->setUnsafe(dataType(0),dataType(0),dataType(0),dataType(1));
        return;
    }

    invNorm = dataType(1)/invNorm;
    this->x *= invNorm;
    this->y *= invNorm;
    this->z *= invNorm;
    this->s *= invNorm;
    //this->setUnsafe(this->getX()*)
}

template<typename dataType>
bool Quaternion<dataType>::epsilonEquals(const Quaternion& other, const double& epsilon)
{
    return( std::abs(this->getX()-other.getX()) <=epsilon &&
            std::abs(this->getY()-other.getY()) <=epsilon &&  
            std::abs(this->getZ()-other.getZ()) <=epsilon &&
            std::abs(this->getS()-other.getS()) <=epsilon );
}

template<typename dataType>
bool Quaternion<dataType>::geometricallyEquals(const Quaternion& other, const double& epsilon)
{
    double dx = this->getX()-other.getX();
    double dy = this->getY()-other.getY();
    double dz = this->getZ()-other.getZ();
    double ds = this->getS()-other.getS();

    return(sqrt(dx*dx+dy*dy+dz*dz+ds*ds)<=epsilon);
}


template<typename dataType>
bool Quaternion<dataType>::epsilonZero(const double& epsilon)
{
    return (std::abs(this->getX())<=epsilon &&
            std::abs(this->getY())<=epsilon &&
            std::abs(this->getZ())<=epsilon &&
            std::abs(this->getS()-dataType(1))<=epsilon);
}

template<typename dataType>
bool Quaternion<dataType>::containsNaN()
{
    return (std::isnan(this->getX()) ||
            std::isnan(this->getY()) ||
            std::isnan(this->getZ()) ||
            std::isnan(this->getS()));
}


template<typename dType>
void multiplyImpl(dType q1x, dType q1y, dType q1z, dType q1s, bool conjugateQ1,
                  dType q2x, dType q2y, dType q2z, dType q2s, bool conjugateQ2,
                  Quaternion<dType>& store)
{
    if(conjugateQ1)
    {
        q1x = -q1x;
        q1y = -q1y;
        q1z = -q1z;
    }

    if (conjugateQ2)
    {
        q2x = -q2x;
        q2y = -q2y;
        q2z = -q2z;
    }

    double x = q1s * q2x + q1x * q2s + q1y * q2z - q1z * q2y;
    double y = q1s * q2y - q1x * q2z + q1y * q2s + q1z * q2x;
    double z = q1s * q2z + q1x * q2y - q1y * q2x + q1z * q2s;
    double s = q1s * q2s - q1x * q2x - q1y * q2y - q1z * q2z;
    
    store.setUnsafe(x,y,z,s);
}



_LJH_EUCLID_LIB_END