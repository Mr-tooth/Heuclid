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
#include <gtest/gtest.h>
#include <Heuclid/geometry/ConvexPolygon2D.h>
#include <Heuclid/geometry/tools/HeuclidPolygonTools.h>

using namespace ljh::heuclid;

// Helper: build a ConvexPolygon2D from a list of points
static ConvexPolygon2D makePoly(const std::vector<Point2D<double>>& pts, bool cw = true)
{
    ConvexPolygon2D poly((int)pts.size());
    poly.setVertexBuffer(pts);
    poly.setClockwiseOrder(cw);
    return poly;
}

// Helper: axis-aligned rectangle
static ConvexPolygon2D makeRect(double x, double y, double w, double h)
{
    // Clockwise: top-left, top-right, bottom-right, bottom-left
    std::vector<Point2D<double>> v;
    v.push_back(Point2D<double>(x,   y+h));
    v.push_back(Point2D<double>(x+w, y+h));
    v.push_back(Point2D<double>(x+w, y  ));
    v.push_back(Point2D<double>(x,   y  ));
    return makePoly(v, true);
}

// ============================================================================
// isConvexPolygonContained tests
// ============================================================================

TEST(ConvexPolygonContained, SmallRectInsideLargeRect)
{
    HeuclidGeometryPolygonTools tools;
    auto large = makeRect(0, 0, 10, 10);
    auto small = makeRect(2, 2, 3, 3);
    EXPECT_TRUE(tools.isConvexPolygonContained(small, large));
}

TEST(ConvexPolygonContained, IdenticalRectangles)
{
    HeuclidGeometryPolygonTools tools;
    auto a = makeRect(0, 0, 5, 5);
    auto b = makeRect(0, 0, 5, 5);
    EXPECT_TRUE(tools.isConvexPolygonContained(a, b));
}

TEST(ConvexPolygonContained, VertexOnBoundary)
{
    HeuclidGeometryPolygonTools tools;
    auto outer = makeRect(0, 0, 10, 10);
    // Inner rectangle with one vertex touching the outer's edge
    auto touching = makeRect(5, 0, 5, 3);  // top-right at (10,3), top-left at (5,3)
    // All vertices of touching are inside or on boundary of outer
    EXPECT_TRUE(tools.isConvexPolygonContained(touching, outer));
}

TEST(ConvexPolygonContained, OutsidePartially)
{
    HeuclidGeometryPolygonTools tools;
    auto large = makeRect(0, 0, 10, 10);
    auto outside = makeRect(8, 8, 5, 5);  // extends beyond large
    EXPECT_FALSE(tools.isConvexPolygonContained(outside, large));
}

TEST(ConvexPolygonContained, FullyOutside)
{
    HeuclidGeometryPolygonTools tools;
    auto a = makeRect(0, 0, 2, 2);
    auto b = makeRect(10, 10, 2, 2);
    EXPECT_FALSE(tools.isConvexPolygonContained(a, b));
}

TEST(ConvexPolygonContained, RotatedSmallSquare)
{
    HeuclidGeometryPolygonTools tools;
    auto outer = makeRect(-5, -5, 10, 10);
    // Diamond (45-degree rotated square) centered at origin
    std::vector<Point2D<double>> v;
    v.push_back(Point2D<double>( 0.0,  2.0));
    v.push_back(Point2D<double>( 2.0,  0.0));
    v.push_back(Point2D<double>( 0.0, -2.0));
    v.push_back(Point2D<double>(-2.0,  0.0));
    auto diamond = makePoly(v, true);
    EXPECT_TRUE(tools.isConvexPolygonContained(diamond, outer));
}

TEST(ConvexPolygonContained, DiamondPartiallyOutside)
{
    HeuclidGeometryPolygonTools tools;
    auto outer = makeRect(-5, -5, 10, 10);
    // Diamond centered at corner of outer
    std::vector<Point2D<double>> v;
    v.push_back(Point2D<double>( 5.0,  7.0));  // outside
    v.push_back(Point2D<double>( 7.0,  5.0));  // outside
    v.push_back(Point2D<double>( 5.0,  3.0));  // inside
    v.push_back(Point2D<double>( 3.0,  5.0));  // inside
    auto diamond = makePoly(v, true);
    EXPECT_FALSE(tools.isConvexPolygonContained(diamond, outer));
}

// ============================================================================
// isConvexPolygonIntersect tests
// ============================================================================

TEST(ConvexPolygonIntersect, OverlappingRects)
{
    HeuclidGeometryPolygonTools tools;
    auto a = makeRect(0, 0, 5, 5);
    auto b = makeRect(3, 3, 5, 5);  // overlaps at (3,3)-(5,5)
    EXPECT_TRUE(tools.isConvexPolygonIntersect(a, b));
}

TEST(ConvexPolygonIntersect, DisjointRects)
{
    HeuclidGeometryPolygonTools tools;
    auto a = makeRect(0, 0, 2, 2);
    auto b = makeRect(5, 5, 2, 2);
    EXPECT_FALSE(tools.isConvexPolygonIntersect(a, b));
}

TEST(ConvexPolygonIntersect, OneInsideOther)
{
    HeuclidGeometryPolygonTools tools;
    auto outer = makeRect(0, 0, 10, 10);
    auto inner = makeRect(2, 2, 3, 3);
    // Inner is inside outer → they overlap
    EXPECT_TRUE(tools.isConvexPolygonIntersect(inner, outer));
    EXPECT_TRUE(tools.isConvexPolygonIntersect(outer, inner));
}

TEST(ConvexPolygonIntersect, SharedEdge)
{
    HeuclidGeometryPolygonTools tools;
    auto a = makeRect(0, 0, 5, 5);
    auto b = makeRect(5, 0, 5, 5);  // shared edge at x=5
    // Shared edge → boundary contact → considered intersecting (point on edge returns true)
    EXPECT_TRUE(tools.isConvexPolygonIntersect(a, b));
}

TEST(ConvexPolygonIntersect, TouchingCorner)
{
    HeuclidGeometryPolygonTools tools;
    auto a = makeRect(0, 0, 5, 5);
    auto b = makeRect(5, 5, 5, 5);  // touch at (5,5)
    EXPECT_TRUE(tools.isConvexPolygonIntersect(a, b));
}

TEST(ConvexPolygonIntersect, EmptyPolygon)
{
    HeuclidGeometryPolygonTools tools;
    auto a = makeRect(0, 0, 5, 5);
    ConvexPolygon2D empty(0);
    EXPECT_FALSE(tools.isConvexPolygonIntersect(a, empty));
    EXPECT_FALSE(tools.isConvexPolygonIntersect(empty, a));
}

TEST(ConvexPolygonIntersect, DiagonalOverlap)
{
    HeuclidGeometryPolygonTools tools;
    // Two rectangles overlapping diagonally
    auto a = makeRect(0, 0, 4, 4);
    auto b = makeRect(2, 2, 4, 4);  // overlaps at (2,2)-(4,4)
    EXPECT_TRUE(tools.isConvexPolygonIntersect(a, b));
    // Non-overlapping diagonal
    auto c = makeRect(4, 4, 4, 4);  // just touches corner at (4,4)
    EXPECT_TRUE(tools.isConvexPolygonIntersect(a, c));  // corner contact
}

TEST(ConvexPolygonIntersect, RotatedPolygon)
{
    HeuclidGeometryPolygonTools tools;
    auto rect = makeRect(0, 0, 6, 6);
    // Diamond inside
    std::vector<Point2D<double>> v;
    v.push_back(Point2D<double>( 3.0,  0.0));
    v.push_back(Point2D<double>( 0.0, -3.0));
    v.push_back(Point2D<double>(-3.0,  0.0));
    v.push_back(Point2D<double>( 0.0,  3.0));
    auto diamond = makePoly(v, true);
    EXPECT_TRUE(tools.isConvexPolygonIntersect(rect, diamond));
}

TEST(ConvexPolygonIntersect, NoOverlapRotated)
{
    HeuclidGeometryPolygonTools tools;
    auto rect = makeRect(0, 0, 3, 3);
    // Diamond far away
    std::vector<Point2D<double>> v;
    v.push_back(Point2D<double>(10.0, 12.0));
    v.push_back(Point2D<double>(12.0, 10.0));
    v.push_back(Point2D<double>(10.0,  8.0));
    v.push_back(Point2D<double>( 8.0, 10.0));
    auto diamond = makePoly(v, true);
    EXPECT_FALSE(tools.isConvexPolygonIntersect(rect, diamond));
}

// ===== Intersection Area Tests =====

TEST(ConvexPolygonIntersectionArea, FullOverlap)
{
    HeuclidGeometryPolygonTools tools;
    auto a = makeRect(-1, -1, 2, 2);  // 2×2 square centered at origin
    auto b = makeRect(-2, -2, 4, 4);  // 4×4 square centered at origin
    double area = tools.computeConvexPolygonIntersectionArea(a, b);
    EXPECT_NEAR(area, 4.0, 1e-6);  // a is fully inside b, area = 2×2 = 4
}

TEST(ConvexPolygonIntersectionArea, HalfOverlap)
{
    HeuclidGeometryPolygonTools tools;
    auto a = makeRect(-1, -1, 2, 2);  // 2×2 square centered at origin
    auto b = makeRect(0, -1, 2, 2);   // 2×2 square shifted right by 1
    double area = tools.computeConvexPolygonIntersectionArea(a, b);
    // Overlap is a 1×2 rectangle: area = 2
    EXPECT_NEAR(area, 2.0, 1e-6);
}

TEST(ConvexPolygonIntersectionArea, NoOverlap)
{
    HeuclidGeometryPolygonTools tools;
    auto a = makeRect(-1, -1, 2, 2);
    auto b = makeRect(10, 10, 2, 2);
    double area = tools.computeConvexPolygonIntersectionArea(a, b);
    EXPECT_NEAR(area, 0.0, 1e-6);
}

TEST(ConvexPolygonIntersectionArea, ShiftedOverlap)
{
    HeuclidGeometryPolygonTools tools;
    auto a = makeRect(-1, -1, 2, 2);  // 2×2 centered at (0,0)
    auto b = makeRect(-0.5, -1, 2, 2); // 2×2 shifted right by 0.5
    double area = tools.computeConvexPolygonIntersectionArea(a, b);
    // Overlap: 1.5×2 = 3.0
    EXPECT_NEAR(area, 3.0, 1e-6);
}

TEST(ConvexPolygonIntersectionArea, Identical)
{
    HeuclidGeometryPolygonTools tools;
    auto a = makeRect(-3, -4, 6, 8);  // 6×8 centered at (0,0)
    auto b = makeRect(-3, -4, 6, 8);
    double area = tools.computeConvexPolygonIntersectionArea(a, b);
    EXPECT_NEAR(area, 48.0, 1e-6);  // 6*8 = 48
}
