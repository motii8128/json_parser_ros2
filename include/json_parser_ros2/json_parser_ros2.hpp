#ifndef JSON_PARSER_ROS2_HPP_
#define JSON_PARSER_ROS2_HPP_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int64_multi_array.hpp>
#include <std_msgs/msg/string.hpp>

#include <nlohmann/json.hpp>

using json = nlohmann::json;
using std::placeholders::_1;

namespace json_parser_ros2
{
    class JsonParserROS2 : public rclcpp::Node
    {
        public:
        explicit JsonParserROS2(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());

        void topic_callback(const std_msgs::msg::String::SharedPtr msg);

        private:
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
        rclcpp::Publisher<std_msgs::msg::Int64MultiArray>::SharedPtr pub_m_;
        rclcpp::Publisher<std_msgs::msg::Int64MultiArray>::SharedPtr pub_w_;
    };
}

#endif