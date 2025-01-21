import rclpy
from rclpy.node import Node
from vision_ws_msgs.srv import Boundingbox
from vision_ws_msgs.msg import Boundstruct
from ultralytics import YOLO

class YoloBoundingBoxService(Node):
    def __init__(self):
        super().__init__('yolo_bounding_box_service')

        # Load YOLO model
        self.model = YOLO('blockTrain.pt')
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
        response.bounding_boxes=bounding_boxes
        self.get_logger().info(f"Processed image {request.image_path} with {len(bounding_boxes)} bounding boxes.")
        
        return response

def main(args=None):
    rclpy.init(args=args)
    node = YoloBoundingBoxService()

    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
