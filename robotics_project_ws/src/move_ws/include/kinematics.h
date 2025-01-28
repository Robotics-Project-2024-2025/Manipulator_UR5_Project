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
#define ERROR 0.0025
#define MINT 0
#define MAXT 6
#define NUM_JOINTS 6
#define XMIN -1
#define XMAX 1
#define YMIN -1
#define YMAX(i) ((i<NUM_JOINTS/2) ? 0.22 : 0.12)
#define ZMIN 0
#define ZMAX 0.835
using namespace std;
using namespace Eigen;
using MatrixD6=Matrix<double, -1, NUM_JOINTS>;
using Matrix61=Matrix<double, NUM_JOINTS, 1>;
using Matrix16=Matrix<double, NUM_JOINTS, 1>;
using Matrix86=Matrix<double, 8, NUM_JOINTS>;
using Matrix44=Matrix<double, 4, 4>;
using Matrix41=Matrix<double, 4, 1>;
using Matrix14=Matrix<double, 1, 4>;
using MatrixD4=Matrix<double, -1, 4>;
bool p2pMotionPlan(Matrix61 qES, Vector3d xEf, Vector3d phiEf, int time, MatrixD6* T);
bool control_collision(Matrix16 th);
bool checkAngles(Matrix16 th);
Matrix3d xRot(double theta);
Matrix3d yRot(double theta);
Matrix3d zRot(double theta);
Matrix44 HomogeneousTransformGen(double theta, double alpha, double d, double a);
Matrix44 HomogeneousTransformSpecific(int i, double theta);
pair<Vector3d, Matrix3d> Ur5Direct(Matrix61 Th);
Matrix86 Ur5Inverse(Vector3d v, Matrix3d m);
bool bestInverse(Matrix16 start, MatrixD6& end);
bool checkAngles(Matrix16 th);
bool control_collision(Matrix16 th);
Matrix3d eul2rotm(Vector3d phiEf);
Vector3d rotm2eul(Matrix3d m);
float adjust_acos(float x);
bool checkPosition (Vector3d pos, Matrix16 q);
#endif /* kinematics_h */
