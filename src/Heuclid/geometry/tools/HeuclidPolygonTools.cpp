
#include <Heuclid/geometry/tools/HeuclidPolygonTools.h>

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
    * @param pointX           the x-coordinate of the query.
    * @param pointY           the y-coordinate of the query.
    * @param vertexBuffer     the vector containing in {@code numberOfVertices} the vertices of the
    *                         convex polygon. Not modified.
    * @param numberOfVertices the number of vertices that belong to the convex polygon.
    * @param clockwiseOrdered whether the vertices are clockwise or counter-clockwise ordered.
    * @return {@code true} if the query is considered to be inside the polygon, {@code false}
    *         otherwise.
    * 
    */
bool HeuclidGeometryPolygonTools::isPoint2DInsideConvexPolygon2D(double pointX, double pointY, std::vector<Point2D<double> > vertexBuffer,
                                                                int numOfVertices, bool clockwiseOrdered)
{
    if(numOfVertices == 0)
        return false;
    
    if(numOfVertices == 1)
    {
        this->edgeStart = vertexBuffer.at(0);
        return (std::abs(pointX-this->edgeStart.getX()) < this->EPSILON &&
                std::abs(pointY-this->edgeStart.getY()) < this->EPSILON );
    }
    
    this->edgeStart = vertexBuffer.at(0);
    this->edgeEnd = vertexBuffer.at(1);
    if(numOfVertices == 2)
    {
        // Quick check with the end-points
        if(std::abs(pointX-this->edgeStart.getX()) < this->EPSILON &&
            std::abs(pointY-this->edgeStart.getY()) < this->EPSILON )
            return true;
        if(std::abs(pointX-this->edgeEnd.getX()) < this->EPSILON &&
            std::abs(pointY-this->edgeEnd.getY()) < this->EPSILON )
            return true;
        
        // Check first that the point is inside the bounding box containing the edge.
        if(this->edgeStart.getX() < this->edgeEnd.getX())
        {
            if (pointX < edgeStart.getX() || pointX > edgeEnd.getX())
               return false;
        }
        else
        {
            if (pointX > edgeStart.getX() || pointX < edgeEnd.getX())
                return false;
        }

        if(this->edgeStart.getY() < this->edgeEnd.getY())
        {
            if (pointY < edgeStart.getY() || pointY > edgeEnd.getY())
               return false;
        }
        else
        {
            if (pointY > edgeStart.getY() || pointY < edgeEnd.getY())
                return false;
        }

        this->dx = pointX - this->edgeStart.getX();
        this->dy = pointY - this->edgeStart.getY();

        this->edgeDirectionX = this->edgeEnd.getX() - this->edgeStart.getX();
        this->edgeDirectionY = this->edgeEnd.getY() - this->edgeStart.getY();

        this->crossProduct = edgeDirectionX*dy - dx*edgeDirectionY;                                      
        return std::abs(this->crossProduct) < this->EPSILON;
    }

    if(heuclidGeometryTools.isPoint2DOnSideOfLine2D(pointX,pointY,this->edgeStart,this->edgeEnd,clockwiseOrdered))
        return false;
    
    for (int index = 1;index < numOfVertices;index++)
    {
        this->edgeStart = this->edgeEnd;
        this->edgeEnd = (index+1)<numOfVertices?vertexBuffer.at(index+1):vertexBuffer.at(0);
        if(heuclidGeometryTools.isPoint2DOnSideOfLine2D(pointX,pointY,this->edgeStart,this->edgeEnd,clockwiseOrdered))
            return false;
    }

    return true;

    

}


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
    return this->isPoint2DInsideConvexPolygon2D(pointToCheck.getX(),pointToCheck.getY(),convexPolygon2D.getVertexBuffer(),convexPolygon2D.getNumOfVertices(),convexPolygon2D.getClockwiseOrder());
}




// int HeuclidGeometryPolygonTools::checkNumberOfVertices(const ConvexPolygon2D& convexPolygon2D)
// {
//     if(convexPolygon2D.numOfVertices<0||convexPolygon2D.numOfVertices>convexPolygon2D.vertexBuffer.size())
//         return NUM_INEQUAL_VERTEX;
//     return CHECK_CORRECT;
// }

// int HeuclidGeometryPolygonTools::checkEdgeOfIndex(const ConvexPolygon2D& convexPolygon2D, const int& edgeIndex)
// {
//     if(edgeIndex<0||edgeIndex>=convexPolygon2D.numOfVertices)
//         return EDAGE_INDEX_OUT;
//     return CHECK_CORRECT;
// }
int checkNumberOfVertices(std::vector<Point2D<double> > Buffer, int _numOfVertices)
{
    if(_numOfVertices < 0 || _numOfVertices>Buffer.size())
        return NUM_INEQUAL_VERTEX;
    return CHECK_CORRECT;
}

int checkEdgeOfIndex(int edgeIndex, int _numOfVertices)
{
    if(edgeIndex<0||edgeIndex>=_numOfVertices)
        return EDAGE_INDEX_OUT;
    return CHECK_CORRECT;
}
_LJH_EUCLID_LIB_END