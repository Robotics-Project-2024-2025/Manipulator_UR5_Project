import rclpy
from rclpy.node import Node
from vision_ws_msgs.srv import Boundingbox
from vision_ws_msgs.msg import Boundstruct
import torch
from yolov5.models.common import DetectMultiBackend
from yolov5.utils.general import non_max_suppression, scale_boxes, check_img_size, LOGGER
from yolov5.utils.torch_utils import select_device
from yolov5.utils.dataloaders import LoadImages
import cv2
import numpy as np


class YoloBoundingBoxService(Node):
    def __init__(self):
        super().__init__('yolo_bounding_box_service')

        # YOLOv5 configuration
        weights = "/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/blockTrain.pt"
        data = "/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/yolov5/data/coco128.yaml"
        imgsz = (1900,1080)  # da cambiare
        conf_thres = 0.7  # Confidence threshold
        iou_thres = 0.45  # IoU threshold
        max_det = 1000  # non so quante volgiamo metterne
        device = select_device("")  # Auto-select device (GPU if available)

        # Load YOLOv5 model with DetectMultiBackend
        self.model = DetectMultiBackend(weights, device=device, data=data, fp16=False)
        self.imgsz = check_img_size(imgsz, s=self.model.stride)
        self.conf_thres = conf_thres
        self.iou_thres = iou_thres
        self.max_det = max_det
        self.get_logger().info("YOLOv5 model loaded successfully.")

        # Create the ROS 2 service
        self.service = self.create_service(Boundingbox, 'yolo_bounding_box_service', self.handle_bounding_boxes_request)
        self.get_logger().info('YOLO Bounding Box Service is ready!')

    def handle_bounding_boxes_request(self, request, response):
        image_path = request.image_path
        try:
            # Load and preprocess the image
            dataset = LoadImages(image_path, img_size=self.imgsz, stride=self.model.stride, auto=True)
            for path, im, im0s, vid_cap, s in dataset:
                im = torch.from_numpy(im).to(self.model.device)
                im = im.half() if self.model.fp16 else im.float()  # Convert to FP16/FP32
                im /= 255.0  # Normalize to [0, 1]
                if len(im.shape) == 3:
                    im = im[None]  # Add batch dimension
                # Perform inference
                pred = self.model(im)

                # Apply Non-Max Suppression (NMS)
                pred = non_max_suppression(pred, self.conf_thres, self.iou_thres, max_det=self.max_det)

                # Extract bounding box data
                for det in pred:  # Process each detection
                    if det is not None and len(det):
                        det[:, :4] = scale_boxes(im.shape[2:], det[:, :4], im0s.shape).round()
                        for *box, conf, cls in det:
                  
                            bbox = Boundstruct()
                            bbox.class_id =int(cls)
                            bbox.confidence = float(conf.item())
                            bbox.xmin = float(box[0].item())
                            bbox.ymin = float(box[1].item())
                            bbox.xmax = float(box[2].item())
                            bbox.ymax = float(box[3].item())
                            response.boxes.append(bbox)

                self.get_logger().info(f"Processed image {image_path} with {len(response.boxes)} bounding boxes.")
        except Exception as e:
            self.get_logger().error(f"Error processing image {image_path}: {e}")
        
        img = cv2.imread(request.image_path)
        
        for bbox in response.boxes:
            xmin, ymin, xmax, ymax = int(bbox.xmin), int(bbox.ymin), int(bbox.xmax), int(bbox.ymax)
            cv2.rectangle(img, (xmin, ymin), (xmax, ymax), (255, 0, 0), 2)  # Draw rectangles
            
        dest_path = "/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/generated/Yolo1.png"
        cv2.imwrite(dest_path, img)
        
        return response

def main(args=None):
    rclpy.init(args=args)
    try:
        node = YoloBoundingBoxService()
        rclpy.spin(node)
    except Exception as e:
        print(f"Error during node initialization: {e}")
    finally:
        rclpy.shutdown()

if __name__ == '__main__':
    main()
