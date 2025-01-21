from setuptools import setup

package_name = 'vision_ws'

setup(
    name=package_name,
    version='0.0.1',
    packages=['vision_ws'],
    install_requires=['setuptools', 'rclpy', 'vision_msgs'],  # Add vision_msgs here
    zip_safe=True,
    data_files=[
        ('share/ament_index/resource_index/ros2.package',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),  # Make sure the Python file is included
    ],
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'detection_service = vision_ws.detection:main',  # The main function in detection.py
        ],
    },
)

