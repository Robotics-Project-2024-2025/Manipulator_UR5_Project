#include "block_spawner.h"
BlockSpawn::BlockSpawn(const string& path): Node("block_spawning") {
    RCLCPP_INFO(this->get_logger(), "BlockSpawner Node Initialized");
    gazebo_msgs::SpawnModel spawner;
    spawner.request.model_name=random_name();
    spawner.request.model_xml="/home/ubuntu/ros2_ws/src/ros2_ur5_interface/package.xml";
    block_spawner_ = this->create_subscription<msgs::Factory>(
    "/block_spawner_node/spawn", 100,
        std::bind(&BlockSpawn::spawnCallback, this, std::placeholders::_1)
    );
    rclcpp::spin_some(this->get_node_base_interface());
}
string random_name() {
    stringstream ss;
    ss << hex << rand();
    return ss.str();
}
int main (int argc, const char* argv[]) {
    rclcpp::init(argc, argv);
    cout << "Start Spawning Blocks" << endl;
    RCLCPP_INFO(this->get_logger(), "Spawn Blocks");
    auto node=make_shared<BlockSpawn>("/home/ubuntu/ros2_ws/src/ros2_ur5_interface/models/meshed");
    try {
        while(rclcpp::ok()) {
            rclcpp::spinOnce();
        }
        cout << "End Spawning Blocks" << endl;
    }
    catch (const exception& e) {
        RCLCPP_ERROR(this->get_logger(), "Error: %s", e.what());
    }
    rclcpp::shutdown();
    return 0;
}

