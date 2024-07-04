#ifndef SUB_NODE
#define SUB_NODE

#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/header.hpp"
#include "cv_bridge/cv_bridge.h"
#include "rclcpp_components/register_node_macro.hpp"

#include <memory>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>

class My_first_subnode : public rclcpp::Node
{

private:

    //create a subscrition
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr img_sub_;  
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr   string_sub_;  
    rclcpp::Subscription<rcl_interfaces::msg::ParameterEvent>::SharedPtr para_sub_;

    void para_declare();
    void para_get();

    void img_callback(const sensor_msgs::msg::Image::SharedPtr img_msg);    
    void string_callback(const std_msgs::msg::String::SharedPtr string_msg);    
    void para_callback(const rcl_interfaces::msg::ParameterEvent::SharedPtr event);

    int just_a_para;

public:
    
    My_first_subnode();
    My_first_subnode(std::string name);
    ~My_first_subnode();

};


#endif