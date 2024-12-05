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
    /*Vector3d xE0;
    xE0 << 0.1, 0.3, 0.1;*/
   setupCommunication(argc, argv);
    while(rclcpp::ok()) {
        cout << "Waiting for Joint States" << endl;
        Vector3d xE1;
        xE1 << 0.0, 0.0, 0.0;
        Matrix16 qES;
        qES=receive_joint_state();
        /*Vector3d phiE0;
         phiE0 << 0, 0, 0;*/
        Vector3d phiE1;
        phiE1 << 0, 0, 0;
        MatrixD6 th;
        cout << endl << "Insert values for xE1:" << endl;
        for(int i = 0; i<3; i++){
            double tmp;
            cout << "Insert Value " << i << ": ";
            cin >> tmp;
            if(tmp >= -1.0 && tmp <= 1.0){
                xE1(i) = tmp;
            }
            else{
                cout << endl << "Invalid value" << endl;
            }
        }
        if(checkPosition(xE1, qES)) {
            if(p2pMotionPlan(qES, xE1, phiE1, &th)) {
                cout << "Moving to HOME" << endl;
                send_trajectory(th);
            }
            else {
                cout << "Error in computation of trajectory to point " << xE1 << endl;
            }
        }
        else {
            cout << "Impossible to Reach the final Position " << xE1 << endl;
        }
        cout << "Control vector xE1 integrity:";
        for(int i=0; i<3; i++){
            cout << endl << xE1(i) << " ";
        }
    }
    return 0;
}
