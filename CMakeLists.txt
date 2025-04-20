cmake_minimum_required(VERSION 3.5)
project(json_parser_ros2)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

ament_auto_add_library(target_json_parser_ros2 SHARED
  DIRECTORY src
)

target_include_directories(target_json_parser_ros2
  SYSTEM PUBLIC
)

rclcpp_components_register_node(target_json_parser_ros2
  PLUGIN "json_parser_ros2::JsonParserROS2"
  EXECUTABLE json_parser_ros2_node
)

ament_auto_package(
  INSTALL_TO_SHARE
)