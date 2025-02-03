//
//  complete_job.h
//  Robotics
//
//  Created by Matteo Gottardelli on 05/01/25.
//
#include "complete_job.h"

bool control;
Point3D blockPos;
Point3D finalPos;
Vector3d phiEf;
float startFrameZ;
Vector3d posHome;

bool areEqual(double n1, double n2, double precision) {
    double diff = std::abs(n1 - n2);
    return diff < precision;
}

Point2D getDestination(int class_id) {
    Eigen::Vector3f x_coords(0.45f, 0.37f, 0.3f);
    Eigen::Vector3f y_coords(0.25f, 0.15f, 0.05f);
    int row = class_id / 3;
    int col = class_id % 3;
    Point2D point;
    point.x = x_coords(col);
    point.y = y_coords(row);
    return point;
}

Point3D convertFromWorldFrameToMFrame(Vector3d start) {
    cout << start(0) << " " << start(1) << " " << start(2) << endl;
    Vector3d trasl, res;
    trasl << 0.5, 0.35, 1.81;
    res=start-trasl;
    Point3D ret;
    ret.x=res(0);
    ret.y=-res(1);
    ret.z=0.72;
    cout << res(0) << " " << res(1) << " " << res(2) << endl;
    return ret;
}

void initializeBlocks(float block_x, float block_y, float dest_x, float dest_y, double sFZ) {
    float x=block_x;
    float y=block_y;
    Vector3d v;
    v << x, y, 0.9;
    blockPos=convertFromWorldFrameToMFrame(v);
    startFrameZ=sFZ;
    v << dest_x, dest_y, 0.72;
    phiEf << sFZ, -M_PI, 0.0;
    posHome << 0.0, -0.5, 0.4;
}

bool motion (Matrix16 qEs, Vector3d xEs, Vector3d xEf, Vector3d phiEf, double minT, double maxT, MatrixD6* Th, std::shared_ptr<rclcpp::Node> node) {
    InverseType inv;
    RCLCPP_INFO(node->get_logger(), "Computation moving from START");
    //3 operations per motion for generalizing
    int interval=(int)((maxT-minT)/3); //2 secs
    Vector3d tStart, tEnd;
    tStart << minT, minT+interval, minT+interval*2;
    tEnd << maxT-2*interval, maxT-interval, maxT;
    //First Motion
    //pair<Vector3d, Matrix3d> start1=Ur5Direct(qEs);
    Vector3d start1=xEs;
    start1(2)=0.5;
    inv=VERTICAL;
    //Vector3d start1=convertFromWorldFrameToMFrame(s1.first);
    RCLCPP_INFO(node->get_logger(), "FIRST: %.3f %.3f %.3f", start1(0), start1(1), start1(2));
    Vector3d phi1;
    phi1 << 0.0, 0.0, 0.0;
    if(!p2pMotionPlan(qEs.transpose(), start1, phi1, tStart(0), tEnd(0), Th, true, inv, 0.0)) {
        RCLCPP_ERROR(node->get_logger(), "First motion failed!");
        return false;
    }
    /*if(!linear_interpolation(qEs, xEs, start1, phiEf, tStart(0), tEnd(0), Th)) {
        RCLCPP_ERROR(node->get_logger(), "First motion failed!");
        return false;
    }*/
    RCLCPP_INFO(node->get_logger(), "Computation arrived to journey level");
    //Second Motion
    if (Th->rows() > 0) {
        qEs=Th->row(Th->rows() - 1);
    }
    else {
        qEs=receive_joint_state();
    }
    Vector3d start2=xEf;
    start2(2)=0.5;
    //inv=HORIZONTAL;
    inv=HORIZONTAL;
    double limit=0.3;
    /*bool velocity=true;
    if (abs(start1(0)-start2(0))>limit) {
        velocity=false;
    }*/
    /*if(!linear_interpolation(qEs, start1, start2, phiEf, tStart(1), tEnd(1), Th)) {
        RCLCPP_ERROR(node->get_logger(), "Second motion failed!");
        return false;
    }*/
    if(!cartesianInterpolation(qEs.transpose(), start2, phiEf, tStart(1), tEnd(1), Th, false, inv, startFrameZ)) {
        RCLCPP_ERROR(node->get_logger(), "Second motion failed!");
        return false;
    }
    RCLCPP_INFO(node->get_logger(), "Computation arrived to destination level");
    //Third Motion
    if (Th->rows() > 0) {
        qEs=Th->row(Th->rows() - 1);
    }
    else {
        qEs=receive_joint_state();
    }
    /*if(!linear_interpolation(qEs, start2, xEf, phiEf, tStart(2), tEnd(2), Th)) {
        RCLCPP_ERROR(node->get_logger(), "Third motion failed!");
        return false;
    }*/
    inv=VERTICAL;
    if(!p2pMotionPlan(qEs.transpose(), xEf, phiEf, tStart(2), tEnd(2), Th, true, inv, startFrameZ)) {
        RCLCPP_ERROR(node->get_logger(), "Third motion failed!");
        return false;
    }
    RCLCPP_INFO(node->get_logger(), "Computation arrived to destination");
    return true;
}

void oneIteration(std::shared_ptr<rclcpp::Node> node) {
    cout << "In ONE ITERATION" << endl;
    Vector3d posDest{{finalPos.x, finalPos.y, finalPos.z}};
    Vector3d posBlock{{blockPos.x, blockPos.y, blockPos.z}};
    //Vector3d phiDefault{{0.0, 0.0, 0.0}};
    MatrixD6 th;
    Matrix16 configurationHome;
    //Spawning position
    configurationHome << -1.3, -1.82, -2.1, -0.775, -M_PI_2, 0.0;
    //0.5, 0.131, 0.0 -> 0.0, 0.2185, -0.5
    //(-0.5, -0.35, -0.5)
    Matrix16 qEs=receive_joint_state();
    //p2pMotionPlan(qEs.transpose(), posHome, phiEf, MINT, MAXT, &th, true);
    //auto [tras, rot]=Ur5Direct(configurationHome);
    //linear_interpolation(qEs.transpose(), posHome, posHome, phiEf, MINT, MAXT, &th);
        //return false;
    send_trajectory(configurationHome, node);
    //std::cout << "configurationHome size: " << configurationHome.rows() << "x" << configurationHome.cols() << std::endl;
    //std::cout << "qEs size: " << qEs.rows() << "x" << qEs.cols() << std::endl;
    /*if (!configurationHome.isApprox(qEs, 1e-2)) {
        send_trajectory(configurationHome.transpose(), node);
    }*/
    pair<Vector3d, Matrix3d> home=Ur5Direct(configurationHome);
    auto gripper=std::make_shared<GripperCommunicator>();
    RCLCPP_INFO(node->get_logger(), "Checking Position");
    //gripper->rotate_gripper(startFrameZ);
    //while(1) {
    //    gripper->rotate_gripper(0.9);
    //}
    bool cond[3]={true, true, true};
    //if(checkPosition(block, qEs)) {
        if (th.rows() > 0) {
            qEs=(th.row(th.rows() - 1));
        }
        else {
            qEs=configurationHome;
        }
        while(th.size()>1) {
            removeRow(&th, 0);
        }
        RCLCPP_INFO(node->get_logger(), "Reachable Position");
        gripper->open();
        //To Block
        cout << th << endl;
        cond[0]=motion(qEs, posHome, posBlock, phiEf, MINT, MAXT, &th, node);
        if(cond[0]){
            RCLCPP_INFO(node->get_logger(), "Check matrix");
            cout << th << endl;
            send_trajectory(th, node);
            if (th.rows() > 0) {
                qEs=(th.row(th.rows() - 1)).transpose();
            }
            else {
                qEs=receive_joint_state();
            }
            while(th.size()>1) {
                removeRow(&th, 0);
            }
            gripper->close();
            startFrameZ=0.0;
            //To Dest
            cond[1]=motion(qEs, posBlock, posDest, phiEf, MINT, MAXT, &th, node);
        }
        if(cond[0] && cond[1]) {
            send_trajectory(th, node);
            if (th.rows() > 0) {
                qEs=(th.row(th.rows() - 1)).transpose();
            }
            else {
                qEs=receive_joint_state();
            }
            while(th.size()>1) {
                removeRow(&th, 0);
            }
            gripper->open();
            //To Home
            cond[2]=motion(qEs, posDest, posHome, phiEf, MINT, MAXT, &th, node);
            
        }
        if(cond[0] && cond[1] && cond[2]) {
            send_trajectory(th, node);
            while(th.size()>1) {
                removeRow(&th, 0);
            }
        }
        else {
            RCLCPP_INFO(node->get_logger(), "ERROR in Trajectory Computation");
            rclcpp::shutdown();
            exit(1);
        }
    //}
   /* else {
        RCLCPP_INFO(node->get_logger(), "Unreachable Point, ERROR Occuring");
        rclcpp::shutdown();
        exit(1);
    }*/
}

Point2D findCenter(Point2D pmin, Point2D pmax){
    Point2D tmp;
    tmp.x = (pmax.x-pmin.x)/2 + pmin.x;
    tmp.y = (pmax.y-pmin.y)/2 + pmin.y;
    return tmp;
}

ConversionClient::ConversionClient() : Node("conversion_client"){
    // Initialization of the client service
    client_ = this->create_client<vision_ws_msgs::srv::Convert2din3d>("/convert_coordinates");

    // Log message to report client startup
    RCLCPP_INFO(this->get_logger(), "Conversion client ready to send requests.");
}

std::shared_future<std::shared_ptr<vision_ws_msgs::srv::Convert2din3d::Response>> ConversionClient::sendRequest(Point2D pmin, Point2D pmax, string image_path){
    // Creating a Service Request
    auto request = std::make_shared<vision_ws_msgs::srv::Convert2din3d::Request>();
    request->upperleft.x=pmin.x;
    request->upperleft.y=pmin.y;
    request->bottomright.x=pmax.x;
    request->bottomright.y=pmax.y;
    request->image_path=image_path;
    // Verify that the service is available
    while (!client_->wait_for_service(std::chrono::seconds(10)))
    {
        RCLCPP_WARN(this->get_logger(), "Waiting for the 'Conversion from 2d to 3d' service to be available...");
    }

    // Sending the asynchronous request and returning the future
    return client_->async_send_request(request);
}

bool ConversionClient::spinUntilFutureComplete(std::shared_future<std::shared_ptr<vision_ws_msgs::srv::Convert2din3d::Response>> future){
    // Wait until the result is available
    auto spin_result = rclcpp::spin_until_future_complete(this->get_node_base_interface(), future);

    // Checks the status of the future and returns true if completed successfully
    if (spin_result == rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(this->get_logger(), "Service call completed successfully.");
        return true;
    }
    else
    {
        RCLCPP_ERROR(this->get_logger(), "Service call failed.");
        return false;
    }
}

YoloClient::YoloClient() : Node("yolo_client"){
    // Initialization of the client service
    client_ = this->create_client<vision_ws_msgs::srv::Boundingbox>("yolo_bounding_box_service");
    // Log message to report client startup
    RCLCPP_INFO(this->get_logger(), "Boundingbox client ready to send requests.");
}
std::shared_future<std::shared_ptr<vision_ws_msgs::srv::Boundingbox::Response>> YoloClient::sendRequest(string image_path){
    // Creating a Service Request
    auto request = std::make_shared<vision_ws_msgs::srv::Boundingbox::Request>();
    request->image_path=image_path;
    // Verify that the service is available
    while (!client_->wait_for_service(std::chrono::seconds(10)))
    {
        RCLCPP_WARN(this->get_logger(), "Waiting for the 'Boundingbox' service to be available...");
    }
    // Sending the asynchronous request and returning the future
    return client_->async_send_request(request);
}
bool YoloClient::spinUntilFutureComplete(std::shared_future<std::shared_ptr<vision_ws_msgs::srv::Boundingbox::Response>> future){
    // Wait until the result is available
    auto spin_result = rclcpp::spin_until_future_complete(this->get_node_base_interface(), future);
    // Checks the status of the future and returns true if completed successfully
    if (spin_result == rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(this->get_logger(), "Service call completed successfully.");
        return true;
    }
    else
    {
        RCLCPP_ERROR(this->get_logger(), "Service call failed.");
        return false;
    }
}
