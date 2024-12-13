#include "gz_ros2_control/gz_ros2_control.hpp"
#include "rclcpp/rclcpp.hpp"
#include "ros2_control/gazebo_system.hpp"

class MyGazeboControlNode : public rclcpp::Node
{
public:
    MyGazeboControlNode()
    : Node("gazebo_control_node")
    {
        // Example of initializing Gazebo and ROS 2 control integration
        gazebo_system_ = std::make_shared<ros2_control::GazeboSystem>(this);
        
        // Initialize your control system, load controllers, etc.
        RCLCPP_INFO(this->get_logger(), "Gazebo and ROS 2 control system initialized.");
    }

private:
    std::shared_ptr<ros2_control::GazeboSystem> gazebo_system_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MyGazeboControlNode>());
    rclcpp::shutdown();
    return 0;
}
