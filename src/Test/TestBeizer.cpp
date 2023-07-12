

#include <gtest/gtest.h>
#include <chrono>
#include <Eigen/Dense>
#include <iostream>
#include <Heuclid/geometry/curves/Func.h>
TEST(TestBeizer, basicComputationTest)
{
    Eigen::Matrix4d test;
    test.diagonal().setConstant(5.0);
    test.transpose();
    Eigen::Vector4d slice = test.row(0).transpose();
    Eigen::Vector4d slice2 = test.col(0);
    std::cout << slice<<std::endl;
    std::cout << slice2<<std::endl;

    ljh::heuclid::Bezier<Eigen::Vector2d, 2, 3> Fifth(
      {Eigen::Vector2d(1,1), 
       Eigen::Vector2d(3,1),
       Eigen::Vector2d(4,2),
       Eigen::Vector2d(6,3)}, 0.8);
    
    EXPECT_TRUE((Fifth.at(0.5)-Fifth(0.5)).norm() <1e-3);
    auto start = std::chrono::high_resolution_clock::now();
    auto val1 = Fifth.at(0.5);
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the elapsed time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout<<"de algorithm Cost Time: "<<duration.count()<<std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto val2 = Fifth(0.5);
    end = std::chrono::high_resolution_clock::now();
    // Calculate the elapsed time
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout<<"direct Cost Time: "<<duration.count()<<std::endl;
   
    std::cout<<"at: "<<Fifth.at(0.5)<<std::endl;
    std::cout<<"(): "<<Fifth(0.5)<<std::endl;

    auto dval1 = Fifth.derivative(0.40);
    EXPECT_TRUE((dval1 - Eigen::Vector2d(4.50 / 0.8 , 2.25 / 0.8 )).norm()<1e-3);
    std::cout<<"derivative 1st: "<<dval1.transpose()<<std::endl;
}

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}