#include "pub_node.hpp"

int main(int argc, char **argv)
{

    rclcpp::init(argc, argv);   //initiate
    auto my_node = std::make_shared<My_first_pubnode>("pub01");

    rclcpp::spin(my_node);
    
    rclcpp::shutdown;
    return 0;

}