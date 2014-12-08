rc_car
======

1. install avahi-daemon 

	sudo apt-get install avahi-daemon
	sudo apt-get install libnss-mdns 
	
in /etc/avahi-daemon/*.conf 
pi|			host:rp1
server|		host:ros-linux

.bashrc master:
	export ROS_HOSTNAME=ros-linux.local
	export ROS_MASTER_URI=http://ros-linux.local:11311

.bashrc rpi:
	export ROS_HOSTNAME=raspberrypi.local
	export ROS_MASTER_URI=http://ros-linux.local:11311

============================

2.
follow: 
		http://wiki.ros.org/ROSberryPi/Installing%20ROS%20Indigo%20on%20Raspberry%20Pi 
		https://github.com/fpasteau/raspicam_node/blob/master/README.md

		skip the groovy install 
		add image_common  
		rebuild (3.2 of ROSberryPi guide)
		
in ros_catkin_ws:
	
rosinstall_generator ros_comm image_common --rosdistro indigo --deps --wet-only --exclude roslisp --tar > indigo-custom_ros.rosinstall

wstool merge -t src indigo-custom_ros.rosinstall

wstool update -t src



rosdep install --from-paths src --ignore-src --rosdistro indigo -y -r --os=debian:wheezy

sudo ./src/catkin/bin/catkin_make_isolated --install -DCMAKE_BUILD_TYPE=Release --install-space /opt/ros/indigo

