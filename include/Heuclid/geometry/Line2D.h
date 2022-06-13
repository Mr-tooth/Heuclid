#include <Heuclid/title/Title.h>
#include <Heuclid/euclid/tuple2D/Point2D.h>
#include <Heuclid/euclid/tuple2D/UnitVector2D.h>
#include <Heuclid/euclid/tuple2D/Vector2D.h>

#include <Heuclid/euclid/tools/HeuclidCoreTool.h>
#include <cassert>

_LJH_EUCLID_LIB_BEGIN

class Line2D
{
private:
    Point2D<double> point;
    UnitVector2D<double> direction;
public:
    Line2D():point(),direction(){};
    Line2D(double pointOnLineX, double pointOnLineY, double lineDirectionX, double lineDirectionY);
    Line2D(const Line2D& other);
    Line2D(Point2D<double> firstPointOnLine, Point2D<double> secondPointOnLine);
    Line2D(Point2D<double> pointOnLine, Vector2D<double>  lineDirection);


    void setLine2D(const Line2D& other);
    void setPoint(Point2D<double>& other);
    void setDirection(UnitVector2D<double>& other);
    void setDirection(Vector2D<double>& other);

    UnitVector2D<double> getDirection();
    Point2D<double> getPoint();

    bool geometricallyEquals(const Line2D& other, double epsilon);
    bool epsilonEquals(const Line2D& other, double epsilon);
};




_LJH_EUCLID_LIB_END