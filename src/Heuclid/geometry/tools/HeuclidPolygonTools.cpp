// Copyright 2024-2026 Junhang Lai (赖俊杭)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

    if(this->heuclidGeometryTools.isPoint2DOnSideOfLine2D(pointX,pointY,this->edgeStart,this->edgeEnd,clockwiseOrdered))
        return false;
    
    for (int index = 1;index < numOfVertices;index++)
    {
        this->edgeStart = this->edgeEnd;
        this->edgeEnd = (index+1)<numOfVertices?vertexBuffer.at(index+1):vertexBuffer.at(0);
        if(this->heuclidGeometryTools.isPoint2DOnSideOfLine2D(pointX,pointY,this->edgeStart,this->edgeEnd,clockwiseOrdered))
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

int HeuclidGeometryPolygonTools::checkNumberOfVertices(std::vector<Point2D<double> > Buffer, int _numOfVertices)
{
    if(_numOfVertices < 0 || _numOfVertices>Buffer.size())
        return NUM_INEQUAL_VERTEX;
    return CHECK_CORRECT;
}

int HeuclidGeometryPolygonTools::checkEdgeOfIndex(int edgeIndex, int _numOfVertices)
{
    if(edgeIndex<0||edgeIndex>=_numOfVertices)
        return EDAGE_INDEX_OUT;
    return CHECK_CORRECT;
}

bool HeuclidGeometryPolygonTools::isConvexPolygonContained(const ConvexPolygon2D& polyA, const ConvexPolygon2D& polyB)
{
    const std::vector<Point2D<double>> verticesA = polyA.getVertexBuffer();
    const std::vector<Point2D<double>> verticesB = polyB.getVertexBuffer();
    const int nA = polyA.getNumOfVertices();
    const int nB = polyB.getNumOfVertices();
    const bool cwB = polyB.getClockwiseOrder();

    if(nA == 0 || nB == 0)
        return false;

    // All vertices of A must be inside B
    for(int i = 0; i < nA; i++)
    {
        if(!this->isPoint2DInsideConvexPolygon2D(verticesA.at(i).getX(), verticesA.at(i).getY(), verticesB, nB, cwB))
            return false;
    }
    return true;
}

bool HeuclidGeometryPolygonTools::isConvexPolygonIntersect(const ConvexPolygon2D& polyA, const ConvexPolygon2D& polyB)
{
    const std::vector<Point2D<double>> verticesA = polyA.getVertexBuffer();
    const std::vector<Point2D<double>> verticesB = polyB.getVertexBuffer();
    const int nA = polyA.getNumOfVertices();
    const int nB = polyB.getNumOfVertices();
    const bool cwA = polyA.getClockwiseOrder();
    const bool cwB = polyB.getClockwiseOrder();

    if(nA == 0 || nB == 0)
        return false;

    // Check if any vertex of A is inside B
    for(int i = 0; i < nA; i++)
    {
        if(this->isPoint2DInsideConvexPolygon2D(verticesA.at(i).getX(), verticesA.at(i).getY(), verticesB, nB, cwB))
            return true;
    }

    // Check edge midpoints of A against B (catches edge crossing without vertex containment)
    for(int i = 0; i < nA; i++)
    {
        int j = (i + 1) % nA;
        double mx = 0.5 * (verticesA.at(i).getX() + verticesA.at(j).getX());
        double my = 0.5 * (verticesA.at(i).getY() + verticesA.at(j).getY());
        if(this->isPoint2DInsideConvexPolygon2D(mx, my, verticesB, nB, cwB))
            return true;
    }

    // Check if any vertex of B is inside A
    for(int i = 0; i < nB; i++)
    {
        if(this->isPoint2DInsideConvexPolygon2D(verticesB.at(i).getX(), verticesB.at(i).getY(), verticesA, nA, cwA))
            return true;
    }

    // Check edge midpoints of B against A
    for(int i = 0; i < nB; i++)
    {
        int j = (i + 1) % nB;
        double mx = 0.5 * (verticesB.at(i).getX() + verticesB.at(j).getX());
        double my = 0.5 * (verticesB.at(i).getY() + verticesB.at(j).getY());
        if(this->isPoint2DInsideConvexPolygon2D(mx, my, verticesA, nA, cwA))
            return true;
    }

    return false;
}
_LJH_EUCLID_LIB_END