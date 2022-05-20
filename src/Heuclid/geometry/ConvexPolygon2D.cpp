#include <Heuclid/geometry/ConvexPolygon2D.h>
_LJH_EUCLID_LIB_BEGIN

void ConvexPolygon2D::setVertexBuffer(std::vector<Point2D<double> > buffer)
{
    this->vertexBuffer = buffer;
}

_LJH_EUCLID_LIB_END