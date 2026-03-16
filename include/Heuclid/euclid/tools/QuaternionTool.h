
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
 * @file QuaternionTool.h
 * @brief Quaternion utility functions (Euler conversion, etc.).
 * @author Junhang Lai (赖俊杭)
 */
#pragma once

#include <Heuclid/title/Title.h>
#include <Heuclid/euclid/tuple4D/Quaternion.h>
_LJH_EUCLID_LIB_BEGIN

/**
 * @name Quaternion multiplication functions
 * @brief Quaternion multiplication with optional conjugation.
 *
 * @tparam dataType The scalar type.
 * @param q1 First quaternion.
 * @param q2 Second quaternion.
 * @param store Output quaternion (q1 * q2 or conjugated variants).
 */
///@{

/** @brief Standard quaternion multiplication: store = q1 * q2. */
template<typename dataType>
void multiply(const Quaternion<dataType>& q1, const Quaternion<dataType>& q2,  Quaternion<dataType>& store)
{
    multiplyImpl<dataType>(q1,false,q2,false,store);
}

/** @brief Multiply with conjugated left: store = q1* * q2. */
template<typename dataType>
void multiplyConjugateLeft(const Quaternion<dataType>& q1, const Quaternion<dataType>& q2,  Quaternion<dataType>& store)
{
    multiplyImpl<dataType>(q1,true,q2,false,store);
}

/** @brief Multiply with conjugated right: store = q1 * q2*. */
template<typename dataType>
void multiplyConjugateRight(const Quaternion<dataType>& q1, const Quaternion<dataType>& q2,  Quaternion<dataType>& store)
{
    multiplyImpl<dataType>(q1,false,q2,true,store);
}

/** @brief Multiply with both conjugated: store = q1* * q2*. */
template<typename dataType>
void multiplyConjugateBoth(const Quaternion<dataType>& q1, const Quaternion<dataType>& q2,  Quaternion<dataType>& store)
{
    multiplyImpl<dataType>(q1,true,q2,true,store);
}
///@}

/** @brief Internal implementation of quaternion multiplication with conjugation flags. */
template<typename dataType>
void multiplyImpl(const Quaternion<dataType>& q1,bool conjugateQ1, const Quaternion<dataType>& q2, bool conjugateQ2, Quaternion<dataType>& store)
{
    multiplyImpl<dataType>(q1.getX(), q1.getY(), q1.getZ(), q1.getS(), conjugateQ1,
                 q2.getX(), q2.getY(), q2.getZ(), q2.getS(), conjugateQ2, store);
}

// template<typename dataType>
// void multiplyImpl(dataType q1x, dataType q1y, dataType q1z, dataType q1s, bool conjugateQ1,
//                   dataType q2x, dataType q2y, dataType q2z, dataType q2s, bool conjugateQ2,
//                   const Quaternion<dataType>& store)
// {
//     if(conjugateQ1)
//     {
//         q1x = -q1x;
//         q1y = -q1y;
//         q1z = -q1z;
//     }

//     if (conjugateQ2)
//     {
//         q2x = -q2x;
//         q2y = -q2y;
//         q2z = -q2z;
//     }

//     double x = q1s * q2x + q1x * q2s + q1y * q2z - q1z * q2y;
//     double y = q1s * q2y - q1x * q2z + q1y * q2s + q1z * q2x;
//     double z = q1s * q2z + q1x * q2y - q1y * q2x + q1z * q2s;
//     double s = q1s * q2s - q1x * q2x - q1y * q2y - q1z * q2z;
    
//     store.setUnsafe(x,y,z,s);
// }

_LJH_EUCLID_LIB_END