#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicReader : public rclcpp::Node
{
public:
    TopicReader() : Node("topic_reader")
    {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "/robot_status",
            10,
            [this](const std_msgs::msg::String::SharedPtr msg)
            {
                RCLCPP_INFO(this->get_logger(),
                            "Received: %s", msg->data.c_str());
            }
        );
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<TopicReader>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
