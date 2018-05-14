#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String
from gimbal_control.msg import GimbalTargetInPixel

AIM_X_IN_PIXEL = 320
AIM_Y_IN_PIXEL = 240

SPEED = 20

key_maps = { 
	'a': [-1, 0],
	'd': [1, 0],
	'w': [0, -1],
	's': [0, 1],
	'x': [0, 0]
	} 

def talker():
    rospy.init_node('mockup_gimbal_target_node', anonymous=True)
    pub = rospy.Publisher('gimbal_target', GimbalTargetInPixel, queue_size=10)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        key = raw_input()
	if key in key_maps.keys():
		gimbal_target = GimbalTargetInPixel()
		gimbal_target.x = key_maps[key][0] * SPEED + AIM_X_IN_PIXEL
		gimbal_target.y = key_maps[key][1] * SPEED + AIM_Y_IN_PIXEL
        	rospy.loginfo(gimbal_target)
        	pub.publish(gimbal_target)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
