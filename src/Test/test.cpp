#include <Heuclid\euclid\tuple2D\Point2D.h>
#include <Heuclid\geometry\Pose2D.h>
#include <Heuclid\geometry\Pose3D.h>
#include <Heuclid\euclid\tools\QuaternionTool.h>
#include <iostream>

int main()
{
   
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
    return 0;
}