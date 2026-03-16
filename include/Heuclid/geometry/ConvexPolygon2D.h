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
 * @file ConvexPolygon2D.h
 * @brief 2D convex polygon representation.
 * @author Junhang Lai (赖俊杭)
 */

#include <Heuclid/title/Title.h>
#include <Heuclid/euclid/tuple2D/Point2D.h>
#include <vector>
_LJH_EUCLID_LIB_BEGIN
/** @brief A 2D convex polygon defined by its vertex buffer. */
class ConvexPolygon2D
{
public:
    ConvexPolygon2D():clockwiseOrdered(false),numOfVertices(0),vertexBuffer(),centroid(),area(0.0){};
    ConvexPolygon2D(int numvertices):clockwiseOrdered(false),numOfVertices(numvertices),vertexBuffer(numvertices),centroid(),area(0.0){};
    ConvexPolygon2D(const ConvexPolygon2D& other):clockwiseOrdered(other.clockwiseOrdered),numOfVertices(other.numOfVertices),vertexBuffer(other.vertexBuffer),centroid(other.centroid),area(other.area){};
    //virtual int calculateArea(){return 0;};

    void setClockwiseOrder(bool order){this->clockwiseOrdered = order;};
    void setNumOfVertices(int num){this->numOfVertices = num;};
    void setVertexBuffer(std::vector<Point2D<double> > buffer);
    void setCentroid(Point2D<double> cen){this->centroid = cen;};
    void setArea(double _area){this->area =_area;};

    bool getClockwiseOrder() const{return this->clockwiseOrdered;};
    int getNumOfVertices() const{return this->numOfVertices;};
    std::vector<Point2D<double> > getVertexBuffer() const{return this->vertexBuffer;};
    Point2D<double> getCentroid() const{return this->centroid;};
    double getArea() const{return this->area;};
private:
    bool clockwiseOrdered;
    int numOfVertices;
    std::vector<Point2D<double> > vertexBuffer;
    Point2D<double> centroid;
    double area;


};

class Rectangle:public ConvexPolygon2D
{
public:
    Rectangle():ConvexPolygon2D(4) {};
};




_LJH_EUCLID_LIB_END