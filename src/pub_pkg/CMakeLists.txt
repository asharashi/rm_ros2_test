cmake_minimum_required(VERSION 3.8)
project(pub_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED) 
find_package(sensor_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(rclcpp_components REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

aux_source_directory(./src ALL_CPP)

add_executable(PUB_NODE ${ALL_CPP})

target_include_directories(PUB_NODE 
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/pub_pkg>)

ament_target_dependencies(
  PUB_NODE
  "rclcpp"
  "rclcpp_components"
  "OpenCV"
  "sensor_msgs"
  "cv_bridge"
  "image_transport"
  "std_msgs"
  "ament_cmake"
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
PUB_NODE
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
