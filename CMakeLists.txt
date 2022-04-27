cmake_minimum_required(VERSION 3.0.2)
project(tensorvoting)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  libnabo
  libpointmatcher
  libpointmatcher_ros
  roscpp
)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)
find_package(CUDA REQUIRED QUIET)

#set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -lineinfo --use_fast_math -rdc=true -lcudadevrt")
#add_definitions(-DUSE_CUDA)
#add_compile_options(target PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:
#                       --generate-line-info
#                       --use_fast_math
#                       --relocatable-device-code=true
#                       >)
set(CMAKE_CUDA_COMPILER "/usr/local/cuda-11.4/bin/nvcc")
CUDA_ADD_LIBRARY(CudaVoting src/CudaVoting.cu)

set(Eigen3_INCLUDE_DIR /usr/include/eigen3)
find_package(Eigen3)

set(yaml_cpp_INCLUDE_DIR /usr/include)
find_package(yaml-cpp)
#find_library(yaml_cpp_LIBRARIES /usr/local/lib)
#set(EXTRA_LIBS ${EXTRA_LIBS} ${yaml_cpp_LIBRARIES})

#message("\n\npointmatcher " ${POINT_MATCHER_LIBRARY})
#message("\n\npointmatcher_ros " ${POINT_MATCHER_ROS_LIBRARY})

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
# )

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES tensorvoting
  CATKIN_DEPENDS libnabo libpointmatcher libpointmatcher_ros roscpp
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${POINT_MATCHER_INCLUDE_DIR}
  ${POINT_MATCHER_ROS_INCLUDE_DIR}
  ${Eigen3_INCLUDE_DIR}
  ${yaml_cpp_INCLUDE_DIR}
  ${CUDA_INCLUDE_DIRS}
  /usr/local/cuda-11.4/samples/common/inc
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/tensorvoting.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/tensorvoting_node.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(${PROJECT_NAME}_node
#   ${catkin_LIBRARIES}
# )

add_library(tensor_voting src/tensor_voting.cpp)
target_link_libraries(tensor_voting
  ${catkin_LIBRARIES}
  CudaVoting
  ${POINT_MATCHER_LIBRARY}
  ${NABO_LIBRARY}
  ${Boost_LIBRARIES}
  ${EXTRA_LIBS}
  cuda
)

# Build the ROS node and the matrix-adding code that's CUDA-unaware
add_executable(fake_voting_gpu src/fake_voting_sparse_gpu.cpp) # src/tensor_voting.cpp)
target_link_libraries(fake_voting_gpu
  ${catkin_LIBRARIES}
  CudaVoting
  ${POINT_MATCHER_LIBRARY}
  ${NABO_LIBRARY}
  ${Boost_LIBRARIES}
  tensor_voting
)

# sparse voting demo
add_executable(demo_sparse_gpu src/demo_sparse_gpu.cpp) # src/tensor_voting.cpp)
target_link_libraries(demo_sparse_gpu
  ${catkin_LIBRARIES}
  CudaVoting
  ${POINT_MATCHER_LIBRARY}
  ${NABO_LIBRARY}
  ${Boost_LIBRARIES}
  tensor_voting
)

# sparse + dense stick voting demo (use unified GPU implementation)
add_executable(demo_dense_gpu src/demo_dense_gpu.cpp) # src/tensor_voting.cpp)
target_link_libraries(demo_dense_gpu
  ${catkin_LIBRARIES}
  CudaVoting
  ${POINT_MATCHER_LIBRARY}
  ${NABO_LIBRARY}
  ${Boost_LIBRARIES}
  tensor_voting
)
