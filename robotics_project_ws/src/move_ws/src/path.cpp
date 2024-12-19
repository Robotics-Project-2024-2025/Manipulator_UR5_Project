//
//  path.cpp
//  Robotics
//
//  Created by Niccol� Cristoforetti on 05/12/24.
//

#include "path.h"
using namespace std;

bool path(Vector3d xe1, Vector3d phie1, int argc, const char* argv[]){
    Matrix16 qES;
    qES=receive_joint_state();
    cout << qES << endl;
    MatrixD6 th;
    int j=0;
    do {
        double tmp;
        cout << "Insert value " << j+1 << "for xe1: ";
        cin >> tmp;
        if(tmp >= -1 && tmp <= 1){
            xe1(j) = tmp;
            j++;
        }
        else{
            cout << endl << "Invalid value" << endl;
            return false;
        }
    } while(j<3);
    double time;
    cout << "Insert Time: ";
    cin >> time;
    cout << "Checking Position" << endl;
    if(checkPosition(xe1, qES)) {
        if(p2pMotionPlan(qES, xe1, phie1, time, &th)) {
            cout << "Moving to HOME" << endl;
            setupCommunication(argc, argv);
            send_trajectory(th);
        }
        else {
            cout << "Error in computation of trajectory to point " << xe1 << endl;
            return false;
        }
    }
    else {
        cout << "Impossible to Reach the final Position " << xe1 << endl;
        return false;
    }
    cout << "Control vector xe1 integrity:";
    for(int i=0; i<3; i++){
        cout << endl << xe1(i) << " ";
    }
    setupCommunication(argc, argv);
    return true;
}

MyVector::MyVector() : Node("path_acquiring") {
        service_=this->create_service<MoveService>("service_path", bind(&MyVector::calculatePath, this, std::placeholders::_1, std::placeholders::_2));
        auto shared_this=shared_ptr<MyVector>(this);
        while(rclcpp::ok()) {
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to take path vectors xe1(x,y,z) phie1(x,y,z)");
            rclcpp::spin(shared_this);
        }
}


void MyVector::calculatePath(
    const shared_ptr<MoveService::Request> request,
    shared_ptr<MoveService::Response> response){
    Matrix16 qES;
    qES=receive_joint_state();
    //cout << qES << endl;
    MatrixD6 th;
    double time = 4.0;
    Vector3d v, p;
    v << request->xe1.x, request->xe1.y, request->xe1.z;
    p << request->phie1.x, request->phie1.y, request->phie1.z;
    //cout << "Checking Position" << endl;
    if(checkPosition(v, qES)) {
        if(p2pMotionPlan(qES, v, p, time, &th)) {
            //cout << "Moving to HOME" << endl;
            //setupCommunication(request->argc, request->argv);
            send_trajectory(th);
        }
        else {
            //cout << "Error in computation of trajectory to point " << request->xe1 << endl;
            //return false;
            response->result = false;
        }
    }
    else {
        //cout << "Impossible to Reach the final Position " << request->xe1 << endl;
        //return false;
        response->result = false;
    }
    //cout << "Control vector xe1 integrity:";
   /*for(int i=0; i<3; i++){
        cout << endl << request->xe1(i) << " ";
    }
    */
    //setupCommunication(request->argc, request->argv);
    //return true;
    response->result = true;
}

int main (int argc, const char* argv[]) {
    rclcpp::init(argc, argv);
    auto node_s=make_shared<MyVector>();
    rclcpp::shutdown();
    return 0;
}
