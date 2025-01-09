#include "complete_job.h"

class GripperCommunicator : public rclcpp::Node {
public:
    GripperCommunicator() : Node("gripper_communicator") {
        open_gripper_client_ = this->create_client<std_srvs::srv::Trigger>("open_gripper");
        close_gripper_client_ = this->create_client<std_srvs::srv::Trigger>("close_gripper");
        if (!open_gripper_client_->wait_for_service(std::chrono::seconds(5))) {
            RCLCPP_ERROR(this->get_logger(), "Service open_gripper not available.");
        }
        if (!close_gripper_client_->wait_for_service(std::chrono::seconds(5))) {
                    RCLCPP_ERROR(this->get_logger(), "Service close_gripper not available.");
                }

    }
    void open() {
          callService(open_gripper_client_, "Opening the gripper");
      }

      void close() {
          callService(close_gripper_client_, "Closing the gripper");
      }
private:
    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr open_gripper_client_;
    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr close_gripper_client_;
    template<typename ServiceClient>
        void callService(ServiceClient client, const std::string &action) {
            RCLCPP_INFO(this->get_logger(), "%s", action.c_str());
            auto request = std::make_shared<std_srvs::srv::Trigger::Request>();
            auto future = client->async_send_request(request);
            if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), future) ==
                rclcpp::FutureReturnCode::SUCCESS) {
                auto response = future.get();
                if (response->success) {
                    RCLCPP_INFO(this->get_logger(), "%s succeeded: %s", action.c_str(), response->message.c_str());
                } else {
                    RCLCPP_WARN(this->get_logger(), "%s failed: %s", action.c_str(), response->message.c_str());
                }
            } else {
                RCLCPP_ERROR(this->get_logger(), "%s service call timed out.", action.c_str());
            }
        }
};

bool control;
int position_c=-1;
bool path(Vector3d xe1, Vector3d phie1, Matrix16 joint_states, std::shared_ptr<rclcpp::Node> node){
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
    control=path(destinationPos, destinationOri, qEs, node);
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

int main(int argc, const char* argv[])
{
    setupCommunication(argc, argv);
    // Create a service client
    auto node=std::make_shared<rclcpp::Node>("complete_job");
    oneIteration(node);
    rclcpp::shutdown();
    return 0;
}
    /*auto open_path_client_ = node->create_client<MoveService>("service_path");
    cout << "Service Starting Transition" << endl;
    // Wait for the service to become available
    while(!open_path_client_->wait_for_service(std::chrono::seconds(10))) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Path provider not available after waiting");
    }
    // Create a request and populate it
    auto request = std::make_shared<MoveService::Request>();
    request->xe1.x = destinationPos(0);
    request->xe1.y = destinationPos(1);
    request->xe1.z = destinationPos(2);
    request->phie1.x = destinationOri(0);
    request->phie1.y = destinationOri(1);
    request->phie1.z = destinationOri(2);
    request->joints.resize(NUM_JOINTS);
    for (int i=0; i<NUM_JOINTS; i++) {
        float val=qEs(i);
        request->joints[i]=val;
    }
    auto future=open_path_client_->async_send_request(request);
    RCLCPP_INFO(node->get_logger(), "Sending request and waiting for response...");
    if (rclcpp::spin_until_future_complete(node, future) ==
        rclcpp::FutureReturnCode::SUCCESS) {
        auto response = future.get();
        if (response->result) {
            RCLCPP_INFO(node->get_logger(), "Request completed successfully.");
            control=true;
        } else {
            RCLCPP_ERROR(node->get_logger(), "Error in completing the task, redo it.");
        }
    } else {
        RCLCPP_ERROR(node->get_logger(), "Failed to receive a response from the service.");
    }
    cout << "End Service" << endl;*/
