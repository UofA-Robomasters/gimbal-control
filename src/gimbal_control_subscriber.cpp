#include "ros/ros.h"
#include <gimbal_control/GimbalTargetInPixel.h>

void GimbalControlCallback (const gimbal_control::GimbalTargetInPixel::ConstPtr& msg)
{
	ROS_INFO("There is a topic message comes.\n");
}

int main ( int argc, char** argv)
{
	ros::init(argc, argv, "gimbal_controller_node");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("gimbal_target", 1, GimbalControlCallback);
	ros::spin();

	return 0;
}
