#include "ros/ros.h"
#include <gimbal_control/GimbalTargetInPixel.h>
#include <gimbal_control/EnemyPos.h>

void GimbalControlCallback (const gimbal_control::GimbalTargetInPixel::ConstPtr& msg)
{
	ROS_INFO("There is a topic message comes.\n");
}

int main ( int argc, char** argv)
{
	ros::init(argc, argv, "gimbal_controller_node");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<gimbal_control::EnemyPos>("enemy_pos", 1000);
	ros::Subscriber sub = n.subscribe("gimbal_target", 1, GimbalControlCallback);
	ros::Rate loop_rate(100);
	//ros::spin();

	int count = 0;
  	while (ros::ok())
  	{
    		/**
     		* This is a message object. You stuff it with data, and then publish it.
     		*/
    		gimbal_control::EnemyPos msg;

    		ROS_INFO("pitch = %f,  yaw = %f", msg.enemy_pitch, msg.enemy_yaw);

    		/**
     		* The publish() function is how you send messages. The parameter
     		* is the message object. The type of this object must agree with the type
     		* given as a template parameter to the advertise<>() call, as was done
     		* in the constructor above.
     		*/
    		pub.publish(msg);

    		ros::spinOnce();

    		loop_rate.sleep();
    		++count;
  	}

	return 0;
}
