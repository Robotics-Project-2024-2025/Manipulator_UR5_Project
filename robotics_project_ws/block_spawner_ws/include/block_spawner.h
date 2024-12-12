#ifndef __BLOCK_SPAWNER_H__
#define __BLOCK_SPAWNER_H__

#include <rclcpp.hpp>
#include <string>
#include <Eigen/Dense>
#include "gazebo/physics/physics.hh"
#include "gazebo/common/common.hh"
#include "gazebo/gazebo.hh"
#include <gazebo_msgs/SpawnModel.h>
#include <gazebo_msgs/SetModelState.h>
#include <gazebo_msgs/GetModelState.h>
#include <gazebo_msgs/GetWorldProperties.h>
#include <gazebo_msgs/DeleteModel.h>
#include <tf/transform_datatypes.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <sstream>
#include <iomanip>

#define NUM_BLOCKS 5
#define MINIMUM_DISTANCE_BLOCK 0.15
#define BORDER_DISTANCE 0.05
#define DISTANCE_BOTTOM 0.4
#define X_MIN 0
#define X_MAX 0.5
#define Y_MIN 0
#define Y_MAX 0.4
#define Z_MIN 0.87
#define Z_MAX 0.87
using namespace std;
using namespace gazebo {
struct BlockSize {
    double x;
    double y;
    double z;
};
struct BlockPosition {
    string name;
    Vector3d wPosition;
}
class BlockSpawn : public rclcpp::Node : public WorldPlugin {
public:
    BlockSpawn(const string& path);
    void Load(physics::WorldPtr _parent, sdf::ElementPtr) {
        initVariables(physics::WorldPtr _parent);
        generateBlocks();
        block_spawner_=this->create_subscription<msgs::Factory>("/block_spawner_node/spawn", 100, [this](shared_ptr<msgs::Factory> msg){
            factory_= const_pointer_cast<const msgs::Factory>(msg);
            RCLCPP_INFO(this->get_logger(), "Set Block Spawning Message");
        });
        while (rclcpp::ok() && !block_spawner_) {
            rclcpp::spin_some(this->get_node_base_interface());
        }
        if(block_spawner_) {
            RCLCPP_INFO(this->get_logger(), "Successfully Spawned Blocks");
            cout << "Successfully Spawned Blocks" << endl;
        }
    }
    
private:
    vector<string> validBlocks;
    map<string, gazebo::BlockSize> brickDefinition;
    physics::WorldPtr worldPtr;
    shared_ptr<rclcpp::Subscription<msgs::Factory>> block_spawner_;
    shared_ptr<const msgs::Factory> factory_;
    vector<gazebo::BlockPosition> addedBuffer;
    vector<Vector3d> populateVector() {
        //To implement reading in C++
    }
    void initVariables(physics::WorldPtr _parent) {
        this->validBlocks.clear();
        vector<string> names={"X1-Y1-Z2", "X1-Y2-Z1", "X1-Y2-Z2-CHAMFER", "X1-Y2-Z2-TWINFILLET", "X1-Y2-Z2", "X1-Y3-Z2-FILLET", "X1-Y3-Z2", "X1-Y4-Z1", "X1-Y4-Z2", "X2-Y2-Z2-FILLET", "X2-Y2-Z2"};
        vector<Vector3d> vectors=populateVector();
        for(int i=0; i<names.size(); i++) {
            this->validBlocks.pushBack("model://"+names[i]);
            this->brickDefinition(pair<string, gazebo::BlockSize>("model://"+names[i], vectors[i]));
        }
        this->worldPtr=_parent;
    }
    void generateBlocks() {
        
    }
    void spawnCallback(const shared_ptr<msgs::Factory>& msg) {
       factory_ = msg;
       RCLCPP_INFO(this->get_logger(), "Received block spawn message: %s", factory_->name.c_str());
       generateBlocks();
   }
}
string random_name();
float random_position(float min, float max);
#endif
