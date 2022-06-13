#include <Heuclid/euclid/tools/HeuclidCoreTool.h>

_LJH_EUCLID_LIB_BEGIN
double HeuclidCoreTool::normSquared(double x, double y)
{
    return (x*x + y*y);
}

double HeuclidCoreTool::norm(double x, double y)
{
    return std::sqrt(x*x + y*y);
}

double HeuclidCoreTool::abs(double x)
{
    return std::abs(x);
}

int HeuclidCoreTool::abs(int x)
{
    return std::abs(x);
}

double HeuclidCoreTool::cos(double x)
{
    return std::cos(x);
}

double HeuclidCoreTool::sin(double x)
{
    return std::sin(x);
}

_LJH_EUCLID_LIB_END