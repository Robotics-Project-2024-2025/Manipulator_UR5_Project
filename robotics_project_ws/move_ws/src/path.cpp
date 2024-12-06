//
//  path.cpp
//  Robotics
//
//  Created by Niccolò Cristoforetti on 05/12/24.
//

#include "path.h"

bool path(Vector3d xE1, Vector3d phiE1, int argc, const char* argv[]){
        Matrix16 qES;
        qES=receive_joint_state();
        cout << qES << endl;
        MatrixD6 th;
        for(int i = 0; i<3; i++){
            double tmp;
            cout << "Insert value " << i+1 << "for xE1: ";
            cin >> tmp;
            if(tmp >= -1 && tmp <= 1){
                xE1(i) = tmp;
            }
            else{
                cout << endl << "Invalid value" << endl;
                return false;
            }
        }
        cout << "Checking Position" << endl;
        if(checkPosition(xE1, qES)) {
            if(p2pMotionPlan(qES, xE1, phiE1, &th)) {
                cout << "Moving to HOME" << endl;
                setupCommunication(argc, argv);
                send_trajectory(th);
            }
            else {
                cout << "Error in computation of trajectory to point " << xE1 << endl;
                return false;
            }
        }
        else {
            cout << "Impossible to Reach the final Position " << xE1 << endl;
            return false;
        }
        cout << "Control vector xE1 integrity:";
        for(int i=0; i<3; i++){
            cout << endl << xE1(i) << " ";
        }
        setupCommunication(argc, argv);
    return true;
}
