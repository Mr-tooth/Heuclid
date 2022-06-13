#include <Heuclid/geometry/Line2D.h>

_LJH_EUCLID_LIB_BEGIN

Line2D::Line2D(double pointOnLineX, double pointOnLineY, double lineDirectionX, double lineDirectionY)
{
    this->point.setX(pointOnLineX);
    this->point.setY(pointOnLineY);
    this->direction.setX(lineDirectionX);
    this->direction.setY(lineDirectionY);
}

Line2D::Line2D(const Line2D& other)
{
    this->point = other.point;
    this->direction = other.direction;
}

Line2D::Line2D(Point2D<double> firstPointOnLine, Point2D<double> secondPointOnLine)
{
    assert(firstPointOnLine.epsilonEquals(secondPointOnLine,1e-6));

    this->point = firstPointOnLine;
    this->direction = UnitVector2D<double>(secondPointOnLine.getX()-firstPointOnLine.getX(),
                                           secondPointOnLine.getY()-firstPointOnLine.getY());
}

Line2D::Line2D(Point2D<double> pointOnLine, Vector2D<double>  lineDirection)
{
    this->point = pointOnLine;
    this->direction.setX(lineDirection.getX());
    this->direction.setY(lineDirection.getY());
}

void Line2D::setLine2D(const Line2D& other)
{
    this->point = other.point;
    this->direction = other.direction;
}

void Line2D::setPoint(Point2D<double>& other)
{
    this->point = other;
}

void Line2D::setDirection(UnitVector2D<double>& other)
{
    this->direction = other;
}

void Line2D::setDirection(Vector2D<double>& other)
{
    this->direction.setX(other.getX());
    this->direction.setY(other.getY());
}

UnitVector2D<double> Line2D::getDirection()
{
    return this->direction;
}
   
Point2D<double> Line2D::getPoint()
{
    return this->point;
}

/**
 * @brief Compare this to other to determine if the two lines are geometrically similiar.
 * 
 * Two lines are considered geometrically equal is they are collinear, pointing toward the same or
 * opposite direction.
 * 
 * @param other the query to compare
 * @param epsilon the tolerance to use
 * @return true if collinear
 * @return false otherwise
 */
bool Line2D::geometricallyEquals(const Line2D& other, double epsilon)
{
    HeuclidCoreTool tools;
    // check if parallel
    if (tools.abs(other.direction.getRawX()*this->direction.getRawY()-other.direction.getRawY()*this->direction.getRawX())>epsilon)
        return false;

    // check if collinear
    else if(tools.abs((other.point.getX()-this->point.getX())*this->direction.getRawY()-
                      (other.point.getY()-this->point.getY())*this->direction.getRawX())>epsilon)
        return false;
    else
        return true;

}

 /**
* Tests on a per-component basis on the point and vector if this line is equal to {@code other}
* with the tolerance {@code epsilon}. This method will return {@code false} if the two lines are
* physically the same but either the point or vector of each line is different. For instance, if
* {@code this.point == other.point} and {@code this.direction == - other.direction}, the two lines
* are physically the same but this method returns {@code false}.
*
* @param other   the query. Not modified.
* @param epsilon the tolerance to use.
* @return {@code true} if the two lines are equal, {@code false} otherwise.
*/
bool Line2D::epsilonEquals(const Line2D& other, double epsilon)
{
    return (this->point.epsilonEquals(other.point,epsilon)&&
             this->direction.epsilonEquals(other.direction,epsilon));
}
_LJH_EUCLID_LIB_END

