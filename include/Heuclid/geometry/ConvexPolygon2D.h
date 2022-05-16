#pragma once

#include <Heuclid\title\Title.h>
#include <Heuclid\euclid\tuple2D\Point2D.h>
#include <vector>
_LJH_EUCLID_LIB_BEGIN
class ConvexPolygon2D
{
public:
    ConvexPolygon2D():clockwiseOrdered(false),numOfVertices(0),vertexBuffer(),centroid(),area(0.0){};
    ConvexPolygon2D(int numvertices):clockwiseOrdered(false),numOfVertices(numvertices),vertexBuffer(numvertices),centroid(),area(0.0){};
    //virtual int calculateArea(){return 0;};

//private:
    bool clockwiseOrdered;
    int numOfVertices;
    std::vector<Point2D<double> > vertexBuffer;
    Point2D<double> centroid;
    double area;


};

class Rectangle:public ConvexPolygon2D
{
    Rectangle():ConvexPolygon2D(4) {};
};




_LJH_EUCLID_LIB_END