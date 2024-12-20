from setuptools import find_packages
from setuptools import setup

setup(
    name='move_ws',
    version='1.0.0',
    packages=find_packages(
        include=('move_ws', 'move_ws.*')),
)
