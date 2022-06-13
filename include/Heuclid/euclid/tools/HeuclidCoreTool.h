#pragma once
#include <cmath>
#include <Heuclid/title/Title.h>

_LJH_EUCLID_LIB_BEGIN

class HeuclidCoreTool
{
public:
    double normSquared(double x, double y);
    double norm(double x, double y);
    double abs(double x);
    int abs(int x);
    double cos(double x);
    double sin(double x);
};


_LJH_EUCLID_LIB_END