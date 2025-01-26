import cv2
import numpy as np

# Constants
TABLE_DEFAULT = [[175, 88], [423, 81], [635, 288], [19, 313]]  # Original table points
OFFSET = 25  # Padding around the table mask

# Paths
image_path = "/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/Image1.png"
image_resize_path = "/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/Resize1.png"
dest_path = "/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/Unwrap1.png"

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
background = np.zeros((resize_height, resize_width), dtype=np.uint8)
cv2.fillPoly(background, [mask], 255)  # Fill the polygon with white
mask_background = cv2.inRange(background, 1, 255)

# Extract the region of interest (ROI)
roi = cv2.bitwise_and(resized_img, resized_img, mask=mask_background)

# Save the final unwrapped image
cv2.imwrite(dest_path, roi)

# Debugging information (optional)
print("Original Table Points:", TABLE_DEFAULT)
print("Scaled Table Points:", TABLE_RESIZED)
print("Mask boundaries: min_x:", min_x, "max_x:", max_x, "min_y:", min_y, "max_y:", max_y)
