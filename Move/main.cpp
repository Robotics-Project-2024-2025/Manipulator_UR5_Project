//
//  main.cpp
//  Kinematics
//
//  Created by Matteo Gottardelli on 21/11/24.
//

#include "kinematics.h"
#include "kin_communication.h"

using namespace std;
using namespace Eigen;
int main(int argc, const char * argv[]) {
    Vector3d xE0;
    xE0 << 0.1, 0.3, 0.1;
    Vector3d xE1;
    xE1 << 0.5, 0.1, 0.5;
    Vector3d phiE0;
    phiE0 << 0, 0, 0;
    Vector3d phiE1;
    phiE1 << M_PI/6, M_PI/3, M_PI/4;
    MatrixD6 th=p2pMotionPlan(xE0, xE1, phiE0, phiE1, 0, 1, DELTAT);
    cout << th << endl;
    return 0;
}
