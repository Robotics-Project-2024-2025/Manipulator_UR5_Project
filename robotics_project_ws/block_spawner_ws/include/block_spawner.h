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
using spawning="gazebo_msgs::srv::SpawnModel"
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
class BlockSpawn : public rclcpp::Node {
public:
    BlockSpawn(const string& path);
    
private:
    shared_ptr<rclcpp::Client<spawning>> block_spawner_;
    shared_ptr<const spawning> block_;
}
string random_name();
float random_position(float min, float max);
#endif
