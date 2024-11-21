//
//  kinematics.cpp
//  Kinematics
//
//  Created by Matteo Gottardelli on 21/11/24.
//

#include "kinematics.h"

Matrix3d eul2rotm(Vector3d& phiEf) {
    return zRot(phiEf(0)) * yRot(phiEf(1)) * xRot(phiEf(2));
}

Vector3d rotm2eul(Matrix3d m) {
    double x, y, z;
    if(m(2,0)<1) {
        if(m(2,0)>-1) {
            x=atan2(m(2,1), m(2,2));
            y=asin(-m(2,0));
            z=atan2(m(1,0), m(0,0));
        }
        else {
            x=0;
            y=M_PI/2;
            z=-atan2(-m(1,2), m(1,1));
        }
    }
    else {
        x=0;
        y=-M_PI/2;
        z=-atan2(-m(1,2), m(1,1));
    }
    Vector3d ret;
    ret << z, y, x;
    return ret;
}

MatrixD6 p2pMotionPlan(Vector3d xEs, Vector3d xEf, Vector3d phiEs, Vector3d phiEf, double minT, double maxT, double dt) {
    MatrixD6 th;
    th.resize(3, 6);
    th << 1, 2, 3, 4, 5, 6,
          1, 2, 3, 4, 5, 6,
          1, 2, 3, 4, 5, 6;
    cout << zRot(0.5) <<endl;
    return th;
}

Matrix3d xRot(double theta){
    Matrix3d r;
    r << 1, 0, 0,
         0, cos(theta), -sin(theta),
         0,sin(theta),cos(theta);
    return r;
}

Matrix3d yRot(double theta){
    Matrix3d r;
    r << cos(theta), 0, sin(theta),
         0, 1, 0,
         -sin(theta),0,cos(theta);
    return r;
}

Matrix3d zRot(double theta){
    Matrix3d r;
    r << cos(theta), -sin(theta), 0,
          sin(theta), cos(theta), 0,
          0,0,1;
    return r;
}

Matrix44 HomogeneousTransform(int i, double theta, double alpha, double d, double a){
    Matrix44 m;
    if (i==4) {
        d=-d;
    }
    if (i<4) {
        m << cos(theta), -sin(theta)*cos(alpha), sin(theta)*sin(alpha), d,
        sin(theta), cos(theta)*cos(alpha), -cos(theta)*sin(alpha), 0,
        0, sin(alpha), cos(alpha), a,
        0,0,0,1;
    }
    else {
        m << cos(theta), -sin(theta)*cos(alpha), sin(theta)*sin(alpha), 0,
        sin(theta), cos(theta)*cos(alpha), -cos(theta)*sin(alpha), d,
        0, sin(alpha), cos(alpha), 0,
        0,0,0,1;
    }
    return m;
}

pair<Vector3d, Matrix3d> Ur5Direct(Matrix61 Th) {
    vector<double> A={0, -0.425, -0.3922, 0, 0, 0};
    vector<double> D={0.1625, 0, 0, 0.1333, 0.0997, 0.0996};
    vector<double> alfa={0, M_PI/2, 0, 0, M_PI/2, -M_PI/2};
    //T[6]={T10, T21, T32, T43, T54, T65}
    Matrix44 T60;
    T60 << 1, 0, 0, 0,
           0, 1, 0, 0,
           0, 0, 1, 0,
           0, 0, 0, 1;
    for (int i=0; i<6; i++) {
        Matrix44 T=HomogeneousTransform(i, Th[i], alfa[i], D[i], A[i]);
        T60*=T;
    }
    Vector3d v;
    Matrix3d m;
    v << T60(0, 3), T60(1, 3), T60 (2, 3);
    m << T60(0, 0), T60(0, 1), T60(0, 2),
         T60(1, 0), T60(1, 1), T60(1, 2),
         T60(2, 0), T60(2, 1), T60(2, 2);
    return make_pair(v, m);
}
