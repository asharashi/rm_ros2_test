#include "sub_node.hpp"

My_first_subnode::My_first_subnode(std::string name) : Node(name)
{
    RCLCPP_INFO(this->get_logger(), "%s subscribe node on.", name.c_str());

    para_declare();
    para_get();

    img_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
               "my_image",
               1,
               std::bind(&My_first_subnode::img_callback, this, std::placeholders::_1));
    
    string_sub_  = this->create_subscription<std_msgs::msg::String>(
                   "my_string",
                   1,
                   std::bind(&My_first_subnode::string_callback, this, std::placeholders::_1));
}

My_first_subnode::~My_first_subnode()
{
    RCLCPP_INFO(this->get_logger(), "node shut down.");
}

void My_first_subnode::para_callback(const rcl_interfaces::msg::ParameterEvent::SharedPtr event)
{
    for(auto &changed_para : event->changed_parameters)
    {
        RCLCPP_INFO(rclcpp::get_logger("paramter_listener"), "Parameter %s has been changed", changed_para.name.c_str());
        this->para_get();
    }
}

void My_first_subnode::img_callback(const sensor_msgs::msg::Image::SharedPtr img_msg)
{
    RCLCPP_INFO(this->get_logger(), "I heard img topic");
    cv_bridge::CvImage img_bridge;
    img_bridge = *cv_bridge::toCvCopy(img_msg, sensor_msgs::image_encodings::BGR8);

    cv::Mat img_need_process;
    img_need_process = img_bridge.image.clone();

    if(img_need_process.empty())
    {
        RCLCPP_INFO(this->get_logger(), "fail to get image message");
    }
    else
    {

    }
}

void My_first_subnode::string_callback(const std_msgs::msg::String::SharedPtr string_msg)
{
    RCLCPP_INFO(this->get_logger(), "I heard string topic");
    std::string sub_string;
    std::string template_s = "the string is:";
    sub_string = string_msg->data;
    sub_string = template_s + sub_string;
    RCLCPP_INFO(this->get_logger(), sub_string.c_str());
    /*
    function you write
    */
}

void My_first_subnode::para_declare()
{
    this->declare_parameter<int>("sub_para1", 150);
}

void My_first_subnode::para_get()
{
    this->just_a_para = this->get_parameter("sub_para1").as_int();
}
