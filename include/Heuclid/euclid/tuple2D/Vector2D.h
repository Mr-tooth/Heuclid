/**
 * @file Vector2D.h
 * @brief 2D vector with arithmetic operations.
 * @author Junhang Lai (赖俊杭)
 */

#pragma once
#ifndef __VECTOR__2D__
#define __VECTOR__2D__

#define _LJH_EUCLID_LIB_BEGIN namespace ljh{namespace heuclid{
#define _LJH_EUCLID_LIB_END }}

_LJH_EUCLID_LIB_BEGIN

/**
 * @brief A 2D vector representing magnitude and direction on the XY-plane.
 *
 * @tparam dataType The scalar type (e.g., double, float).
 *
 * Can represent physical quantities such as velocity, force, or displacement
 * in 2D space.
 */
template<typename dataType>
class Vector2D
{
public:
    /** @brief Default constructor. Initializes to zero vector. */
    Vector2D():x(dataType(0)),y(dataType(0)){};

    /** @brief Construct from x and y components. */
    Vector2D(dataType _x, dataType _y):x(_x),y(_y){};

    /** @brief Copy constructor. */
    Vector2D(const Vector2D& other):x(other.x),y(other.y){};

    /** @name Getters */
    ///@{
    dataType getX() const {return this->x;};
    dataType getY() const {return this->y;};
    ///@}

    /** @name Setters */
    ///@{
    void setX(const dataType& _x){if(this->x!=_x) this->x = _x;};
    void setY(const dataType& _y){if(this->y!=_y) this->y = _y;};
    ///@}

    /** @brief Equality comparison. */
    bool operator==(const Vector2D& other) const
    {return (this->x == other.x&&this->y==other.y);};

private:
    dataType x; ///< X component
    dataType y; ///< Y component
};

_LJH_EUCLID_LIB_END

#endif
