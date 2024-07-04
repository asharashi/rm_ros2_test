#include "sub_node.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto sub_node = std::make_shared<My_first_subnode>("sub01");
    
    rclcpp::spin(sub_node);

    rclcpp::shutdown();
    return 0;
}