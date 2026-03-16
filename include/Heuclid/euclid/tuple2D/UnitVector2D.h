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
 * @file UnitVector2D.h
 * @brief 2D unit vector with automatic normalization.
 * @author Junhang Lai (赖俊杭)
 */

#pragma once
#ifndef __UNIT__VECTOR__2D__
#define __UNIT__VECTOR__2D__

#include <cmath>
#include <Heuclid/euclid/interfaces/ZeroTestEpsilon.h>

#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace heuclid{
#define _LJH_EUCLID_LIB_END }}

_LJH_EUCLID_LIB_BEGIN

/**
 * @brief A 2D unit-length vector with lazy normalization.
 *
 * @tparam dataType The scalar type (e.g., double, float).
 *
 * Shares the same API as Vector2D while ensuring unit length.
 * Uses a dirty flag for lazy normalization — the vector is only
 * normalized when components are accessed (getX/getY).
 *
 * When set to zero, the next normalization resets to (1, 0).
 */
template<typename dataType>
class UnitVector2D
{
public:
    /** @brief Default constructor. Initializes to (1, 0) — the X-axis unit vector. */
    UnitVector2D():x(dataType(1)),y(dataType(0)),dirty(true){};

    /** @brief Construct from components. Will be normalized on first access. */
    UnitVector2D(dataType _x, dataType _y):x(_x),y(_y),dirty(true){};

    /** @brief Copy constructor. */
    UnitVector2D(const UnitVector2D& other);

    /** @brief Set all components to absolute values. */
    inline void absolute(){this->x = std::abs(this->x);this->y = std::abs(this->y);};

    /** @brief Negate the vector direction. */
    inline void negate(){this->x = - this->x;this->y = - this->y;};

    /** @brief Force normalization. Resets to (1,0) if currently zero. */
    void normalize();

    /** @brief Equality comparison. */
    bool operator==(const UnitVector2D& other) const
    {return (this->x==other.x&&this->y=other.y);};

    /** @brief Check if components are within epsilon of zero. */
    bool equals(const dataType& epsl) const
    {return (std::abs(this->x) <= epsl && std::abs(this->y) <= epsl);};

    /** @brief Mark vector as needing re-normalization. */
    inline void markAsDirty() {this->dirty = true;};

    /** @brief Check if vector needs re-normalization. */
    inline bool isDirty() const {return this->dirty;};

    /** @brief Set X component (marks dirty). */
    void setX(dataType _x);

    /** @brief Set Y component (marks dirty). */
    void setY(dataType _y);

    /** @brief Get raw X component without normalization. */
    dataType getRawX() const {return this->x;};

    /** @brief Get raw Y component without normalization. */
    dataType getRawY() const {return this->y;};

    /**
     * @brief Check equality within epsilon tolerance.
     * @param other The vector to compare.
     * @param epsilon The tolerance threshold.
     * @return True if both components differ by less than epsilon.
     */
    bool epsilonEquals(const UnitVector2D<dataType>& other, double epsilon);

private:
    bool dirty;    ///< Whether normalization is needed
    dataType x;    ///< X component
    dataType y;    ///< Y component
};

template<typename dataType>
UnitVector2D<dataType>::UnitVector2D(const UnitVector2D& other)
{
    this->x = other.x;
    this->y = other.y;
    this->dirty = other.dirty;
}

template<typename dataType>
void UnitVector2D<dataType>::normalize()
{
    if(dirty)
    {
        if(this->equals(dataType(ZERO_TEST_EPSILON)))
        {
            this->x = dataType(1);
            this->y = dataType(0);
        }
        else
        {
            dataType norminverse = dataType(1)/sqrt(this->x * this->x + this->y * this->y);
            x *= norminverse;
            y *= norminverse;
        }
        dirty = false;
    }
}

template<typename dataType>
void UnitVector2D<dataType>::setX(dataType _x)
{
    if(this->x != _x)
    {
        this->x = _x;
        markAsDirty();
    }
}

template<typename dataType>
void UnitVector2D<dataType>::setY(dataType _y)
{
    if(this->y != _y)
    {
        this->y = _y;
        markAsDirty();
    }
}

template<typename dataType>
bool UnitVector2D<dataType>:: epsilonEquals(const UnitVector2D<dataType>& other, double epsilon)
{
    return (std::abs(this->getRawX()-other.getRawX())<epsilon && std::abs(this->getRawY()-other.getRawY())<epsilon);
}

_LJH_EUCLID_LIB_END

#endif
