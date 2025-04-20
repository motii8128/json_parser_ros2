#include "json_parser_ros2/json_parser_ros2.hpp"

namespace json_parser_ros2
{
    JsonParserROS2::JsonParserROS2(const rclcpp::NodeOptions& options) : Node("json_parser_ros2", options)
    {
        pub_m_ = this->create_publisher<std_msgs::msg::Int64MultiArray>("/machine", rclcpp::SystemDefaultsQoS());
        pub_w_ = this->create_publisher<std_msgs::msg::Int64MultiArray>("/wheel", rclcpp::SystemDefaultsQoS());

        sub_ = this->create_subscription<std_msgs::msg::String>(
            "/data",
            rclcpp::SystemDefaultsQoS(),
            std::bind(&JsonParserROS2::topic_callback, this, _1)
        );

        RCLCPP_INFO(this->get_logger(), "Start %s", this->get_name());
    }

    void JsonParserROS2::topic_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        try
        {
            json j = json::parse(msg->data.c_str());

            auto msg_w = std_msgs::msg::Int64MultiArray();
            msg_w.data.push_back(j.at("wheel1").get<int>());
            msg_w.data.push_back(j.at("wheel2").get<int>());
            msg_w.data.push_back(j.at("wheel3").get<int>());

            auto msg_m = std_msgs::msg::Int64MultiArray();
            msg_m.data.push_back(j.at("frontback").get<int>());
            msg_m.data.push_back(j.at("updown").get<int>());
            msg_m.data.push_back(j.at("hand").get<int>());
            
            pub_m_->publish(msg_m);
            pub_w_->publish(msg_w);
        }
        catch(const std::exception& e)
        {
            RCLCPP_WARN(this->get_logger(), "JSON parse error: %s", e.what());
        }
        
    }
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(json_parser_ros2::JsonParserROS2)