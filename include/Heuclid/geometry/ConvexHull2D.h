
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
/**
 * @file ConvexHull2D.h
 * @brief 2D convex hull computation (Graham scan, Gift wrapping).
 * @author Junhang Lai (赖俊杭)
 */
#include <Heuclid/title/Title.h>
#include <Heuclid/geometry/ConvexPolygon2D.h>
#include <Heuclid/euclid/tools/HeuclidCoreTool.h>
#include <Eigen/Core>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
_LJH_EUCLID_LIB_BEGIN

constexpr double eps = 1e-3;

enum class CONVEXHULL_METHOD
{
    Graham_scan,
    Gift_Wrapping
};

template<typename DataType>
bool comparePoints(const Point2D<DataType> & p1, const Point2D<DataType> & p2)
{
    double angle1 = std::atan2(p1.getY(), p1.getX());
    double angle2 = std::atan2(p2.getY(), p2.getX());
    return angle1 < angle2;
}

/*
* A 2D convexhull representation using Halfspace Inequality like A*x <= b.
* */
template<typename DataType, int MatrixRows = 8>
class ConvexHull2D
{

public:
    ConvexHull2D() : numOfPoints(MatrixRows), pointList(MatrixRows){
        this->A_Matrix.setZero();
        this->b_Matrix.setZero();
    }
    // for support ConvexHull Calculation of Double support phase of bipedal robots
    ConvexHull2D(Rectangle rec1, Rectangle rec2) : numOfPoints(MatrixRows), pointList(MatrixRows){
        this->A_Matrix.setZero();
        this->b_Matrix.setZero();

        this->loadRectangleVertex(rec1, rec2);
        
    };

    /** @brief Compute convex hull and convert to half-space form A*x <= b. */
    void calculateHalfspaceForm(CONVEXHULL_METHOD method);
    
    /** @brief Load vertices from two rectangles (for bipedal support polygon). */
    void loadRectangleVertex(Rectangle rec1, Rectangle rec2);
    /** @brief Load a custom set of 2D vertices. */
    void loadVertex(const std::vector<Point2D<DataType>>& _pointList);
    /** @brief Get the half-space inequality matrix A (A*x <= b). */
    const Eigen::Matrix<DataType, MatrixRows, 2>& getA_Matrix() const{return this->A_Matrix;};
    /** @brief Get the half-space inequality vector b (A*x <= b). */
    const Eigen::Vector<DataType, MatrixRows>& getb_Matrix() const{return this->b_Matrix;};
    /** @brief Get the combined [A | b] matrix. */
    const Eigen::Matrix<DataType, MatrixRows, 3>& getAb_Matrix()const{return this->Ab_Matrix;};
    /** @brief Get the number of hull vertices. */
    int getNumofVertex()const{return this->numOfPoints;};
    /** @brief Get the vertex point list. */
    const std::vector<Point2D<DataType>>& getPointList() const{return this->pointList;};
private:
    int numOfPoints;
    std::vector<Point2D<DataType>> pointList;

    Eigen::Matrix<DataType, MatrixRows, 2> A_Matrix;
    Eigen::Vector<DataType, MatrixRows> b_Matrix;
    Eigen::Matrix<DataType, MatrixRows, 3> Ab_Matrix;

    DataType crossProduct(const Point2D<DataType> & p1, const Point2D<DataType> & p2, const Point2D<DataType> & p3);
    // bool comparePoints(const Point2D<DataType> & p1, const Point2D<DataType> & p2);
    //Graham's scan algorithm

    void computeConvexHullbyGraham_scan();
    void computeConvexHullbyGift_Wrapping();
   
};

template<typename DataType, int MatrixRows>
void ConvexHull2D<DataType, MatrixRows>::loadVertex(const std::vector<Point2D<DataType>>& _pointList)
{
    this->pointList.clear();
    this->pointList = _pointList;
    this->numOfPoints = static_cast<int>(this->pointList.size());
}

template<typename DataType, int MatrixRows>
void ConvexHull2D<DataType, MatrixRows>::loadRectangleVertex(Rectangle rec1, Rectangle rec2)
{
    // load vertex of two rectangles
    this->pointList.clear();
    for(int i=0; i<4; i++)
    {
       this->pointList.push_back(rec1.getVertexBuffer().at(i)); 
       this->pointList.push_back(rec2.getVertexBuffer().at(i)); 
    }
    this->numOfPoints = static_cast<int>(this->pointList.size());
}

template<typename DataType, int MatrixRows>
DataType ConvexHull2D<DataType, MatrixRows>:: crossProduct(const Point2D<DataType> & p1, const Point2D<DataType> & p2, const Point2D<DataType> & p3)
{
    return (p2.getX() - p1.getX()) * (p3.getY() - p1.getY()) - (p3.getX() - p1.getX()) * (p2.getY() - p1.getY());
}



template<typename DataType, int MatrixRows>
void ConvexHull2D<DataType, MatrixRows>::computeConvexHullbyGraham_scan()
{
    this->numOfPoints = this->pointList.size();
    if(this->numOfPoints < 3) return;
    int lowestIndex = 0;
    for (int i = 1; i < this->numOfPoints; ++i) {
        if (this->pointList[i].getY() < this->pointList[lowestIndex].getY() || (this->pointList[i].getY() == this->pointList[lowestIndex].getY() && this->pointList[i].getX() < this->pointList[lowestIndex].getX())) {
            lowestIndex = i;
        }
    }

    // Swap the lowest point with the first point in the array
    std::swap(this->pointList[0], this->pointList[lowestIndex]);

    for(auto point = this->pointList.begin() +1 ; point != this->pointList.end();point++)
    {
        point->setX(point->getX() - this->pointList[0].getX());
        point->setY(point->getY() - this->pointList[0].getY());
    }
        // *point = point - this->pointList[0]; 
          
    // Sort the points based on their polar angle with respect to the lowest point
    std::sort(this->pointList.begin() + 1, this->pointList.end(), comparePoints<DataType>);

    for(auto point = this->pointList.begin() +1 ; point != this->pointList.end();point++)
    {
        point->setX(point->getX() + this->pointList[0].getX());
        point->setY(point->getY() + this->pointList[0].getY());
    }
        // *point = point + this->pointList[0];  

    std::vector<Point2D<DataType>> hull;
    hull.push_back(this->pointList[0]);
    hull.push_back(this->pointList[1]);
    for (int i = 2; i < this->numOfPoints+1; ++i) 
    {
        while (hull.size() >= 2) 
        {
            int j = i % this->numOfPoints;
            int m = hull.size() - 1;
            double cross = this->crossProduct(hull[m - 1], hull[m], this->pointList[j]);
            if(std::abs(cross) < eps)
            {
                double dist_m = (hull[m].getX()-hull[m - 1].getX())*(hull[m].getX()-hull[m - 1].getX()) + 
                                (hull[m].getY()-hull[m - 1].getY())*(hull[m].getY()-hull[m - 1].getY());
                double dist_i = (this->pointList[j].getX()-hull[m - 1].getX())*(this->pointList[j].getX()-hull[m - 1].getX()) + 
                                (this->pointList[j].getY()-hull[m - 1].getY())*(this->pointList[j].getY()-hull[m - 1].getY());
                if(dist_m < dist_i)
                    hull.pop_back();
            }
            else if(cross < 0.0)
            {
                hull.pop_back();
            }
            // if (this->crossProduct(hull[m - 1], hull[m], this->pointList[i]) <= 0) 
            //     hull.pop_back();
            else 
                break;
        }
        if(i < this->numOfPoints)
            hull.push_back(this->pointList[i]);
    }

    this->pointList = hull;
    this->numOfPoints = this->pointList.size();
}

template<typename DataType, int MatrixRows>
void ConvexHull2D<DataType, MatrixRows>::computeConvexHullbyGift_Wrapping()
{
    this->numOfPoints = this->pointList.size();
    if(this->numOfPoints < 3) return;

    std::vector<Point2D<DataType>> hull;
    int leftmost = 0;
    for (int i = 1; i < this->numOfPoints; ++i) 
    {
        if (this->pointList[i].getX() < this->pointList[leftmost].getX() || 
                (this->pointList[i].getX() == this->pointList[leftmost].getX() && 
                    this->pointList[i].getY() < this->pointList[leftmost].getY()))
            leftmost = i;
    }

    int p = leftmost, q;
    do {
        hull.push_back(this->pointList[p]);
        q = (p + 1) % this->numOfPoints;

        for (int i = 0; i < this->numOfPoints; ++i) 
        {
            double cross = this->crossProduct(this->pointList[p], this->pointList[i], this->pointList[q]);
            if(std::abs(cross) < eps)
            {
                double dist_i = HeuclidCoreTool::normSquared(this->pointList[i].getX()-this->pointList[p].getX(),
                                                                this->pointList[i].getY()-this->pointList[p].getY());
                double dist_q = HeuclidCoreTool::normSquared(this->pointList[q].getX()-this->pointList[p].getX(),
                                                                this->pointList[q].getY()-this->pointList[p].getY());
                if(dist_i > dist_q) q = i;
            }
            else if(cross > eps)
            {
                q = i;
            }
        }

        p = q;
    // std::cout<<"doing wrapping...\n";
    } while (p != leftmost);

    // std::cout<<"wrapping finished...\n";
    this->pointList = hull;
    this->numOfPoints = this->pointList.size();

}

template<typename DataType, int MatrixRows>
void ConvexHull2D<DataType, MatrixRows>::calculateHalfspaceForm(CONVEXHULL_METHOD method)
{
    if(method == CONVEXHULL_METHOD::Gift_Wrapping)
        this->computeConvexHullbyGift_Wrapping();
    else if(method == CONVEXHULL_METHOD::Graham_scan)
        this->computeConvexHullbyGraham_scan();

    this->A_Matrix.setZero();
    this->b_Matrix.setZero();
    
    this->Ab_Matrix.setZero();

    for(int i=0; i< this->numOfPoints; i++)
    {
        int j = (i + 1) % this->numOfPoints;
        
        A_Matrix(i, 0) = this->pointList[j].getY() - this->pointList[i].getY();
        A_Matrix(i, 1) = this->pointList[i].getX() - this->pointList[j].getX();
        b_Matrix(i)    = -(this->pointList[j].getX() * this->pointList[i].getY() - this->pointList[i].getX() * this->pointList[j].getY());

        Ab_Matrix(i, 0) = this->pointList[j].getY() - this->pointList[i].getY();
        Ab_Matrix(i, 1) = this->pointList[i].getX() - this->pointList[j].getX();
        Ab_Matrix(i, 2) = -(this->pointList[j].getX() * this->pointList[i].getY() - this->pointList[i].getX() * this->pointList[j].getY());
    }

}


_LJH_EUCLID_LIB_END