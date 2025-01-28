import cv2
import numpy as np

# Constants
TABLE_DEFAULT = [[175, 88], [423, 81], [635, 288], [19, 313]]  # Original table points
PERCENTAGE=0.25
OFFSET = 25  # Padding around the table mask

# Paths
image_path = "/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/Image1.png"
image_resize_path = "/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/Resize1.png"
no_back_path = "/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/NoBack1.png"
dest_path = "/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/DectImage1.png"

# Load the original image
img = cv2.imread(image_path)

# Resize the image
resize_width, resize_height = 1900, 1080
resized_img = cv2.resize(img, (resize_width, resize_height))
cv2.imwrite(image_resize_path, resized_img)

# Scale TABLE_DEFAULT points to match the resized image
TABLE_RESIZED = []
for point in TABLE_DEFAULT:
    new_x = int(point[0] * resize_width / 640)  # Scale x-coordinate
    new_y = int(point[1] * resize_height / 360)  # Scale y-coordinate
    TABLE_RESIZED.append([new_x, new_y])

# Adjust TABLE_RESIZED with the OFFSET
min_x = max(0, min([p[0] for p in TABLE_RESIZED]) - OFFSET)
max_x = min(resize_width - 1, max([p[0] for p in TABLE_RESIZED]) + OFFSET)
min_y = max(0, min([p[1] for p in TABLE_RESIZED]) - OFFSET)
max_y = min(resize_height - 1, max([p[1] for p in TABLE_RESIZED]) + OFFSET)

# Create a polygon mask
mask = np.array(TABLE_RESIZED, dtype=np.int32)
#mask = np.array(TABLE_DEFAULT, dtype=np.int32)
background = np.zeros((resize_height, resize_width), dtype=np.uint8)
#background = np.zeros((360, 640), dtype=np.uint8)
cv2.fillPoly(background, [mask], 255)  # Fill the polygon with white
mask_background = cv2.inRange(background, 1, 255)

# Extract the region of interest (ROI)
roi = cv2.bitwise_and(resized_img, resized_img, mask=mask_background)
#roi = cv2.bitwise_and(img, img, mask=mask_background)
cv2.imwrite(no_back_path, roi)

for y in range(int(roi.shape[0]*PERCENTAGE)):
    roi[y] = 0

cv2.imwrite(dest_path, roi)

image=cv2.imread(dest_path)
hsv_image=cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
color_ranges = {
    'red': [(0, 50, 50), (10, 255, 255)], # Hue range: 0-10
    'green': [(36, 50, 50), (70, 255, 255)], # Hue range: 36-70
    'blue': [(90, 50, 50), (130, 255, 255)], # Hue range: 90-130
    'yellow': [(20, 50, 50), (35, 255, 255)], # Hue range: 20-35
    'magenta': [(290, 50, 50), (310, 255, 255)], # Hue range: 290-310
    'orange': [(11, 50, 50), (25, 255, 255)], # Hue range: 11-25
    'cyan': [(170, 50, 50), (190, 255, 255)],  # Hue range: 170-190
    'pink': [(330, 50, 50), (350, 255, 255)],  # Hue range: 330-350
    'brown': [(20, 50, 50), (40, 255, 255)],  # Hue range: 20-40
    'light_green': [(80, 50, 50), (100, 255, 255)]  # Hue range: 80-100

}
mask = np.zeros(image.shape[:2], dtype=np.uint8)
    
for color_range in color_ranges.values():
    lower_color = np.array(color_range[0])
    upper_color = np.array(color_range[1])
    color_mask = cv2.inRange(hsv_image, lower_color, upper_color)
    mask = cv2.bitwise_or(mask, color_mask)

result = cv2.bitwise_and(image, image, mask=mask)
background = np.zeros_like(image)
background[mask == 0] = [0, 0, 0]
image=cv2.add(result, background)

dest_image="/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/OnlyBlocks1.png"
cv2.imwrite(dest_image, image)
        
        
