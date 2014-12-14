rc_car
======

1. install avahi-daemon 

	sudo apt-get install avahi-daemon
	sudo apt-get install libnss-mdns 
	
set the avahi hostnames /etc/avahi-daemon/*.conf 
on the pi
	host:rp1
on the server
	host:ros-linux

Add host/master exports to ~/.bashrc
.bashrc master:
	export ROS_HOSTNAME=ros-linux.local
	export ROS_MASTER_URI=http://ros-linux.local:11311

.bashrc rpi:
	export ROS_HOSTNAME=raspberrypi.local
	export ROS_MASTER_URI=http://ros-linux.local:11311

============================

2.
follow until step 3: 
		http://wiki.ros.org/ROSberryPi/Installing%20ROS%20Indigo%20on%20Raspberry%20Pi 
		
We need to add image_common, and do so in a custom_ros.install.
If you don't want to compile ros twice, add image_common during step two.
		
 	cd ~/ros_catkin_ws
	
	rosinstall_generator ros_comm image_common --rosdistro indigo --deps --wet-only --exclude roslisp --tar > indigo-custom_ros.rosinstall

	wstool merge -t src indigo-custom_ros.rosinstall

	wstool update -t src


	rosdep install --from-paths src --ignore-src --rosdistro indigo -y -r --os=debian:wheezy

	sudo ./src/catkin/bin/catkin_make_isolated --install -DCMAKE_BUILD_TYPE=Release --install-space /opt/ros/indigo

============================

3. Get raspicam by fpastbeau

	https://github.com/fpasteau/raspicam_node/blob/master/README.md


ON rpi, ignore master, bcs we don't install qt on it:
catkin_make -DCATKIN_BLACKLIST_PACKAGES="master"

###### USAGE ######
To use pwm in wiringPi, the service must be run as root.
The rc.launch file creates the service node with the launch-prefix "sudo -E".
Given a passwordless sudoer, the environtment is kept and the node can be run as root.
Without the pwm wiringPiSys() can be used as non-root, but all pins use the 
broadcom numbers and must be exported by a shell script before rosrun.

ON the rpi:
start the camera node:
	rosrun raspicam raspicam_node
	
start the car service node:	
	rosrun ros_pi car_service
	
	
	
ON the master:
	rosrun image_view image_view image:=/camera/image _image_transport:=compressed
