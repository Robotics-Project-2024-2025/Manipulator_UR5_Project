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
MatrixD6 p2pMotionPlan(Vector3d xEs, Vector3d xEf, Vector3d phiEs, Vector3d phiEf, double minT, double maT, double dt);
//Rotations
Matrix3d xRot(double theta);
Matrix3d yRot(double theta);
Matrix3d zRot(double theta);
//Direct Kinematics
pair<Vector3d, Matrix3d> Ur5Direct(Matrix61 Th);


#endif /* kinematics_h */

