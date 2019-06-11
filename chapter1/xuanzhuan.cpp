#include <iostream>
#include <cmath>

using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>


int main(int argc,char** argv)
{
  //设置Q,r
  Eigen::Matrix3d R = Eigen::AngleAxisd(M_PI,Eigen::Vector3d(0,0,1)).toRotationMatrix();
  Eigen::Quaterniond q = Eigen::Quaterniond(R);
  cout<<"R=\n"<<R<<endl;
  cout<<"q=\n"<<q.coeffs().transpose()<<endl;//coeffs的顺序是（x,y,z,w）,w是实部
  
  //w是计算出来的增量，
  Eigen::Vector3d w(0.01,0.02,0.03);
  //w的模，w转换成轴角的形式，再转换乘旋转矩阵
  double m =sqrt(w(0)*w(0)+w(1)*w(1)+w(2)*w(2));
  //旋转向量转换乘旋转矩阵，此处等价于 w的指数映射。旋转向量->旋转矩阵
  Eigen::Matrix3d w_=Eigen::AngleAxisd(m,Eigen::Vector3d(w(0)/m,w(1)/m,w(2)/m)).toRotationMatrix();
  //使用旋转矩阵的方式更新
  R=R*w_;
  cout<<"R update with Rodrigues Formula\n"<<R<<endl;
  //使用四元数的方式更新
  Eigen::Quaterniond q_ = Eigen::Quaterniond (1,0.5*w(0),0.5*w(1),0.5*w(2));
  q=q*q_;
  q.normalized();
  //把四元数转换成旋转矩阵的形式
  Eigen::Matrix3d q2R = q.toRotationMatrix();
  cout<<"R updated from q is \n"<<q2R<<endl;
  
}




















