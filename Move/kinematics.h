//
//  kinematics.h
//  Kinematics
//
//  Created by Matteo Gottardelli on 21/11/24.
//

#ifndef kinematics_h
#define kinematics_h
#include <iostream>
#include "kinematics.h"
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <Eigen/Dense>
#define DELTAT 0.01
using namespace std;
using namespace Eigen;
using MatrixD6=Matrix<double, -1, 6>;
using Matrix61=Matrix<double, 6, 1>;
using Matrix86=Matrix<double, 8, 6>;
using Matrix44=Matrix<double, 4, 4>;
using Matrix41=Matrix<double, 4, 1>;
using Matrix14=Matrix<double, 1, 4>;
MatrixD6 p2pMotionPlan(Vector3d xEs, Vector3d xEf, Vector3d phiEs, Vector3d phiEf, double minT, double maxT, double dt);
//Rotations
Matrix3d xRot(double theta);
Matrix3d yRot(double theta);
Matrix3d zRot(double theta);
Matrix3d eul2rotm(Vector3d& phiEf);
Vector3d rotm2eul(Matrix3d m);
//Direct Kinematics
pair<Vector3d, Matrix3d> Ur5Direct(Matrix61 Th);
Matrix86 Ur5Inverse(Vector3d v, Matrix3d m);
Matrix44 HomogeneousTransform(double theta, double alpha, double d, double a); 


#endif /* kinematics_h */

