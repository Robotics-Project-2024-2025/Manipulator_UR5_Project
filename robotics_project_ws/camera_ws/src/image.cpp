//
//  image.cpp
//  Camera
//
//  Created by Matteo Gottardelli on 06/12/24.
//

#include "image.h"

ImageCamera::ImageCamera() : Node ("image_acquiring") {
    image_receiver_=this->create_subscription<senseimage>("/camera/image_raw", 1, [this](shared_ptr<senseimage> msg) {
        image_content_=const_pointer_cast<const senseimage>(msg);
        RCLCPP_INFO(this->get_logger(), "Received Image message");
        cout << "Received Image message" << endl;
    });
    while(rclcpp::ok() && !image_content_) {
        rclcpp::spin_some(this->get_node_base_interface());
    }
    if(image_content_) {
        RCLCPP_INFO(this->get_logger(), "Successfully Received image");
        cout << "Successfully Received image" << endl;
    }
}
void ImageCamera::generateOutput() {
    string filename;
    filename.append("/generated/");
    filename.append(to_string(counter_id));
    filename.append(".png");
    printOnFile(filename);
}
void ImageCamera::printOnFile(string filename) {
    /*std_msgs/Header header
     uint32 height
     uint32 width
     string encoding
     uint8 is_bigendian
     uint32 step
     uint8[] data*/
    FILE* file;
    file=fopen(filename, a+);
    if(file==NULL) {
        cerr << "Couldn't open or create the file" << endl;
        exit(1);
    }
    //HEADER
    fprintf(file, "%d %d %d %s\n", image_content_->header.seq, image_content_->header.stamp.seconds, image_content_->header.stamp.nanoseconds, image_content_->header.frame_id);
    //HEIGHT
    fprintf(file, "%d\n", image_content_->height);
    //WIDTH
    fprintf(file, "%d\n", image_content_->width);
    //ENCODING
    fprintf(file, "%s\n", image_content_->encoding);
    //IS_BIGENDIAN
    fprintf(file, "%d\n", image_content_->is_bigendian);
    //STEP
    fprintf(file, "%d\n", image_content_->step);
    //DATA
    for (int i=0; i<image_content_->height; i++) {
        for (int j=0; j<image_content_->step; j++) {
            fprintf(file, "%-3d ", image_content_->data[i+j*image_content_->step]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}
shared_ptr<const senseimage> ImageCamera::get_image_content() const {
    return image_content_
}
int main (int argc, const char* argv[]) {
    rclcpp::init(argc, argv);
    cout << "Requesting Image" << endl;
    auto node=make_shared<ImageCamera>();
    auto image_result_=node->get_image_content();
    if(image_result!=NULL) {
        RCLCPP_INFO(rclcpp::get_logger("main"), "Image Received");
        generateOutput();
    }
    else {
        RCLCPP_WARN(rclcpp::get_logger("main"), "No Image Received.");
    }
    rclcpp:shutdown();
    cout << "End Image Receiving" << endl;
    return 0;
}
