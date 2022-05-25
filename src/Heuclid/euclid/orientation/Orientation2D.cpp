
#include <Heuclid/euclid/orientation/Orientation2D.h>

_LJH_EUCLID_LIB_BEGIN

void Orientation2D::setYaw(const double& _yaw)
{
    this->yaw = this->shiftProperYaw(_yaw);
}

bool Orientation2D::epsilonEquals(const Orientation2D& other, const double& epsilon) const
{
    return (std::abs(this->getYaw()-other.getYaw())<=epsilon);
    //return (std::abs(this->yaw-other.yaw)<=epsilon);
}

bool Orientation2D::geometricallyEquals(const Orientation2D& other, const double& epsilon)
{
    double Yaw1 = this->shiftProperYaw(this->getYaw());
    double Yaw2 = this->shiftProperYaw(other.getYaw());
    
    return (std::abs(Yaw1-Yaw2)<=epsilon || (2*pi_o-std::abs(Yaw1-Yaw2))<=epsilon);
}

double Orientation2D::shiftProperYaw(double _yaw)
{
    if(_yaw>2*pi_o)
    {
        int num = int(_yaw/(2*pi_o));
        _yaw = _yaw - num*2*pi_o;
    }
    else if(_yaw<-2*pi_o)
    {
        int num = int(_yaw/(2*pi_o));
        _yaw = _yaw + num*2*pi_o;
    }
        
    if(_yaw>pi_o && _yaw<=2*pi_o)
        _yaw -= 2*pi_o;
    else if(_yaw>=-2*pi_o && _yaw<-pi_o)
        _yaw += 2*pi_o;

    return _yaw;
}

bool Orientation2D::epsilonZero(const double& epsilon)
{
    return (this->getYaw()<=epsilon);
}

_LJH_EUCLID_LIB_END