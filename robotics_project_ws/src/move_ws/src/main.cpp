//
//  main.cpp
//  Kinematics
//
//  Created by Matteo Gottardelli on 21/11/24.
//

#include "kinematics.h"
#include "kin_communication.h"
#include "path.h"

using namespace std;
using namespace Eigen;

int main (int argc, const char* argv[]) {
    rclcpp::init(argc, argv);
    while(1) {
        auto node_s=make_shared<MyVector>();
    }
    rclcpp::shutdown();
    return 0;
}

/*
int main(int argc, const char * argv[]) {
    //Vector3d xE0;
    //xE0 << 0.1, 0.3, 0.1;
    setupCommunication(argc, argv);
    while(rclcpp::ok()) {
        cout << "Waiting for Joint States" << endl;
        Vector3d xE1;
        //Block Recognition and classification call
        xE1 << 0.0, 0.0, 0.0;
        Vector3d phiE1;
        phiE1 << 0, 0, 0;
        if(!path(xE1, phiE1, argc, argv)){
            cout << "Errore!" << endl;
        }
        else {
            cout << "Movement Handled Successfully" << endl;
        }
    }
    return 0;
}
*/
