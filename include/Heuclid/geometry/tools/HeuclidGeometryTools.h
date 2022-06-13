#pragma once
#include <Heuclid/title/Title.h>
#include <Heuclid/euclid/tuple2D/Point2D.h>
#include <Heuclid/euclid/tuple2D/Vector2D.h>
#include <Heuclid/euclid/tuple2D/UnitVector2D.h>

#include <Heuclid/euclid/tools/HeuclidCoreTool.h>
#include <cassert>

#ifndef PI
#define PI 3.1415926535
#endif

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
    // Tolerance used to identify edge cases
    const double ONE_MILLIONTH = 1.0e-6;
    const double ONE_TEN_MILLIONTH = 1.0e-7;
    const double ONE_TRILLIONTH = 1.0e-12;
    const double IS_POINT_ON_LINE_EPS = 1.0e-8;
    const double HALF_PI = 0.5 * PI;
    //ToUse CoreTool more conveniently
    HeuclidCoreTool coreTool;
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
    

    bool areVector2DsParallel(double firstVectorX, double firstVectorY, bool isFirstVectorUnitary,
                              double secondVectorX, double secondVectorY, bool isSecondVectorUnitary,
                              double angleEpsilon);
    bool areVector2DsParallel(double firstVectorX, double firstVectorY, 
                              double secondVectorX, double secondVectorY, 
                              double angleEpsilon);
    bool areVector2DsParallel(Vector2D<double> firstVector, Vector2D<double> secondVector, double angleEpsilon);  
    bool areVector2DsParallel(UnitVector2D<double> firstVector, UnitVector2D<double> secondVector, double angleEpsilon);       


    double signedDistanceFromPoint2DToLine2D(double pointX, double pointY,
                                            double pointOnLineX, double pointOnLineY,
                                            double lineDirectionX, double lineDirectionY,
                                            bool isDirectionUnitary);
    double signedDistanceFromPoint2DToLine2D(double pointX, double pointY,
                                            double pointOnLineX, double pointOnLineY,
                                            double lineDirectionX, double lineDirectionY);  

    double signedDistanceFromPoint2DToLine2D(Point2D<double> point, Point2D<double> pointOnLine,
                                             Vector2D<double> lineDirection);

    double signedDistanceFromPoint2DToLine2D(Point2D<double> point, Point2D<double> firstPoint, 
                                             Point2D<double> secondPoint);

    double distanceFromPoint2DToLine2D(double pointX, double pointY,
                                        double pointOnLineX, double pointOnLineY,
                                        double lineDirectionX, double lineDirectionY,
                                        bool isDirectionUnitary);  
    double distanceFromPoint2DToLine2D(double pointX, double pointY,
                                        double pointOnLineX, double pointOnLineY,
                                        double lineDirectionX, double lineDirectionY); 
    double distanceFromPoint2DToLine2D(Point2D<double> point, Point2D<double> pointOnLine,
                                       Vector2D<double> lineDirection);

    double distanceFromPoint2DToLine2D(Point2D<double> point, Point2D<double> firstPointOnLine, 
                                       Point2D<double> secondPointOnLine);                                                                           




    bool areLine2DsCollinear(double pointOnLine1x,double pointOnLine1y,
                               double lineDirection1x,double lineDirection1y,
                               bool   isDirection1Unitary,
                               double pointOnLine2x,double pointOnLine2y,
                               double lineDirection2x,double lineDirection2y,
                               bool   isDirection2Unitary,
                               double angleEpsilon,double distanceEpsilon);

    bool areLine2DsCollinear(double pointOnLine1x,double pointOnLine1y,
                               double lineDirection1x,double lineDirection1y,
                               double pointOnLine2x,double pointOnLine2y,
                               double lineDirection2x,double lineDirection2y,
                               double angleEpsilon,double distanceEpsilon);                               

    bool areLine2DsCollinear(Point2D<double> firstPointOnLine1, Point2D<double> secondPointOnLine1,
                             Point2D<double> firstPointOnLine2, Point2D<double> secondPointOnLine2,
                             double angleEpsilon, double distanceEpsilon);
                             
    bool areLine2DsCollinear(Point2D<double> pointOnLine1, Vector2D<double> lineDirection1,
                             Point2D<double> pointOnLine2, Vector2D<double> lineDirection2,
                             double angleEpsilon, double distanceEpsilon);                             
};


_LJH_EUCLID_LIB_END