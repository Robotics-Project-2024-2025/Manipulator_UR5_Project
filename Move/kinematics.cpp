//
//  kinematics.cpp
//  Kinematics
//
//  Created by Matteo Gottardelli on 21/11/24.
//

#include "kinematics.h"

MatrixD6 p2pMotionPlan(Vector3d xEs, Vector3d xEf, Vector3d phiEs, Vector3d phiEf, double minT, double maT, double dt) {
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

Matrix44 HomogeneousTransform(double theta, double alpha, double d, double a){  
    Matrix44 m;
    m << cos(theta), -sin(theta)*cos(alpha), sin(theta)*sin(alpha), d,
        sin(theta), cos(theta)*cos(alpha), -cos(theta)*sin(alpha), 0,
        0, sin(alpha), cos(alpha), a,
        0,0,0,1;
    
}

