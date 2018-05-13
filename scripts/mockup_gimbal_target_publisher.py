#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String
from gimbal_control.msg import GimbalTargetInPixel

key_maps = {
	'a': [1, 0],
	'd': [-1, 0],
	'w': [0, -1],
	's': [0, 1]
	} 

def talker():
    pub = rospy.Publisher('gimbal_target', GimbalTargetInPixel, queue_size=10)
    rospy.init_node('mockup_gimbal_target_node', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        key = raw_input()
	if key in key_maps.keys():
		gimbal_target = GimbalTargetInPixel()
		gimbal_target.x = key_maps[key][0]
		gimbal_target.y = key_maps[key][1]
        	rospy.loginfo(gimbal_target)
        	pub.publish(gimbal_target)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
