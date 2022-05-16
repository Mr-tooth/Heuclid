#include <Heuclid\title\Title.h>
#include <Heuclid\geometry\ConvexPolygon2D.h>
#include <Heuclid\geometry\tools\HeuclidGeometryTools.h>

#define EDAGE_INDEX_OUT -1
#define NUM_INEQUAL_VERTEX -2
#define CHECK_CORRECT 0
_LJH_EUCLID_LIB_BEGIN
/**
 * This class provides a variety of tools to perform operations with polygons.
 *
 * @author Lai Junhang
 */
class HeuclidGeometryPolygonTools
{
private:
    Point2D<double> edgeStart;
    Point2D<double> edgeEnd;
    double dx;
    double dy;
    double edgeDirectionX;
    double edgeDirectionY;
    double crossProduct;

    HeuclidGeometryTools *heuclidGeometryTools;

public:
    const double EPSILON = 1.0e-7 ;
    bool isPoint2DInsideConvexPolygon2D(const ConvexPolygon2D& convexPolygon2D, const Point2D<double>& pointToCheck);

    int checkNumberOfVertices(const ConvexPolygon2D& convexPolygon2D);
    int checkEdgeOfIndex(const ConvexPolygon2D& convexPolygon2D, const int& edgeIndex);



};




_LJH_EUCLID_LIB_END