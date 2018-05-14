#include "ros/ros.h"
#include <gimbal_control/GimbalTargetInPixel.h>
#include <gimbal_control/EnemyPos.h>

#define MAX_YAW_RADIAN 0.8727
#define MIN_YAW_RADIAN -0.8727
#define MAX_PIT_RADIAN 0.2618
#define MIN_PIT_RADIAN -0.3491

#define AIM_X_IN_PIXEL 320.0
#define AIM_Y_IN_PIXEL 240.0

class GimbalController
{
	float pitch_speed;
	float yaw_speed;
private:
	ros::NodeHandle n;
	ros::Publisher pub;
	ros::Subscriber sub;
	ros::Rate loop_rate;
	gimbal_control::EnemyPos enemy_pos_msg;

public:
	GimbalController ( int argc, char** argv) : 
		loop_rate (100)
	{
		pub = n.advertise <gimbal_control::EnemyPos> ("enemy_pos", 1000);
		sub = n.subscribe("gimbal_target", 1, &GimbalController::GimbalControlCallback, this);
	}

	void GimbalControlCallback (const gimbal_control::GimbalTargetInPixel::ConstPtr& msg)
	{
		yaw_speed = (AIM_X_IN_PIXEL - (float) msg->x) / 10000.0f;
		pitch_speed = (AIM_Y_IN_PIXEL - (float) msg->y) / -10000.0f;
		ROS_INFO("msg->x = %d, msg->y = %d", msg->x, msg->y);
    		ROS_INFO("pitch_speed = %f,  yaw_speed = %f", pitch_speed, yaw_speed);
	}

	void run ()
	{
		while (ros::ok())
		{
			if (enemy_pos_msg.enemy_pitch + pitch_speed < MAX_PIT_RADIAN && enemy_pos_msg.enemy_pitch + pitch_speed > MIN_PIT_RADIAN)
			{
				enemy_pos_msg.enemy_pitch = enemy_pos_msg.enemy_pitch + pitch_speed;
				//pitch_speed = -pitch_speed;
			}
			
			if (enemy_pos_msg.enemy_yaw + yaw_speed < MAX_YAW_RADIAN && enemy_pos_msg.enemy_yaw + yaw_speed > MIN_YAW_RADIAN)
			{
				enemy_pos_msg.enemy_yaw = enemy_pos_msg.enemy_yaw + yaw_speed;
			}

			pub.publish(enemy_pos_msg);
    			//ROS_INFO("pitch = %f,  yaw = %f", enemy_pos_msg.enemy_pitch, enemy_pos_msg.enemy_yaw);
			
			ros::spinOnce();
    			loop_rate.sleep();
		}
	}
};


int main ( int argc, char** argv)
{
	ros::init(argc, argv, "gimbal_controller_node");
	GimbalController controller (argc, argv);
	controller.run();
	return 0;
}
