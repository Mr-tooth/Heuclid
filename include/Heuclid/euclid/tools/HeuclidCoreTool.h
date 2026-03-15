#pragma once
/**
 * @file HeuclidCoreTool.h
 * @brief Core utility functions for geometric computation.
 * @author Junhang Lai (赖俊杭)
 */
#include <cmath>
#include <Heuclid/title/Title.h>

_LJH_EUCLID_LIB_BEGIN

namespace HeuclidCoreTool
{
    double normSquared(double x, double y);
    double norm(double x, double y);
    double abs(double x);
    int abs(int x);
    double cos(double x);
    double sin(double x);
};


_LJH_EUCLID_LIB_END