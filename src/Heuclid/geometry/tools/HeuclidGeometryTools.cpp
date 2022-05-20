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






_LJH_EUCLID_LIB_END