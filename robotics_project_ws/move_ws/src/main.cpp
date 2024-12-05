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
    cout << "Waiting for Joint States" << endl;
    
    Vector3d xE1;
    xE1 << 0.1, 0.3, -0.4;
    Matrix16 qES;
    qES << 0, -M_PI/2+0.01, 0, 0, 0, 0;
    /*Vector3d phiE0;
    phiE0 << 0, 0, 0;*/
    Vector3d phiE1;
    phiE1 << 0, 0, 0;
    MatrixD6 th;
    cout << endl << "Insert values for xE1:" << endl;
    for(int i = 0; i<3; i++){
        double tmp;
        cin >> tmp;
        if(tmp >= -3 && tmp <= 3){
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

    cout << "Control vector xE1 integrity:"
    for(int i=0; i<3; i++){
        cout << endl << xE1(i) << " ";
    }
    
    /*const rclcpp::InitOptions iO(rcl_get_default_allocator());
    if(!rclcpp::ok()) {
        rclcpp::init(static_cast<int>(argc), argv, rclcpp::InitOptions(),
                     rclcpp::SignalHandlerOptions::None);
    }
    rclcpp::spin(std::make_shared<TrajectoryPublisher>(th));
    rclcpp::shutdown();*/
    return 0;
}
