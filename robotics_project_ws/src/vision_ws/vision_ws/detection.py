import rclpy
import sys
import torch
from rclpy.node import Node
from vision_ws_msgs.srv import Boundingbox

#from vision_ws_msgs.msg import Boundstruct
#from ultralytics import YOLO
from yolov5 import YOLOv5

class YoloBoundingBoxService(Node):
    def __init__(self):
        super().__init__('yolo_bounding_box_service')
        # Load YOLO model
        self.model = YOLOv5('/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/blockTrain.pt')
        self.service = self.create_service(Boundingbox, 'get_bounding_boxes', self.handle_bounding_boxes_request)
        self.get_logger().info('YOLO Bounding Box Service is ready!')

    def handle_bounding_boxes_request(self, request, response):
        # Run YOLO inference (replace 'image.jpg' with your image source)
        results = self.model(request.image_path)

        bounding_boxes = []
        for result in results[0].boxes:
            box = result.xyxy[0].cpu().numpy()  # [xmin, ymin, xmax, ymax]
            confidence = result.conf.cpu().item()
            class_id = int(result.cls.cpu().item())

            bounding_box_data = {
                'class_id': class_id,
                'confidence': confidence,
                'xmin': box[0],
                'ymin': box[1],
                'xmax': box[2],
                'ymax': box[3],
            }
            bounding_boxes.append(bounding_box_data)

        # Log and return the bounding boxes
        response.boxes=bounding_boxes
        self.get_logger().info(f"Processed image {request.image_path} with {len(bounding_boxes)} bounding boxes.")
        
        return response

def main(args=None):
    rclpy.init(args=args)
    try:
        node = YoloBoundingBoxService()

        try:
            from vision_ws_msgs.srv import Boundingbox
            from vision_ws_msgs.msg import Boundstruct
            node.get_logger().info("ROS 2 message imports successful.")
        except ImportError as e:
            node.get_logger().error(f"Failed to import ROS 2 messages: {e}")

        rclpy.spin(node)
        node.destroy_node()
    except Exception as e:
        print(f"Error during node initialization: {e}")
    finally:
        rclpy.shutdown()

if __name__ == '__main__':
    main()
