#include <Heuclid/euclid/tools/HeuclidCoreTool.h>

_LJH_EUCLID_LIB_BEGIN
double HeuclidCoreTool::normSquared(double x, double y)
{
    return (x*x + y*y);
}

double HeuclidCoreTool::norm(double x, double y)
{
    return sqrt(x*x + y*y);
}


_LJH_EUCLID_LIB_END