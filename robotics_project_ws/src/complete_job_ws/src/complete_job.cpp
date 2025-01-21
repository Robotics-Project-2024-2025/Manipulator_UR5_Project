#include "complete_job.h"

bool control;
int position_c=-1;
bool path_search(Vector3d xe1, Vector3d phie1, Matrix16 joint_states, std::shared_ptr<rclcpp::Node> node){
    MatrixD6 th;
    double time = 4.0;
    Matrix61 qEs;
    for (int i=0; i<NUM_JOINTS; i++) {
        qEs(i)=joint_states(i);
    }
    RCLCPP_INFO(node->get_logger(), "Checking Position");
    if(checkPosition(xe1, joint_states)) {
        if(p2pMotionPlan(qEs, xe1, phie1, time, &th)) {
            RCLCPP_INFO(node->get_logger(), "Moving to HOME");
            send_trajectory(th, node);
        }
        else {
            RCLCPP_INFO(node->get_logger(), "Error in computation of trajectory to point ");
            return false;
        }
    }
    else {
        RCLCPP_INFO(node->get_logger(), "Impossible to Reach the final Position ");
        return false;
    }
    return true;
}

void generalizeMovement (std::shared_ptr<rclcpp::Node> node, Vector3d destinationPos, Vector3d destinationOri) {
    control=false;
    Matrix16 qEs=receive_joint_state();
    control=path_search(destinationPos, destinationOri, qEs, node);
}
void oneIteration(std::shared_ptr<rclcpp::Node> node) {
    Vector3d posHome{{-0.2, 0.2, -0.3}};
    Vector3d posBlock{{-0.3, 0.4, -0.8}};
    Vector3d posDest{{0.4, 0.2, -0.7}};
    Vector3d phiStart{{0.0, 0.0, 0.0}};
    Vector3d phiEf{{0.0, 0.0, 0.0}};
    auto gripper=std::make_shared<GripperCommunicator>();
    position_c++;
    position_c=position_c%3;
    switch (position_c) {
        case 0:
            gripper->open();
            generalizeMovement(node, posHome, phiEf);
            break;
        case 1:
            gripper->close();
            generalizeMovement(node, posBlock, phiEf);
            break;
        case 2:
            gripper->open();
            generalizeMovement(node, posDest, phiEf);
            break;
        default:
            rclcpp::shutdown();
            break;
    }
}
