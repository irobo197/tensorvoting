# This repository demonstrated how to calculating GPU-based TVF ROS1
A library for tensor voting on 3D point-clouds using GPU (NVIDIA). Running on Ubuntu18.04 and Ubuntu20.04

Please read the full guide in here [here](https://github.com/irobo197/tensorvoting/blob/master/doc/gpu_tv_note.pdf)

If you are interested in the library and its application, please feel free to cite the following two papers:
- M. Liu, "Robotic Online Path Planning on Point Cloud," in IEEE Transactions on Cybernetics, vol. 46, no. 5, pp. 1217-1228, May 2016
- M. Liu, F. Pomerleau, F. Colas and R. Siegwart, "Normal estimation for pointcloud using GPU based sparse tensor voting," 2012 IEEE International Conference on Robotics and Biomimetics (ROBIO), 2012, pp. 91-96

## Installation
**Navigate into the src folder of your ROS workspace and type in the terminal:**
```
git clone https://github.com/irobo197/libnabo.git
```
```
git clone https://github.com/irobo197/libpointmatcher.git
```
```
git clone https://github.com/irobo197/ethzasl_icp_mapping.git
```
**Change version of gcc and g++ if error "unsuppoerted" happens**
- For Ubuntu18.04:
```
sudo update-alternatives --install /usr/bin/cc cc /usr/bin/gcc-6 <proprity-alternatives>
sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-6 <priority-alternatives>
```
- For Ubuntu20.04:
```
sudo update-alternatives --install /usr/bin/cc cc /usr/bin/gcc-8 <priority-alternatives>
sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-8 <priority-alternatives>
```
- Configure alternatives
```
sudo update-alternatives --config cc
```
```
sudo update-alternatives --config c++
```
**Make each folder above according to installation in the link to each repo**
```
SRC_DIR=${PWD}
BUILD_DIR=${SRC_DIR}/build
mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR}
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ${SRC_DIR}
sudo make install
```
**Navigate to _include_ folder of libpointmatcher_ros and type this command**
```
sudo cp -r pointmatcher_ros /usr/local/include
```
**Add cutil_math.h from below into _/usr/include_**
```
https://github.com/kashif/cuda-workshop/blob/master/cutil/inc/cutil_math.h
```
**Navigate back to the main folder of the caktin workspace and compile the packages**
```
catkin_make_isolated
```
