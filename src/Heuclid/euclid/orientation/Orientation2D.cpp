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