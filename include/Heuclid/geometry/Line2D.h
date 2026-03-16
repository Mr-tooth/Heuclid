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
#pragma once
/**
 * @file Line2D.h
 * @brief 2D line representation (point-direction form).
 * @author Junhang Lai (赖俊杭)
 */
#include <Heuclid/title/Title.h>
#include <Heuclid/euclid/tuple2D/Point2D.h>
#include <Heuclid/euclid/tuple2D/UnitVector2D.h>
#include <Heuclid/euclid/tuple2D/Vector2D.h>

#include <Heuclid/euclid/tools/HeuclidCoreTool.h>
#include <cassert>

_LJH_EUCLID_LIB_BEGIN

/** @brief A 2D line in point-direction form (origin + direction vector). */
class Line2D
{
private:
    Point2D<double> point;
    UnitVector2D<double> direction;
public:
    Line2D():point(),direction(){};
    Line2D(double pointOnLineX, double pointOnLineY, double lineDirectionX, double lineDirectionY);
    Line2D(const Line2D& other);
    Line2D(Point2D<double> firstPointOnLine, Point2D<double> secondPointOnLine);
    Line2D(Point2D<double> pointOnLine, Vector2D<double>  lineDirection);


    void setLine2D(const Line2D& other);
    void setPoint(Point2D<double>& other);
    void setDirection(UnitVector2D<double>& other);
    void setDirection(Vector2D<double>& other);

    UnitVector2D<double> getDirection();
    Point2D<double> getPoint();

    bool geometricallyEquals(const Line2D& other, double epsilon);
    bool epsilonEquals(const Line2D& other, double epsilon);
};




_LJH_EUCLID_LIB_END