import rclpy
import sys
import torch
import math
import time
from statistics import mean
from rclpy.node import Node
from vision_ws_msgs.srv import Convert2din3d
from vision_ws_msgs.msg import Point2d
from sensor_msgs_py import point_cloud2
from sensor_msgs.msg import PointCloud2
from sensor_msgs.msg import Image
from sensor_msgs.msg import CameraInfo
from copy import deepcopy
from cv_bridge import CvBridge
#from vision_ws_msgs.msg import Boundstruct
#from ultralytics import YOLO
import yolov5
import cv2
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


class ConvertRealCoordinates(Node):
    def __init__(self):
        super().__init__('convert_coordinates')
        self.service=self.create_service(Convert2din3d, 'convert_coordinates', self.process_object_box_request)
        self.get_logger().info('Convertion 2d to 3d Service is ready!')
    
    def get_point_cloud_msg(self, node, topic):
        future=rclpy.task.Future()
        
        def callback(msg):
            future.set_result(msg)
            
        subscription=node.create_subscription(PointCloud2, topic, callback, 10)
        try:
            rclpy.spin_until_future_complete(node, future)
            if future.done():
                return future.result()
        finally:
            node.destroy_subscription(subscription)
        return None

    def get_camera_info(self, node, topic):
        future=rclpy.task.Future()
        
        def callback(msg):
            future.set_result(msg)
            
        subscription=node.create_subscription(CameraInfo, topic, callback, 10)
        try:
            rclpy.spin_until_future_complete(node, future)
            if future.done():
                return future.result()
        finally:
            node.destroy_subscription(subscription)
        return None
     
    def get_depth(self, node, topic):
        future=rclpy.task.Future()
        
        def callback(msg):
            future.set_result(msg)
            
        subscription=node.create_subscription(Image, topic, callback, 10)
        try:
            rclpy.spin_until_future_complete(node, future)
            if future.done():
                return future.result()
        finally:
            node.destroy_subscription(subscription)
        return None
     
    def convert_to_gazebo_world_frame(self, points: list) -> list:
        node=rclpy.create_node('point_cloud_message_receiver')
        try:
            point_cloud_msg=self.get_point_cloud_msg(node, "/camera/image_raw/points")
            if point_cloud_msg:
                node.get_logger().info("Successfully received a PointCloud2 message!")
            else:
                node.get_logger().warn("No message received.")
        finally:
            node.destroy_node()
    
        node=rclpy.create_node('camera_info_capture')
        try:
            camera_info=self.get_camera_info(node, "camera/image_raw/camera_info")
            if camera_info:
                node.get_logger().info("Successfully received a Camera Info message!")
        finally:
            node.destroy_node()

        fx = camera_info.k[0]
        fy = camera_info.k[4]
        cx = camera_info.k[2]
        cy = camera_info.k[5]
        
        self.get_logger().info(f'Camera Info:')
        self.get_logger().info(f'Focal Length (fx, fy): ({fx}, {fy})')
        self.get_logger().info(f'Principal Point (cx, cy): ({cx}, {cy})')
        self.get_logger().info(f'Camera Matrix (K): {camera_info.k}')
        self.get_logger().info(f'Distortion Coefficients: {camera_info.d}')
        self.get_logger().info(f'Image Dimensions (width, height): ({camera_info.width}, {camera_info.height})')
        self.get_logger().info(f'Header: {camera_info.header}')
        camera_position=[-0.5, 0.5, 1.2]
        camera_orientation=[0.0, 0.4, -0.06]
        
        node=rclpy.create_node('camera_depth_capture')
        try:
            self.bridge = CvBridge()
            depth=self.get_depth(node, "camera/image_raw/depth_image")
            if camera_info:
                node.get_logger().info("Successfully received Depth message!")
        finally:
            node.destroy_node()
        depth_image=self.bridge.imgmsg_to_cv2(depth, desired_encoding="passthrough")

        scale_x = depth_image.shape[1] / 1900.0  # 640 / 1900
        scale_y = depth_image.shape[0] / 1080.0
                #v rows, u columns
        points_3D=[]
        for u, v in points:
            u_depth = int(u * scale_x)
            v_depth = int(v * scale_y)
            if 0 <= u_depth < depth_image.shape[1] and 0 <= v_depth < depth_image.shape[0]:
                depth_value=depth_image[v_depth, u_depth]
                if depth_value > 0:
                    #self.get_logger().info(f"Depth at (u={u}, v={v}): {depth_value} meters")
                    X=(u_depth-cx)*depth_value/fx
                    Y=(v_depth-cy)*depth_value/fy
                    Z=depth_value
                    points_3D.append([X, Y, Z])
                else:
                    self.get_logger().warn(f"Invalid depth value at (u={u}, v={v})")
            else:
                self.get_logger().warn(f"Depth coordinate (u={u_depth}, v={v_depth}) is out of bounds!")
        #Array of camera points - convertion in real world
        #world_point=R*camera_point+T
        from scipy.spatial.transform import Rotation as R
        rotation = R.from_euler('xyz', camera_orientation).as_matrix()
        translation = np.array(camera_position)
        
        precision=5
        
        points_world = []
        for point in points_3D:
            point_camera = np.array(point)
            point_world = np.dot(rotation, point_camera) + translation
            points_world.append([round(coord, precision) for coord in point_world])
      
        print(f"Converted points in Gazebo world frame")
        return points_world if len(points_world) > 1 else points_world[0]
    
    def linear_operation(self, p1: tuple, p2: tuple) -> tuple:
        if p1[0]==p2[0]:
            return 1,0
        
        m=(p2[1]-p1[1])/(p2[0]-p1[0])
        q=p1[1]-m*p1[0]
        return m,q
    
    def verify_points(self, points):
        height, width=1080, 1900
        blank_image = np.ones((height, width, 3), dtype=np.uint8) * 255
        for point in points:
             if 0 <= point[0] < width and 0 <= point[1] < height:
                blank_image[point[1], point[0]] = (0, 0, 255)
        cv2.imwrite("/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/generated/Verify1.png", blank_image)
        cv2.waitKey(0)
            
    def process_object_box_request(self, request, response):
        self.get_logger().info(f"UPPERLEFT: {request.upperleft.x} {request.upperleft.y} BOTTOMRIGHT: {request.bottomright.x} {request.bottomright.y}")
        image=cv2.imread(request.image_path)
        box=[(request.upperleft.x, request.upperleft.y), (request.upperleft.x, request.bottomright.y), (request.bottomright.x, request.upperleft.y), (request.bottomright.x, request.bottomright.y)]
        
        min_x = min(box, key=lambda x: x[0])[0]
        max_x = max(box, key=lambda x: x[0])[0]

        min_y = min(box, key=lambda x: x[1])[1]
        max_y = max(box, key=lambda x: x[1])[1]
        
        clean_image=image.copy()
        process_image=image[min_y : max_y+1, min_x : max_x+1]
        gray = cv2.cvtColor(process_image, cv2.COLOR_BGR2GRAY)
        _, binary_mask = cv2.threshold(gray, 1, 255, cv2.THRESH_BINARY)
        contours, _ = cv2.findContours(binary_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        contours = sorted(contours, key=cv2.contourArea, reverse=True)
        contours.pop(0)
        for contour in contours:
            cv2.drawContours(image, [contour], 0, (0, 0, 0), -1)
        clean_image[min_y : max_y+1, min_x : max_x+1] = process_image
        
        dest_path = "/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/generated/Elaborate1.png"
        cv2.imwrite(dest_path, process_image)
        image=clean_image
        
        points_2D = []
        for x in range(min_x, max_x+1):
            for y in range(min_y, max_y+1):
                if clean_image[y,x].tolist() != [0,0,0]:
                    #print(f"Point: {x} {y}")
                    points_2D.append([x,y])
        
        if not len(points_2D):
            raise ValueError("No valid 2D points found in the processed image!")
        self.verify_points(points_2D)
        points_3D=self.convert_to_gazebo_world_frame(points=points_2D)

        #Association to each correspondence
        points=[[points_2D[i], points_3D[i]] for i in range(len(points_2D))]
        #image rows
        rows=[]

        #center
        center_max_x = max(points, key=lambda x: x[1][0])
        center_min_x = min(points, key=lambda x: x[1][0])

        center_max_y = max(points, key=lambda x: x[1][1])
        center_min_y = min(points, key=lambda x: x[1][1])

        center_max_z = max(points, key=lambda x: x[1][2])
        center_min_z = min(points, key=lambda x: x[1][2])
        
        a = (center_min_x[1][0], center_min_y[1][1])
        b = (center_min_x[1][0], center_max_y[1][1])
        c = (center_max_x[1][0], center_max_y[1][1])
        d = (center_max_x[1][0], center_min_y[1][1])
        
        m_bd, q_bd = self.linear_operation(b, d)
        m_ac, q_ac = self.linear_operation(a, c)
        
        center_x = (q_bd - q_ac) / (m_ac - m_bd)
        center_y = m_ac * center_x + q_ac
        center_z = center_max_z[1][2]

        center = (center_x, center_y, center_z)
        center = min(points, key=lambda x: math.dist(x[1], center))
        
        center_2D, center_3D = center
        
        tolerance = 1e-5
        scale=1900.0/640.0
        bottom_row_points = [point for point in points if abs(point[0][1] - max_y) < tolerance]
        most_right_pixel = max(bottom_row_points, key=lambda point: point[0][0])[0]
        basePixel=most_right_pixel
        
        left_column_points=[point for point in points if abs(point[0][0]-(min_x+5*int(scale)))<tolerance]
        most_bottom_left_pixel=max(left_column_points, key=lambda point: point[0][1])[0]
       
        right_column_points=[point for point in points if abs(point[0][0]-(max_x-5*int(scale)))<tolerance]
        most_bottom_right_pixel=max(right_column_points, key=lambda point: point[0][1])[0]
        
        column_base=[point for point in points if abs(point[0][0]-basePixel[0])<tolerance]
        upper_column_base=min(column_base, key=lambda point: point[0][1])[0]
        
        x_side=basePixel[0]-most_bottom_right_pixel[0]
        y_side=basePixel[1]-most_bottom_right_pixel[1]
        angle_rad = math.atan2(x_side, y_side)
        angle_deg=math.degrees(angle_rad)
        #? COLORS
        thickness = 1

        green = (0,255,0)
        blue = (255, 0, 0)
        red = (0, 0, 255)

        cv2.line(image, most_bottom_left_pixel, basePixel, green, thickness)
        cv2.line(image, basePixel, most_bottom_right_pixel, red, thickness)
        cv2.line(image, basePixel, upper_column_base, blue, thickness)
        
        response.x=center_3D[0]+0.5 #Adjustment because camera is distant 0.5 from the table
        response.y=center_3D[1]
        response.z=center_3D[2]
        response.rotation=angle_rad
        response.success=True
        
        print(f"Position: {(response.x, response.y, response.z)} \nOrientation {angle_rad}\nOrientation (deg): {angle_deg}")
        
        final_path = "/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/generated/Obj1.png"
        cv2.imwrite(final_path, image)
        return response
        
def main(args=None):
    rclpy.init(args=args)
    try:
        node = ConvertRealCoordinates()

        try:
            from vision_ws_msgs.srv import Convert2din3d
            from vision_ws_msgs.msg import Point2d
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
