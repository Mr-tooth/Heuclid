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
#include "./Foot/FootPolygon.h"
#include <Heuclid/geometry/ConvexHull2D.h>
#include <chrono>
TEST(TestConvexHull, hullComputation)
{
    ljh::heuclid::Rectangle leftFoot, rightFoot;
    
    std::vector<ljh::heuclid::Point2D<double> >leftVertex, rightVertex;

    double left_FootCenterPos[2] = { 0,  0.1};
    double rightFootCenterPos[2] = { 0, -0.1};

    double left_yaw = 0.0;
    double rightyaw = 0.0;

    double VertexX[4] = {0.0};
    double VertexY[4] = {0.0};

    getFootVertex(left_FootCenterPos, left_yaw, 1, VertexX, VertexY);
    for(int i=0; i<4; i++)
      leftVertex.push_back({VertexX[i], VertexY[i]});

    getFootVertex(rightFootCenterPos, rightyaw, 0, VertexX, VertexY);
    for(int i=0; i<4; i++)
      rightVertex.push_back({VertexX[i], VertexY[i]});
    
    leftVertex.clear();
    leftVertex.push_back({1.,1.});
    leftVertex.push_back({3.,1.});
    leftVertex.push_back({3.,2.});
    leftVertex.push_back({1.,2.});

    rightVertex.clear();
    rightVertex.push_back({1.,-1.});
    rightVertex.push_back({3.,-1.});
    rightVertex.push_back({3.,-2.});
    rightVertex.push_back({1.,-2.});

    // rightVertex.push_back({5.,3.});
    // rightVertex.push_back({6.,4.});
    // rightVertex.push_back({4.,4.});
    // rightVertex.push_back({5.,2.});



    leftFoot.setVertexBuffer(leftVertex);
    rightFoot.setVertexBuffer(rightVertex);


  ljh::heuclid::ConvexHull2D<double> hull(leftFoot, rightFoot);
  
  auto start = std::chrono::high_resolution_clock::now();
  hull.calculateHalfspaceForm(ljh::heuclid::CONVEXHULL_METHOD::Gift_Wrapping);
  
  auto A_matrix = hull.getA_Matrix();
  auto b_matrix = hull.getb_Matrix();
  // End the timer
  auto end = std::chrono::high_resolution_clock::now();
  // Calculate the elapsed time
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout<<"Gift Wrapping Cost Time: "<<duration.count()<<std::endl;

  start = std::chrono::high_resolution_clock::now();
  hull.calculateHalfspaceForm(ljh::heuclid::CONVEXHULL_METHOD::Graham_scan);
  auto A_matrix1 = hull.getA_Matrix();
  auto b_matrix1 = hull.getb_Matrix();
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout<<"Graham Scan Cost Time: "<<duration.count()<<std::endl;

  std::cout << "A_Matrix: \n"<<A_matrix<<std::endl;
  std::cout << "b_Matrix: \n"<<b_matrix<<std::endl;

  std::cout << "A_Matrix1: \n"<<A_matrix1<<std::endl;
  std::cout << "b_Matrix1: \n"<<b_matrix1<<std::endl;
  double thr = 1e-3;
  EXPECT_LT((A_matrix-A_matrix1).norm(), thr)
    <<"A_Matrix Inequal: \n A by Gift is \n"
    << A_matrix<<"A by gift is \n"
    << A_matrix1<<std::endl;
  
  EXPECT_LT((b_matrix-b_matrix1).norm(), thr)
    <<"b_Matrix Inequal: \n b by Gift is \n"
    << b_matrix<<"b by graham is \n"
    << b_matrix1<<std::endl;

}


int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}