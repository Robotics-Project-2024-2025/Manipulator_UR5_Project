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
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <utility>
#include <cmath>
#include <Eigen/Dense>
#include <vector>
#define DELTAT 0.01
#define ERROR 0.0025
#define MINT 0
#define MAXT 2
#define NUM_JOINTS 6
#define XMIN -1.5
#define XMAX 1.5
#define YMIN -0.7
#define YMAX(i) ((i<NUM_JOINTS/2) ? 0.22 : 0.12)
#define ZMIN 0.0
#define ZMAX(i) ((i<NUM_JOINTS/2) ? 0.72 : 0.72)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
using namespace std;
using namespace Eigen;
using MatrixD6=Matrix<double, -1, NUM_JOINTS>;
using Matrix61=Matrix<double, NUM_JOINTS, 1>;
using Matrix16=Matrix<double, 1, NUM_JOINTS>;
using Matrix86=Matrix<double, 8, NUM_JOINTS>;
using Matrix44=Matrix<double, 4, 4>;
using Matrix41=Matrix<double, 4, 1>;
using Matrix14=Matrix<double, 1, 4>;
using MatrixD4=Matrix<double, -1, 4>;
using Matrix66=Matrix<double, 6, 6>;

typedef enum InverseType {VERTICAL, HORIZONTAL, DEFAULT} InverseType;

bool p2pMotionPlan(Matrix61 qES, Vector3d xEf, Vector3d phiEf, int minT, int maxT, MatrixD6* T, bool velocity, InverseType inv, double rot_gripper);
bool control_collision(Matrix16* th);
bool checkAngles(Matrix16* th);
Matrix3d xRot(double theta);
Matrix3d yRot(double theta);
Matrix3d zRot(double theta);
Matrix44 HomogeneousTransformGen(double theta, double alpha, double d, double a);
Matrix44 HomogeneousTransformSpecific(int i, double theta);
pair<Vector3d, Matrix3d> Ur5Direct(Matrix61 Th);
//Matrix86 Ur5Inverse(Vector3d v, Matrix3d m);
Matrix86 Ur5Inverse(Vector3d pe, Matrix3d re);
bool bestInverse(Matrix16 start, MatrixD6& end);
bool checkAngles(Matrix16* th);
bool control_collision(Matrix16 th);
Matrix3d eul2rotm(Vector3d phiEf);
Vector3d rotm2eul(Matrix3d m);
float adjust_acos(float x);
bool checkPosition (Vector3d pos, Matrix16 q);
double hypot(double x1, double x2);
double singularityCheck(int angle, double value);
void removeRow(MatrixD6* m, unsigned int remove);
bool linear_interpolation(Matrix61 qEs, Vector3d xES, Vector3d xEF, Vector3d phiEf, int minT, int maxT, MatrixD6* Th);
Vector3d smoothBlend(Vector3d old_xE, Vector3d new_xE, double alpha);
bool checkJointOperationalSpace(const vector<Vector3d> jointPositions, int& val);
void clampJointAngles(Matrix61& q);
void computeJointPositions(Matrix61 th, Vector3d jointPositions[NUM_JOINTS]);
void adjustTrajectory(Matrix61& q);
Matrix61 computeJointAdjustment(Vector3d pos_error, Vector3d ori_error, Matrix61 current);
Matrix66 computeJacobian(const Matrix61& q);
Matrix86 Ur5InverseVerticalZ(Vector3d v, Matrix3d m, double th1, double th5, double th6);
//Matrix86 Ur5InverseHorizontalXY(Vector3d v, Matrix3d m, double th4, double th5, double th6);
bool cartesianInterpolation (Matrix61 qES, Vector3d xEf, Vector3d phiEf, int minT, int maxT, MatrixD6* Th, bool velocity, InverseType inv, double rot_gripper);
#endif /* kinematics_h */
