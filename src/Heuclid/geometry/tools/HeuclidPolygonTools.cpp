
#include <Heuclid\geometry\tools\HeuclidPolygonTools.h>

_LJH_EUCLID_LIB_BEGIN

   /**
    * Determines if the point is inside the convex polygon given the tolerance {@code epsilon}.
    * <p>
    * WARNING: This method assumes that the given vertices already form a convex polygon.
    * </p>
    * <p>
    * Edge cases:
    * <ul>
    * <li>if {@code numberOfVertices == 0}, this method returns {@code false}.
    * <li>if {@code numberOfVertices == 1}, this method returns whether the query and the single vertex
    * are exactly equal.
    * <li>if {@code numberOfVertices == 2}, this method returns whether the query is exactly on the
    * polygon single edge.
    * <li>if the query is exactly equal to one of the polygon vertices, this method returns
    * {@code true}.
    * <li>if the query is exactly on one of the polygon's edges, the intent for this method is to
    * return {@code true} but this scenario is highly sensitive to numerical error.
    * </ul>
    *
    * @param pointToCheck     the 2D Point need to check whether in the polygon.
    * @param convexPolygon2D  the class containing in {@code numberOfVertices} {@code vertexBuffer} {@code clockwiseOrdered} the num of/the vertices of the
    *                         convex polygon. Not modified.
    * 
    * @return {@code true} if the query is considered to be inside the polygon, {@code false}
    *         otherwise.
    * 
    */
bool HeuclidGeometryPolygonTools::isPoint2DInsideConvexPolygon2D(const ConvexPolygon2D& convexPolygon2D, const Point2D<double>& pointToCheck)
{
    if(this->checkNumberOfVertices(convexPolygon2D))
        return false; // TODO modify it to throw abnormal
    
    if(convexPolygon2D.numOfVertices == 0)
        return false;
    
    if(convexPolygon2D.numOfVertices == 1)
    {
        if(pointToCheck.epsilonEquals(convexPolygon2D.vertexBuffer.at(0),this->EPSILON))
            return true;
    }

    this->edgeStart = convexPolygon2D.vertexBuffer.at(0);
    this->edgeEnd = convexPolygon2D.vertexBuffer.at(1);

    if(convexPolygon2D.numOfVertices == 2)
    {
        // Quick check with the end-points
        if(pointToCheck.epsilonEquals(this->edgeStart,this->EPSILON))
            return true;
        if(pointToCheck.epsilonEquals(this->edgeEnd,this->EPSILON))
            return true;

        // Check first that the point is inside the bounding box containing the edge.
        
        if(edgeStart.getX() < edgeEnd.getX())
        {
            if (pointToCheck.getX() < edgeStart.getX() || pointToCheck.getX() > edgeEnd.getX())
               return false;
        }
        else
        {
            if (pointToCheck.getX() > edgeStart.getX() || pointToCheck.getX() < edgeEnd.getX())
                return false;
        }

        if(edgeStart.getY() < edgeEnd.getY())
        {
            if (pointToCheck.getY() < edgeStart.getY() || pointToCheck.getY() > edgeEnd.getY())
               return false;
        }
        else
        {
            if (pointToCheck.getY() > edgeStart.getY() || pointToCheck.getY() < edgeEnd.getY())
                return false;
        }

        this->dx = pointToCheck.getX() - this->edgeStart.getX();
        this->dy = pointToCheck.getY() - this->edgeStart.getY();

        this->edgeDirectionX = this->edgeEnd.getX() - this->edgeStart.getX();
        this->edgeDirectionY = this->edgeEnd.getY() - this->edgeStart.getY();
        // 
        this->crossProduct = edgeDirectionX*dy - dx*edgeDirectionY;                                      
        return this->crossProduct == 0.0;
    }

    if(heuclidGeometryTools->isPoint2DOnSideOfLine2D(pointToCheck,edgeStart,edgeEnd,convexPolygon2D.clockwiseOrdered))
        return false;
    
    for(int index = 1;index < convexPolygon2D.numOfVertices;index++)
    {
        edgeStart = edgeEnd;
        edgeEnd = ((index+1)<convexPolygon2D.numOfVertices)?convexPolygon2D.vertexBuffer.at(index+1):convexPolygon2D.vertexBuffer.at(0) ;
        if(heuclidGeometryTools->isPoint2DOnSideOfLine2D(pointToCheck,edgeStart,edgeEnd,convexPolygon2D.clockwiseOrdered))
            return false;
    }

    return true;


}

int HeuclidGeometryPolygonTools::checkNumberOfVertices(const ConvexPolygon2D& convexPolygon2D)
{
    if(convexPolygon2D.numOfVertices<0||convexPolygon2D.numOfVertices>convexPolygon2D.vertexBuffer.size())
        return NUM_INEQUAL_VERTEX;
    return CHECK_CORRECT;
}

int HeuclidGeometryPolygonTools::checkEdgeOfIndex(const ConvexPolygon2D& convexPolygon2D, const int& edgeIndex)
{
    if(edgeIndex<0||edgeIndex>=convexPolygon2D.numOfVertices)
        return EDAGE_INDEX_OUT;
    return CHECK_CORRECT;
}


_LJH_EUCLID_LIB_END