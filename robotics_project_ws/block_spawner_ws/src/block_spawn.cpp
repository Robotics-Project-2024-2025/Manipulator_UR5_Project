#include <rclcpp.hpp>
#include <string>
#include <Eigen/Dense>
#include "gazebo/physics/physics.hh"
#include "gazebo/common/common.hh"
#include "gazebo/gazebo.hh"

#define NUM_BLOCKS 5
#define MINIMUM_DISTANCE_BLOCK 0.15
#define BORDER_DISTANCE 0.05
#define DISTANCE_BOTTOM 0.4
using namespace
namespace gazebo {
struct BlockSize {
    double x;
    double y;
    double z;
};
struct BlockPosition {
    string name;
    Vector3d wPosition;
}
class BlockSpawn : public WorldPlugin {
public:
    BlockSpawn(): nh("block_spawning");
    void Load(physics::WorldPtr _parent, sdf::ElementPtr) {
        this->validBlocks.clear();
        vector<string> names={"X1-Y1-Z2", "X1-Y2-Z1", "X1-Y2-Z2-CHAMFER", "X1-Y2-Z2-TWINFILLET", "X1-Y2-Z2", "X1-Y3-Z2-FILLET", "X1-Y3-Z2", "X1-Y4-Z1", "X1-Y4-Z2", "X2-Y2-Z2-FILLET", "X2-Y2-Z2"};
        vector<Vector3d> vectors={{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
        for(int i=0; i<names.size(); i++) {
            this->validBlocks.pushBack("model://"+names[i]);
            this->brickDefinition(pair<string, gazebo::BlockSize>("model://"+names[i], vectors[i]));
        }
        
    }
    
private:
    vector<string> validBlocks;
    map<string, gazebo::BlockSize> brickDefinition;
}
}
