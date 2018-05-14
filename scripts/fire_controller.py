#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String
from gimbal_control.msg import EnemyPos 
from gimbal_control.msg import ShootCmd 

key_maps = {
	'f': [1, 0],
	'r': [-1, 0],
	'e': [0, -1],
	'c': []
	} 

def talker():
    rospy.init_node('mockup_shoot_control_node', anonymous=True)
    pub = rospy.Publisher('cmd_sht', ShootCmd, queue_size=10)
    rate = rospy.Rate(10) # 10hz
    
    shoot_msg = ShootCmd()
    shoot_msg.fric_wheel_spd = 1800
    
    while not rospy.is_shutdown():

	#pub.publish(shoot_msg)
	#rate.sleep()
	
        key = raw_input("r: firc_wheel, f: continue_shoot, e: shoot, c: change_fric_wheel_spd")
	if key in key_maps.keys():
		if key == 'r':
			shoot_msg.fric_wheel_run = 1 - shoot_msg.fric_wheel_run
		elif key == 'f':
			shoot_msg.c_shoot_cmd = 1 - shoot_msg.c_shoot_cmd
		elif key == 'e':
			shoot_msg.shoot_cmd = 1 - shoot_msg.shoot_cmd
		elif key == 'c':
			new_spd = raw_input("Type in speed: ")
			try:
				shoot_msg.fric_wheel_spd = int(new_spd)
			except:
				pass
		
        	rospy.loginfo(shoot_msg)
        	pub.publish(shoot_msg)
        rate.sleep()
	

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
