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
 * @file UnitVector3D.h
 * @brief 3D unit vector with automatic normalization.
 * @author Junhang Lai (赖俊杭)
 */
#ifndef __UNIT__VECTOR__3D__
#define __UNIT__VECTOR__3D__

#include <cmath>
#include <Heuclid/euclid/interfaces/ZeroTestEpsilon.h>
#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace heuclid{
#define _LJH_EUCLID_LIB_END }}

_LJH_EUCLID_LIB_BEGIN

/**
 * @brief A 3D unit-length vector with lazy normalization.
 *
 * @tparam dataType The scalar type (e.g., double, float).
 *
 * Same as UnitVector2D but in 3D. When set to zero, the next normalization
 * resets to (1, 0, 0).
 */
template<typename dataType>
class UnitVector3D
{
public:
    UnitVector3D():x(dataType(0)),y(dataType(0)),z(dataType(0)),dirty(true){};
    UnitVector3D(dataType _x, dataType _y, dataType _z):x(_x),y(_y),z(_z),dirty(true){};
    UnitVector3D(const UnitVector3D& other):x(other.x),y(other.y),z(other.z),dirty(other.dirty){};

    inline void absolute(){this->x = std::abs(this->x);
                           this->y = std::abs(this->y);
                           this->z = std::abs(this->z);};

    inline void negate(){this->x = - this->x;
                         this->y = - this->y;
                         this->z = - this->z;};
    
    void normalize();
    // bool operator==(const dataType& epsl) const 
    // {return (this->x == epsl && this->y == epsl && this->z == epsl);};

    bool operator==(const UnitVector3D& other) const
    {return (this->x==other.x && this->y=other.y && this->z=other.z);};

    bool equals(const dataType& epsl) const
    {return (std::abs(this->x) <= epsl && std::abs(this->y) <= epsl && std::abs(this->z) <= epsl);};

    inline void markAsDirty() {this->dirty = true;};
    inline bool isDirty() const {return this->dirty;};

    void setX(dataType _x);
    void setY(dataType _y);
    void setZ(dataType _z);
    dataType getRawX() const {return this->x;};
    dataType getRawY() const {return this->y;};
    dataType getRawZ() const {return this->z;};

private:
    bool dirty;
    dataType x;
    dataType y;
    dataType z;
};

template<typename dataType>
void UnitVector3D<dataType>::normalize()
{
    if(dirty)
    {
        if(this->equals(dataType(ZERO_TEST_EPSILON)))
        {
            this->x = dataType(1);
            this->y = dataType(0);
            this->z = dataType(0);
        }
        else
        {
            dataType norminverse = dataType(1)/sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
            x *= norminverse;
            y *= norminverse;
            z *= norminverse;
        }
        dirty = false;
    }
}

template<typename dataType>
void UnitVector3D<dataType>::setX(dataType _x)
{
    if(this->x != _x)
    {
        this->x = _x;
        markAsDirty();
    }   
}

template<typename dataType>
void UnitVector3D<dataType>::setY(dataType _y)
{
    if(this->y != _y)
    {
        this->y = _y;
        markAsDirty();
    }   
}

template<typename dataType>
void UnitVector3D<dataType>::setZ(dataType _z)
{
    if(this->z != _z)
    {
        this->z = _z;
        markAsDirty();
    }   
}

_LJH_EUCLID_LIB_END

#endif