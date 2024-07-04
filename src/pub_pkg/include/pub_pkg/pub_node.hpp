#ifndef PUB_NODE
#define PUB_NODE

#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/header.hpp"
#include "cv_bridge/cv_bridge.h"
#include "rclcpp_components/register_node_macro.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>

class My_first_pubnode : public rclcpp::Node
{
private:

    //publisher's timer
    rclcpp::TimerBase::SharedPtr img_timer_;    
    rclcpp::TimerBase::SharedPtr string_timer_; 
    
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr img_pub_;  
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr string_pub_; 
    rclcpp::Subscription<rcl_interfaces::msg::ParameterEvent>::SharedPtr para_sub_;

    void img_callback();    
    void string_callback(); 
    void para_callback(const rcl_interfaces::msg::ParameterEvent::SharedPtr event);   //节点参数回调函数

public:
    My_first_pubnode();
    ~My_first_pubnode();
    My_first_pubnode(std::string name);

};


#endif