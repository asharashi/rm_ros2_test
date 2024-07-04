#include "pub_node.hpp"
#include "toGetImage.hpp"

My_first_pubnode::~My_first_pubnode()
{
    RCLCPP_INFO(this->get_logger(), "node shut down.");
}

My_first_pubnode::My_first_pubnode(std::string name) : Node(name)
{
    RCLCPP_INFO(this->get_logger(), "%s publish node is on.", name.c_str());

    int queue_length = 1;
    img_pub_    = this->create_publisher<sensor_msgs::msg::Image>("my_image", queue_length);
    string_pub_ = this->create_publisher<std_msgs::msg::String>("my_string", queue_length);  
    para_sub_   = this->create_subscription<rcl_interfaces::msg::ParameterEvent>(
                  "/parameter_events", 
                  10, 
                  std::bind(&My_first_pubnode::para_callback, this, std::placeholders::_1));
    
    img_timer_     = this->create_wall_timer(std::chrono::milliseconds(1), std::bind(&My_first_pubnode::img_callback, this));
    string_timer_  = this->create_wall_timer(std::chrono::milliseconds(1), std::bind(&My_first_pubnode::string_callback, this));
}

void My_first_pubnode::para_callback(const rcl_interfaces::msg::ParameterEvent::SharedPtr event)
{
    for(auto &changed_para : event->changed_parameters)
    {
        RCLCPP_INFO(rclcpp::get_logger("paramter_listener"), "Parameter %s has been changed", changed_para.name.c_str());
    }
}

void My_first_pubnode::img_callback() 
{
    
    cv::Mat raw_img;
    cv::Mat* img_ptr = &raw_img;

    bool isGetImage = toGetImage(img_ptr);

    if(!isGetImage)
    {
        RCLCPP_INFO(this->get_logger(), "the image is empty");
    }
    else
    {
        RCLCPP_INFO(this->get_logger(), "image capture success");
    }

    //convert Opencv image to ROS image
    cv_bridge::CvImage img_bridge;
    sensor_msgs::msg::Image::SharedPtr raw_img_msg;
    raw_img_msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", raw_img).toImageMsg();

    //RCLCPP_INFO(this->get_logger(), "message publishing");
    //img_bridge = cv_bridge::CvImage

    img_pub_->publish(*raw_img_msg.get());
}

void My_first_pubnode::string_callback() 
{
    
    std::string raw_string = "im string ran";

    /*
        function to get string
    */

    if(raw_string.empty())
    {
        RCLCPP_INFO(this->get_logger(), "the string is empty");
    }
    else
    {
        RCLCPP_INFO(this->get_logger(), "string capture success");
    }

    //convert string to mag
    std_msgs::msg::String string_msg;
    string_msg.data = raw_string;

    string_pub_->publish(string_msg);
}