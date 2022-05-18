#include <Heuclid\euclid\tuple2D\Point2D.h>
#include <Heuclid\geometry\Pose2D.h>
#include <Heuclid\geometry\Pose3D.h>
#include <Heuclid\euclid\tools\QuaternionTool.h>
#include <iostream>

#include <Heuclid\geometry\ConvexPolygon2D.h>
#include <Heuclid\geometry\tools\HeuclidPolygonTools.h>

#include <matplotlibcpp.h>
namespace plt = matplotlibcpp;
int main()
{
   ljh::mathlib::Orientation2D oo;
   oo.setYaw(3.5*pi_o);
   std::cout<<"Yaw test is "<<oo.getYaw()<<std::endl;
    ljh::mathlib::Point2D<double> hhha;
    hhha.setX(100.0);
    ljh::mathlib::Point2D<double> testp(hhha);
    std::cout<< "testp.x is "<<testp.getX()<<std::endl;
    bool equal = testp==hhha;
    std::cout<<"eual is "<<equal<<std::endl;
    ljh::mathlib::Pose2D<double> midFootPose;
    // midFootPose.getPosition().setX(0.5);
    // midFootPose.getPosition().setY(0.7);
    midFootPose.setPosition(hhha);
    midFootPose.setOrientation(1.5*3.1415926);
    // midFootPose.getPosition().setX(1.0);
    std::cout<<"Pose x is "<<midFootPose.getPosition().getX()<<std::endl;
    std::cout<<"Pose y is "<<midFootPose.getPosition().getY()<<std::endl;
    std::cout<<"Pose O is "<<midFootPose.getOrientation().getYaw()<<std::endl;
    ljh::mathlib::Pose2D<double> mid(midFootPose);
    bool equal2 = midFootPose==mid;
    std::cout<<"eual2 is "<<equal2<<std::endl;
    // std::vector<int> test(10,20);
    // for(int i=0;i<10;i++)
    //     test.push_back(i);
    // for (int i = 0; i < 20; i++)
    // {
    //     std::cout << "vector ["<<i<<"] is"<< test[i]<<std::endl;
    // }

    // test.clear();
    // test.push_back(200);
    // std::cout<<test[0]<<std::endl;

    ljh::mathlib::Quaternion<double> q1(2.0,2.0,2.0,2.0);
    ljh::mathlib::Quaternion<double> q4(3.0,4.0,4.0,2.0);
    ljh::mathlib::Quaternion<double> q3;
    ljh::mathlib::Quaternion<double> q2(1.0,2.0,0.3,0.54);
    std::cout<<" q1 is "<<q1.getX()<<" "<<q1.getY()<<" "<<q1.getZ()<<" "<<q1.getS()<<std::endl
             <<" q2 is "<<q2.getX()<<" "<<q2.getY()<<" "<<q2.getZ()<<" "<<q2.getS()<<std::endl
             <<" q3 is "<<q3.getX()<<" "<<q3.getY()<<" "<<q3.getZ()<<" "<<q3.getS()<<std::endl;

    ljh::mathlib::multiply(q1,q2,q3);


    std::cout<<" q1 is "<<q1.getX()<<" "<<q1.getY()<<" "<<q1.getZ()<<" "<<q1.getS()<<std::endl
             <<" q2 is "<<q2.getX()<<" "<<q2.getY()<<" "<<q2.getZ()<<" "<<q2.getS()<<std::endl
             <<" q3 is "<<q3.getX()<<" "<<q3.getY()<<" "<<q3.getZ()<<" "<<q3.getS()<<std::endl;
    
    
    ljh::mathlib::Pose3D<double> cnmb;
    ljh::mathlib::Pose3D<double> cnmba(1,2,3,0.2,0.1,0.4);

    cnmb = cnmba;
    std::cout<<"cnmb pos is "<< cnmb.getPosition().getX()<<" "<< cnmb.getPosition().getY()<<" "<< cnmb.getPosition().getZ()<<" "<<std::endl;
    std::cout<<"cnmb ori is "<<cnmb.getOrientation().getX()<<" "<<cnmb.getOrientation().getY()<<" "<<cnmb.getOrientation().getZ()<<" "<<cnmb.getOrientation().getS()<<" "<<std::endl;


    ljh::mathlib::Quaternion<double> q5(0.245,0.3,0.5);
    std::cout<<"yaw is "<<q5.getYaw()<<std::endl;
    std::cout<<"pitch is "<<q5.getPitch()<<std::endl;
    std::cout<<"roll is "<<q5.getRoll()<<std::endl;




    // polygon check
    ljh::mathlib::HeuclidGeometryPolygonTools heuclidGeometryPolygonTools;
    
    //ljh::mathlib::Point2D<double> pToCheck(1.2,3.5);
    ljh::mathlib::Point2D<double> pToCheck(1.2,3);


    ljh::mathlib::ConvexPolygon2D polygon(4);
    ljh::mathlib::Point2D<double> p1(1,4);
    ljh::mathlib::Point2D<double> p2(2,4);
    ljh::mathlib::Point2D<double> p3(2,0);
    ljh::mathlib::Point2D<double> p4(1,0);
    std::vector<ljh::mathlib::Point2D<double> > buffer;
    buffer.push_back(p1);
    buffer.push_back(p2);
    buffer.push_back(p3);
    buffer.push_back(p4);

    polygon.setVertexBuffer(buffer);
    polygon.setClockwiseOrder(true);

    bool isInPolygon = heuclidGeometryPolygonTools.isPoint2DInsideConvexPolygon2D(polygon,pToCheck);

    std::cout<<"the Flag is ";
    if(isInPolygon)
        std::cout<<" true in "<<std::endl;
    else
        std::cout<<" false out "<<std::endl;


    std::vector<double> vertX;
    std::vector<double> vertY;
    std::vector<double> pointsX;
    std::vector<double> pointsY;
    vertX.push_back(p1.getX());
    vertX.push_back(p2.getX());
    vertX.push_back(p3.getX());
    vertX.push_back(p4.getX());
    vertX.push_back(p1.getX());

    vertY.push_back(p1.getY());
    vertY.push_back(p2.getY());
    vertY.push_back(p3.getY());
    vertY.push_back(p4.getY());
    vertY.push_back(p1.getY());

    pointsX.push_back(pToCheck.getX());
    pointsY.push_back(pToCheck.getY());

    plt::figure(1);
    plt::clf();
    plt::plot(vertX,vertY,"r");
    plt::scatter(pointsX,pointsY,4);
    plt::show();
    return 0;
}