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
#include <Heuclid/title/Title.h>
/**
 * @file HeuclidPolygonTools.h
 * @brief Polygon utility functions.
 * @author Junhang Lai (赖俊杭)
 */
#include <Heuclid/geometry/ConvexPolygon2D.h>
#include <Heuclid/geometry/tools/HeuclidGeometryTools.h>

#define EDAGE_INDEX_OUT -1
#define NUM_INEQUAL_VERTEX -2
#define CHECK_CORRECT 0
_LJH_EUCLID_LIB_BEGIN

/**
 * @brief Static utility functions for polygon operations.
 *
 * Provides edge intersection checks, point-in-polygon tests, and other
 * polygon-specific geometric predicates.
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

    HeuclidGeometryTools heuclidGeometryTools;

public:
    const double EPSILON = 1.0e-7 ;

    HeuclidGeometryPolygonTools():edgeStart(),edgeEnd(),dx(0.0),dy(0.0),edgeDirectionX(0.0),edgeDirectionY(0.0),crossProduct(0.0),heuclidGeometryTools(){};
    bool isPoint2DInsideConvexPolygon2D(const ConvexPolygon2D& convexPolygon2D, const Point2D<double>& pointToCheck);
    bool isPoint2DInsideConvexPolygon2D(double pointX, double pointY, std::vector<Point2D<double> > vertexBuffer,
                                        int numOfVertices, bool clockwiseOrdered);


    int checkNumberOfVertices(std::vector<Point2D<double> > Buffer, int _numOfVertices);
    int checkEdgeOfIndex(int edgeIndex, int _numOfVertices);

    /**
     * @brief Check if two convex polygons overlap or intersect.
     *
     * Uses mutual vertex-in-polygon + edge-midpoint-in-polygon tests
     * to detect any geometric overlap between the two convex polygons.
     * If no vertex of either polygon is inside the other and no edge
     * midpoints overlap, the polygons are disjoint.
     *
     * @param polyA first convex polygon
     * @param polyB second convex polygon
     * @return true if the two polygons overlap (intersect), false if disjoint
     */
    bool isConvexPolygonIntersect(const ConvexPolygon2D& polyA, const ConvexPolygon2D& polyB);

    /**
     * @brief Check if polyA is fully contained within polyB.
     *
     * For convex polygons, containment is verified by checking that all
     * vertices of polyA are inside polyB. This correctly rejects cases where
     * polyA straddles polyB's boundary or extends outside polyB.
     *
     * @param polyA the candidate contained polygon
     * @param polyB the containing polygon
     * @return true if polyA ⊆ polyB (all vertices of A are inside B)
     */
    bool isConvexPolygonContained(const ConvexPolygon2D& polyA, const ConvexPolygon2D& polyB);
    // int checkNumberOfVertices(const ConvexPolygon2D& convexPolygon2D);
    // int checkEdgeOfIndex(const ConvexPolygon2D& convexPolygon2D, const int& edgeIndex);



};




_LJH_EUCLID_LIB_END