#include <Heuclid/geometry/tools/HeuclidGeometryTools.h>

_LJH_EUCLID_LIB_BEGIN

/**
    * Returns a boolean value, stating whether a 2D point is on the left or right side of an infinitely
    * long line. The idea of "side" is determined based on the direction of the line.
    * <p>
    * For instance, given the {@code lineDirection} components x = 0, and y = 1, and the
    * {@code pointOnLine} coordinates x = 0, and y = 0, a point located on:
    * <ul>
    * <li>the left side of this line has a negative x coordinate.
    * <li>the right side of this line has a positive x coordinate.
    * </ul>
    * </p>
    * This method will return {@code false} if the point is on the line.
    *
    * @param pointX         the x-coordinate of the query point.
    * @param pointY         the y-coordinate of the query point.
    * @param pointOnLineX   the x-coordinate of a point positioned on the infinite line.
    * @param pointOnLineY   the y-coordinate of a point positioned on the infinite line.
    * @param lineDirectionX the x-component of the direction of the infinite line.
    * @param lineDirectionY the y-component of the direction of the infinite line.
    * @param testLeftSide   the query of the side, when equal to {@code true} this will test for the
    *                       left side, {@code false} this will test for the right side.
    * @return {@code true} if the point is on the query side of the line, {@code false} if the point is
    *         on the opposite side or exactly on the line.
    */
bool HeuclidGeometryTools::isPoint2DOnSideOfLine2D(double pointX, double pointY, 
                                 double pointOnLineX, double pointOnLineY, 
                                 double lineDirectionX, double lineDirectionY,
                                 bool testLeftSide)
{
    this->dx = pointX-pointOnLineX;
    this->dy = pointY-pointOnLineY;
    this->crossProduct = lineDirectionX*dy - lineDirectionY*dx;
    if(testLeftSide)
        return this->crossProduct>0.0;
    else
        return this->crossProduct<0.0;
}

   /**
    * Returns a boolean value, stating whether a 2D point is on the left or right side of an infinitely
    * long line defined by two points. The idea of "side" is determined based on order of
    * {@code firstPointOnLine} and {@code secondPointOnLine}.
    * <p>
    * For instance, given the {@code firstPointOnLine} coordinates x = 0, and y = 0, and the
    * {@code secondPointOnLine} coordinates x = 0, y = 1, a point located on:
    * <ul>
    * <li>the left side of this line has a negative x coordinate.
    * <li>the right side of this line has a positive x coordinate.
    * </ul>
    * </p>
    * This method will return {@code false} if the point is on the line.
    *
    * @param pointX            the x-coordinate of the query point.
    * @param pointY            the y-coordinate of the query point.
    * @param firstPointOnLine  a first point located on the line. Not modified.
    * @param secondPointOnLine a second point located on the line. Not modified.
    * @param testLeftSide      the query of the side, when equal to {@code true} this will test for the
    *                          left side, {@code false} this will test for the right side.
    * @return {@code true} if the point is on the query side of the line, {@code false} if the point is
    *         on the opposite side or exactly on the line.
    */
bool HeuclidGeometryTools::isPoint2DOnSideOfLine2D(double pointX, double pointY, 
                                Point2D<double> firstPointOnLine,
                                Point2D<double> secondPointOnLine,
                                bool testLeftSide)
{
    this->pointOnLineX = firstPointOnLine.getX();
    this->pointOnLineY = firstPointOnLine.getY();

    this->lineDirectionX = secondPointOnLine.getX()-firstPointOnLine.getX();
    this->lineDirectionY = secondPointOnLine.getY()-firstPointOnLine.getY();

    return this->isPoint2DOnSideOfLine2D(pointX,pointY,this->pointOnLineX,this->pointOnLineY,this->lineDirectionX,this->lineDirectionY,testLeftSide);
}                                

   /**
    * Returns a boolean value, stating whether a 2D point is on the left or right side of an infinitely
    * long line. The idea of "side" is determined based on the direction of the line.
    * <p>
    * For instance, given the {@code lineDirection} components x = 0, and y = 1, and the
    * {@code pointOnLine} coordinates x = 0, and y = 0, a point located on:
    * <ul>
    * <li>the left side of this line has a negative x coordinate.
    * <li>the right side of this line has a positive x coordinate.
    * </ul>
    * </p>
    * This method will return {@code false} if the point is on the line.
    *
    * @param pointX        the x-coordinate of the query point.
    * @param pointY        the y-coordinate of the query point.
    * @param pointOnLine   a point positioned on the infinite line. Not modified.
    * @param lineDirection the direction of the infinite line. Not modified.
    * @param testLeftSide  the query of the side, when equal to {@code true} this will test for the
    *                      left side, {@code false} this will test for the right side.
    * @return {@code true} if the point is on the query side of the line, {@code false} if the point is
    *         on the opposite side or exactly on the line.
    */
bool HeuclidGeometryTools::isPoint2DOnSideOfLine2D(double pointX, double pointY, 
                                Point2D<double> pointOnLine,
                                Vector2D<double> lineDirection,
                                bool testLeftSide)
{
    this->pointOnLineX = pointOnLine.getX();
    this->pointOnLineY = pointOnLine.getY();

    this->lineDirectionX = lineDirection.getX();
    this->lineDirectionY = lineDirection.getY();

    return this->isPoint2DOnSideOfLine2D(pointX,pointY,this->pointOnLineX,this->pointOnLineY,this->lineDirectionX,this->lineDirectionY,testLeftSide);
}                                

   /**
    * Returns a boolean value, stating whether a 2D point is on the left or right side of an infinitely
    * long line defined by two points. The idea of "side" is determined based on order of
    * {@code firstPointOnLine} and {@code secondPointOnLine}.
    * <p>
    * For instance, given the {@code firstPointOnLine} coordinates x = 0, and y = 0, and the
    * {@code secondPointOnLine} coordinates x = 0, y = 1, a point located on:
    * <ul>
    * <li>the left side of this line has a negative x coordinate.
    * <li>the right side of this line has a positive x coordinate.
    * </ul>
    * </p>
    * This method will return {@code false} if the point is on the line.
    *
    * @param point             the query point. Not modified.
    * @param firstPointOnLine  a first point located on the line. Not modified.
    * @param secondPointOnLine a second point located on the line. Not modified.
    * @param testLeftSide      the query of the side, when equal to {@code true} this will test for the
    *                          left side, {@code false} this will test for the right side.
    * @return {@code true} if the point is on the query side of the line, {@code false} if the point is
    *         on the opposite side or exactly on the line.
    */
bool HeuclidGeometryTools::isPoint2DOnSideOfLine2D(Point2D<double> point, 
                                Point2D<double> firstPointOnLine,
                                Point2D<double> secondPointOnLine,
                                bool testLeftSide)
{
    return this->isPoint2DOnSideOfLine2D(point.getX(),point.getY(),firstPointOnLine,secondPointOnLine,testLeftSide);
}                                

   /**
    * Returns a boolean value, stating whether a 2D point is on the left or right side of an infinitely
    * long line. The idea of "side" is determined based on the direction of the line.
    * <p>
    * For instance, given the {@code lineDirection} components x = 0, and y = 1, and the
    * {@code pointOnLine} coordinates x = 0, and y = 0, a point located on:
    * <ul>
    * <li>the left side of this line has a negative x coordinate.
    * <li>the right side of this line has a positive x coordinate.
    * </ul>
    * </p>
    * This method will return {@code false} if the point is on the line.
    *
    * @param point         the query point. Not modified.
    * @param pointOnLine   a point positioned on the infinite line. Not modified.
    * @param lineDirection the direction of the infinite line. Not modified.
    * @param testLeftSide  the query of the side, when equal to {@code true} this will test for the
    *                      left side, {@code false} this will test for the right side.
    * @return {@code true} if the point is on the query side of the line, {@code false} if the point is
    *         on the opposite side or exactly on the line.
    */
bool HeuclidGeometryTools::isPoint2DOnSideOfLine2D(Point2D<double> point, 
                                Point2D<double> pointOnLine,
                                Vector2D<double> lineDirection,
                                bool testLeftSide)
{
    return this->isPoint2DOnSideOfLine2D(point.getX(),point.getY(),pointOnLine,lineDirection,testLeftSide);
}        


/**
 * @brief Tests if the two given vectors are parallel given a tolerance on the angle between the two vector
 * axes in the range ]0; pi/2[. This method returns {@code true} if the two vectors are
 * parallel, whether they are pointing in the same direction or in opposite directions.
 * 
 * @param firstVectorX x-component of the first vector. Not modified.
 * @param firstVectorY y-component of the first vector. Not modified.
 * @param isFirstVectorUnitary clarify whether the firstVector is UnitVector.
 * @param secondVectorX x-component of the second vector. Not modified.
 * @param secondVectorY y-component of the second vector. Not modified.
 * @param isSecondVectorUnitary clarify whether the secondVector is UnitVector.
 * @param angleEpsilon tolerance on the angle in radians.
 * @return true if the two vector is parallel
 * @return false otherwise
 */
bool HeuclidGeometryTools::areVector2DsParallel(double firstVectorX, double firstVectorY, bool isFirstVectorUnitary,
                              double secondVectorX, double secondVectorY, bool isSecondVectorUnitary,
                              double angleEpsilon)
{
    
    assert(angleEpsilon<0.0 || angleEpsilon>this->HALF_PI);
    if(angleEpsilon<0.0 || angleEpsilon>this->HALF_PI)
        throw "The angleEpsilon input of function HeuclidGeometryTools::areVector2DsParallel is not right";

    double firstVectorLength = isFirstVectorUnitary? 1.0: this->coreTool.norm(firstVectorX,firstVectorY);
    if(firstVectorLength<this->ONE_TEN_MILLIONTH)
        return false;
    double secondVectorLength = isSecondVectorUnitary? 1.0: this->coreTool.norm(secondVectorX,secondVectorY);
    if(secondVectorLength<this->ONE_TEN_MILLIONTH)
        return false;
    
    double dot = firstVectorX * secondVectorX + firstVectorY * secondVectorY;

    return this->coreTool.abs(dot/(firstVectorLength * secondVectorLength)) > this->coreTool.cos(angleEpsilon);
}

/**
 * @brief Tests if the two given vectors are parallel given a tolerance on the angle between the two vector
 * axes in the range ]0; pi/2[. This method returns {@code true} if the two vectors are
 * parallel, whether they are pointing in the same direction or in opposite directions.
 * 
 * @param firstVectorX x-component of the first vector. Not modified.
 * @param firstVectorY y-component of the first vector. Not modified.
 * @param secondVectorX x-component of the second vector. Not modified.
 * @param secondVectorY y-component of the second vector. Not modified.
 * @param angleEpsilon tolerance on the angle in radians.
 * @return true if the two vector is parallel
 * @return false otherwise
 */
bool HeuclidGeometryTools::areVector2DsParallel(double firstVectorX, double firstVectorY, 
                                                double secondVectorX, double secondVectorY, 
                                                double angleEpsilon)
{
    return this->areVector2DsParallel(firstVectorX,firstVectorY,false,secondVectorX,secondVectorY,false,angleEpsilon);
}

/**
 * @brief Tests if the two given vectors are parallel given a tolerance on the angle between the two vector
 * axes in the range ]0; pi/2[. This method returns {@code true} if the two vectors are
 * parallel, whether they are pointing in the same direction or in opposite directions. 
 * 
 * @param firstVector  the first vector. Not modified.
 * @param secondVector the second vector. Not modified.
 * @param angleEpsilon tolerance on the angle in radians.
 * @return {@code true} if the two vectors are parallel, {@code false} otherwise.
 */
bool HeuclidGeometryTools::areVector2DsParallel(Vector2D<double> firstVector, Vector2D<double> secondVector, double angleEpsilon)
{
    return this->areVector2DsParallel(firstVector.getX(),firstVector.getY(),
                                      secondVector.getX(),secondVector.getY(),
                                      angleEpsilon);
}

/**
 * @brief Tests if the two given vectors are parallel given a tolerance on the angle between the two vector
 * axes in the range ]0; pi/2[. This method returns {@code true} if the two vectors are
 * parallel, whether they are pointing in the same direction or in opposite directions. 
 * 
 * @param firstVector  the first unit vector. Not modified.
 * @param secondVector the second unit vector. Not modified.
 * @param angleEpsilon tolerance on the angle in radians.
 * @return {@code true} if the two vectors are parallel, {@code false} otherwise.
 */
bool HeuclidGeometryTools::areVector2DsParallel(UnitVector2D<double> firstVector, UnitVector2D<double> secondVector, double angleEpsilon)
{
    if(firstVector.isDirty())
        firstVector.normalize();
    if(secondVector.isDirty())
        secondVector.normalize();
    
    return this->areVector2DsParallel(firstVector.getRawX(),firstVector.getRawY(),true,
                                    secondVector.getRawX(),secondVector.getRawY(),true,
                                    angleEpsilon);
}


/**
 * Returns the minimum signed distance between a 2D point and an infinitely long 2D line defined by
 * a point and a direction.
 * 
 * The calculated distance is negative if the query is located on the right side of the line.
 * 
 * Edge cases:
 * 
 * if {@code lineDirection.length() < }{@value #ONE_TRILLIONTH}, this method returns the
 * distance between {@code pointOnLine} and the given {@code point}.
 * 
 * 
 *
 * @param pointX         x-coordinate of the query.
 * @param pointY         y-coordinate of the query.
 * @param pointOnLineX   x-coordinate of a point located on the line.
 * @param pointOnLineY   y-coordinate of a point located on the line.
 * @param lineDirectionX x-component of the line direction.
 * @param lineDirectionY y-component of the line direction.
 * @param isDirectionUnitary whether the direction is unit
 * @return the minimum distance between the 2D point and the 2D line. The distance is negative if
 *         the query is located on the right side of the line.
 */
double HeuclidGeometryTools::signedDistanceFromPoint2DToLine2D(double pointX, double pointY,
                                            double pointOnLineX, double pointOnLineY,
                                            double lineDirectionX, double lineDirectionY,
                                            bool isDirectionUnitary)
{
    
    double dx = pointX - pointOnLineX;
    double dy = pointY - pointOnLineY;
    double directionMagnitude = isDirectionUnitary? 1.0:this->coreTool.norm(lineDirectionX,lineDirectionY);
    
    // deteriorate to distance to two points
    if(directionMagnitude < this->ONE_TRILLIONTH)
        return coreTool.norm(dx,dy);
    else
        return (lineDirectionX * dy - dx * lineDirectionY)/directionMagnitude ;

    // ly/lx(x-x0) = y-y0;
    // distance = abs(A*x1 + B*y1 + C)/sqrt(A^2 + B^2);
}                                            

/**
 * Returns the minimum signed distance between a 2D point and an infinitely long 2D line defined by
 * a point and a direction.
 * 
 * The calculated distance is negative if the query is located on the right side of the line.
 * 
 * Edge cases:
 * 
 * if {@code lineDirection.length() < }{@value #ONE_TRILLIONTH}, this method returns the
 * distance between {@code pointOnLine} and the given {@code point}.
 * 
 * 
 *
 * @param pointX         x-coordinate of the query.
 * @param pointY         y-coordinate of the query.
 * @param pointOnLineX   x-coordinate of a point located on the line.
 * @param pointOnLineY   y-coordinate of a point located on the line.
 * @param lineDirectionX x-component of the line direction.
 * @param lineDirectionY y-component of the line direction.
 * @return the minimum distance between the 2D point and the 2D line. The distance is negative if
 *         the query is located on the right side of the line.
 */
double HeuclidGeometryTools::signedDistanceFromPoint2DToLine2D(double pointX, double pointY,
                                            double pointOnLineX, double pointOnLineY,
                                            double lineDirectionX, double lineDirectionY)
{
    return this->signedDistanceFromPoint2DToLine2D(pointX,pointY,pointOnLineX,pointOnLineY,lineDirectionX,lineDirectionY,false);
}

/**
 * @brief Returns the minimum signed distance between a 2D point and an infinitely long 2D line defined by
 * a point and a direction.
 * 
 * The calculated distance is negative if the query is located on the right side of the line.
 * Edge cases:
 *
 * if {@code firstPointOnLine.distance(secondPointOnLine) < }{@value #ONE_TRILLIONTH}, this
 * method returns the distance between {@code firstPointOnLine} and the given {@code point}.
 * 
 * @param point         the point of the query.
 * @param pointOnLine   a point located on the line
 * @param lineDirection the line direction vector
 * @return the minimum distance between the 2D point and the 2D line. The distance is negative if
 *         the query is located on the right side of the line.
 */
double HeuclidGeometryTools::signedDistanceFromPoint2DToLine2D(Point2D<double> point, Point2D<double> pointOnLine,
                                             Vector2D<double> lineDirection)
{
    return this->signedDistanceFromPoint2DToLine2D(point.getX(),point.getY(),
                                                   pointOnLine.getX(),pointOnLine.getY(),
                                                   lineDirection.getX(),lineDirection.getY());                                               
}   

/**
 * Returns the minimum signed distance between a 2D point and an infinitely long 2D line defined by
 * a point and a direction.
 * <p>
 * The calculated distance is negative if the query is located on the right side of the line.
 * </p>
 * <p>
 * Edge cases:
 * <ul>
 * <li>if {@code firstPointOnLine.distance(secondPointOnLine) < }{@value #ONE_TRILLIONTH}, this
 * method returns the distance between {@code firstPointOnLine} and the given {@code point}.
 * </ul>
 * </p>
 *
 * @param point      the point of the query.
 * @param firstPoint  a first point located on the line. Not modified.
 * @param secondPoint a second point located on the line. Not modified.
 * @return the minimum distance between the 2D point and the 2D line. The distance is negative if
 *         the query is located on the right side of the line.
 */
double HeuclidGeometryTools::signedDistanceFromPoint2DToLine2D(Point2D<double> point, Point2D<double> firstPoint, 
                                             Point2D<double> secondPoint)
{
    return this->signedDistanceFromPoint2DToLine2D(point.getX(),point.getY(),
                                                firstPoint.getX(),firstPoint.getY(),
                                                secondPoint.getX()-firstPoint.getX(),
                                                secondPoint.getY()-firstPoint.getY());
}     



double HeuclidGeometryTools::distanceFromPoint2DToLine2D(double pointX, double pointY,
                                            double pointOnLineX, double pointOnLineY,
                                            double lineDirectionX, double lineDirectionY,
                                            bool isDirectionUnitary)
{
    return this->coreTool.abs(this->signedDistanceFromPoint2DToLine2D(pointX,pointY,
                                                                      pointOnLineX,pointOnLineY,  
                                                                      lineDirectionX,lineDirectionY,
                                                                      isDirectionUnitary));
}     

/**
 * Returns the minimum distance between a 2D point and an infinitely long 2D line defined by a point
 * and a direction.
 * 
 * Edge cases:
 * 
 * if {@code lineDirection.length() < }{@value #ONE_TRILLIONTH}, this method returns the
 * distance between {@code pointOnLine} and the given {@code point}.
 * 
 *
 * @param pointX         x-coordinate of the query.
 * @param pointY         y-coordinate of the query.
 * @param pointOnLineX   x-coordinate of a point located on the line.
 * @param pointOnLineY   y-coordinate of a point located on the line.
 * @param lineDirectionX x-component of the line direction.
 * @param lineDirectionY y-component of the line direction.
 * @return the minimum distance between the 2D point and the 2D line.
 */
double HeuclidGeometryTools::distanceFromPoint2DToLine2D(double pointX, double pointY,
                                        double pointOnLineX, double pointOnLineY,
                                        double lineDirectionX, double lineDirectionY)
{
    return this->distanceFromPoint2DToLine2D(pointX,pointY,
                                             pointOnLineX,pointOnLineY,  
                                             lineDirectionX,lineDirectionY,
                                             false);
}   

/**
 * Returns the minimum distance between a 2D point and an infinitely long 2D line defined by a point
 * and a direction.
 * 
 * Edge cases:
 * 
 * if {@code lineDirection.length() < }{@value #ONE_TRILLIONTH}, this method returns the
 * distance between {@code pointOnLine} and the given {@code point}.
 *
 *
 * @param point         2D point to compute the distance from the line. Not modified.
 * @param pointOnLine   a point located on the line. Not modified.
 * @param lineDirection the direction of the line. Not modified.
 * @return the minimum distance between the 2D point and the 2D line.
 */
double HeuclidGeometryTools::distanceFromPoint2DToLine2D(Point2D<double> point, Point2D<double> pointOnLine,
                                       Vector2D<double> lineDirection)
{
    return this->distanceFromPoint2DToLine2D(point.getX(),point.getY(),
                                             pointOnLine.getX(),pointOnLine.getY(),
                                             lineDirection.getX(),lineDirection.getY());
}                                       


/**
 * Returns the minimum distance between a 2D point and an infinitely long 2D line defined by two
 * points.
 * 
 * Edge cases:
 * 
 * if {@code firstPointOnLine.distance(secondPointOnLine) < }{@value #ONE_TRILLIONTH}, this
 * method returns the distance between {@code firstPointOnLine} and the given {@code point}.
 * 
 *
 * @param point             2D point to compute the distance from the line. Not modified.
 * @param firstPointOnLine  a first point located on the line. Not modified.
 * @param secondPointOnLine a second point located on the line. Not modified.
 * @return the minimum distance between the 2D point and the 2D line.
 */
double HeuclidGeometryTools::distanceFromPoint2DToLine2D(Point2D<double> point, Point2D<double> firstPointOnLine, 
                                   Point2D<double> secondPointOnLine)
{
    return this->distanceFromPoint2DToLine2D(point.getX(),point.getY(),
                                             firstPointOnLine.getX(),firstPointOnLine.getY(),
                                             secondPointOnLine.getX()-firstPointOnLine.getX(),
                                             secondPointOnLine.getY()-firstPointOnLine.getY());
}  



/**
 * Tests if the two given lines are collinear given a tolerance on the angle between in the range
 * ]0; <i>pi</i>/2[. This method returns {@code true} if the two lines are collinear, whether they
 * are pointing in the same direction or in opposite directions.
 *
 * Edge cases:
 * 
 * if the direction magnitude of either line is below {@link #ONE_TEN_MILLIONTH}, this method
 * fails and returns {@code false}.
 * 
 *
 * @param pointOnLine1x   x-coordinate of a point located on the first line.
 * @param pointOnLine1y   y-coordinate of a point located on the first line.
 * @param lineDirection1x x-component of the first line direction.
 * @param lineDirection1y y-component of the first line direction.
 * @param pointOnLine2x   x-coordinate of a point located on the second line.
 * @param pointOnLine2y   y-coordinate of a point located on the second line.
 * @param lineDirection2x x-component of the second line direction.
 * @param lineDirection2y y-component of the second line direction.
 * @param angleEpsilon    tolerance on the angle in radians.
 * @param distanceEpsilon tolerance on the distance to determine if {@code pointOnLine2} belongs to
 *                        the first line segment.
 * @return {@code true} if the two line segments are collinear, {@code false} otherwise.
 * @throws  if angleEpsilon out of [0; pi/2]
 */
bool HeuclidGeometryTools::areLine2DsCollinear(double pointOnLine1x,double pointOnLine1y,
                               double lineDirection1x,double lineDirection1y,
                               double pointOnLine2x,double pointOnLine2y,
                               double lineDirection2x,double lineDirection2y,
                               double angleEpsilon,double distanceEpsilon)
{
    return this->areLine2DsCollinear(pointOnLine1x,pointOnLine1y,
                                    lineDirection1x,lineDirection1y,
                                    false,
                                    pointOnLine2x,pointOnLine2y,
                                    lineDirection2x,lineDirection2y,
                                    false,
                                    angleEpsilon,distanceEpsilon);
}                               

bool HeuclidGeometryTools::areLine2DsCollinear(double pointOnLine1x,double pointOnLine1y,
                               double lineDirection1x,double lineDirection1y,
                               bool   isDirection1Unitary,
                               double pointOnLine2x,double pointOnLine2y,
                               double lineDirection2x,double lineDirection2y,
                               bool   isDirection2Unitary,
                               double angleEpsilon,double distanceEpsilon)
{
    if(!this->areVector2DsParallel(lineDirection1x,lineDirection1y,isDirection1Unitary,lineDirection2x,lineDirection2y,isDirection2Unitary,angleEpsilon))
        return false;
    
    double distance = this->distanceFromPoint2DToLine2D(pointOnLine2x,pointOnLine2y,
                                                        pointOnLine1x,pointOnLine1y,
                                                        lineDirection1x,lineDirection1y,
                                                        isDirection1Unitary);
    return distance < distanceEpsilon;
}                               

/**
 * Tests if the two given lines are collinear given a tolerance on the angle between in the range
 * ]0; <i>pi</i>/2[. This method returns {@code true} if the two lines are collinear, whether they
 * are pointing in the same direction or in opposite directions.
 * 
 * Edge cases:
 * 
 * if the direction magnitude of either line is below {@link #ONE_TEN_MILLIONTH}, this method
 * fails and returns {@code false}.
 * 
 *
 * @param firstPointOnLine1  a first point located on the first line. Not modified.
 * @param secondPointOnLine1 a second point located on the first line. Not modified.
 * @param firstPointOnLine2  a first point located on the second line. Not modified.
 * @param secondPointOnLine2 a second point located on the second line. Not modified.
 * @param angleEpsilon       tolerance on the angle in radians.
 * @param distanceEpsilon    tolerance on the distance to determine if {@code firstPointOnLine2}
 *                           belongs to the first line segment.
 * @return {@code true} if the two line segments are collinear, {@code false} otherwise.
 * @throws  if angleEpsilon out of [0; pi/2]
 */
bool HeuclidGeometryTools::areLine2DsCollinear(Point2D<double> firstPointOnLine1, Point2D<double> secondPointOnLine1,
                             Point2D<double> firstPointOnLine2, Point2D<double> secondPointOnLine2,
                             double angleEpsilon, double distanceEpsilon)
{
    return this->areLine2DsCollinear(firstPointOnLine1.getX(),firstPointOnLine1.getY(),
                                     secondPointOnLine1.getX()-firstPointOnLine1.getX(),
                                     secondPointOnLine1.getY()-firstPointOnLine1.getY(),
                                     firstPointOnLine2.getX(),firstPointOnLine2.getY(),
                                     secondPointOnLine2.getX()-firstPointOnLine2.getX(),
                                     secondPointOnLine2.getY()-firstPointOnLine2.getY(),
                                     angleEpsilon,distanceEpsilon);
}                             

/**
 * Tests if the two given lines are collinear given a tolerance on the angle between in the range
 * ]0; <i>pi</i>/2[. This method returns {@code true} if the two lines are collinear, whether they
 * are pointing in the same direction or in opposite directions.
 *
 * Edge cases:
 *
 *if the direction magnitude of either line is below {@link #ONE_TEN_MILLIONTH}, this method
 * fails and returns {@code false}.
 * 
 *
 * @param pointOnLine1    point located on the first line. Not modified.
 * @param lineDirection1  the first line direction. Not modified.
 * @param pointOnLine2    point located on the second line. Not modified.
 * @param lineDirection2  the second line direction. Not modified.
 * @param angleEpsilon    tolerance on the angle in radians.
 * @param distanceEpsilon tolerance on the distance to determine if {@code pointOnLine2} belongs to
 *                        the first line segment.
 * @return {@code true} if the two line segments are collinear, {@code false} otherwise.
 * @throws if angleEpsilon out of [0; pi/2]
 */                            
bool HeuclidGeometryTools::areLine2DsCollinear(Point2D<double> pointOnLine1, Vector2D<double> lineDirection1,
                            Point2D<double> pointOnLine2, Vector2D<double> lineDirection2,
                            double angleEpsilon, double distanceEpsilon)
{
    return this->areLine2DsCollinear(pointOnLine1.getX(),pointOnLine1.getY(),
                                     lineDirection1.getX(),lineDirection1.getY(),
                                     pointOnLine2.getX(),pointOnLine2.getY(),
                                     lineDirection2.getX(),lineDirection2.getY(),
                                     angleEpsilon,distanceEpsilon);
}                            
_LJH_EUCLID_LIB_END