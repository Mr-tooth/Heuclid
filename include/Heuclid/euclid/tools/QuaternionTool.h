
#pragma once

#include <Heuclid/title/Title.h>
#include <Heuclid/euclid/tuple4D/Quaternion.h>
_LJH_EUCLID_LIB_BEGIN


template<typename dataType>
void multiply(const Quaternion<dataType>& q1, const Quaternion<dataType>& q2,  Quaternion<dataType>& store)
{
    multiplyImpl<dataType>(q1,false,q2,false,store);
}

template<typename dataType>
void multiplyConjugateLeft(const Quaternion<dataType>& q1, const Quaternion<dataType>& q2,  Quaternion<dataType>& store)
{
    multiplyImpl<dataType>(q1,true,q2,false,store);
}

template<typename dataType>
void multiplyConjugateRight(const Quaternion<dataType>& q1, const Quaternion<dataType>& q2,  Quaternion<dataType>& store)
{
    multiplyImpl<dataType>(q1,false,q2,true,store);
}

template<typename dataType>
void multiplyConjugateBoth(const Quaternion<dataType>& q1, const Quaternion<dataType>& q2,  Quaternion<dataType>& store)
{
    multiplyImpl<dataType>(q1,true,q2,true,store);
}





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