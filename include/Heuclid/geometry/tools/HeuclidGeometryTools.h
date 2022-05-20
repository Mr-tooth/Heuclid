#pragma once
#include <Heuclid/title/Title.h>
#include <Heuclid/euclid/tuple2D/Point2D.h>
#include <Heuclid/euclid/tuple2D/Vector2D.h>

_LJH_EUCLID_LIB_BEGIN
class HeuclidGeometryTools
{
private:
    // for isPoint2DOnSideOfLine2D
    double dx;
    double dy;
    double crossProduct;
    double pointOnLineX;
    double pointOnLineY;
    double lineDirectionX;
    double lineDirectionY;

public:
    HeuclidGeometryTools():dx(0.0),dy(0.0),crossProduct(0.0),pointOnLineX(0.0),
                        pointOnLineY(0.0),lineDirectionX(0.0),lineDirectionY(0.0){};

    bool isPoint2DOnSideOfLine2D(double pointX, double pointY, 
                                 double pointOnLineX, double pointOnLineY, 
                                 double lineDirectionX, double lineDirectionY,
                                 bool testLeftSide);

    bool isPoint2DOnSideOfLine2D(double pointX, double pointY, 
                                 Point2D<double> firstPointOnLine,
                                 Point2D<double> secondPointOnLine,
                                 bool testLeftSide);

    bool isPoint2DOnSideOfLine2D(double pointX, double pointY, 
                                 Point2D<double> pointOnLine,
                                 Vector2D<double> lineDirection,
                                 bool testLeftSide);

    bool isPoint2DOnSideOfLine2D(Point2D<double> point, 
                                 Point2D<double> firstPointOnLine,
                                 Point2D<double> secondPointOnLine,
                                 bool testLeftSide);

    bool isPoint2DOnSideOfLine2D(Point2D<double> point, 
                                 Point2D<double> pointOnLine,
                                 Vector2D<double> lineDirection,
                                 bool testLeftSide);
    
};


_LJH_EUCLID_LIB_END