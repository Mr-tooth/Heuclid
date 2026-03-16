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
    // int checkNumberOfVertices(const ConvexPolygon2D& convexPolygon2D);
    // int checkEdgeOfIndex(const ConvexPolygon2D& convexPolygon2D, const int& edgeIndex);



};




_LJH_EUCLID_LIB_END