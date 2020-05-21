#!/bin/sh
sleep 5
xterm  -e  " source /opt/ros/kinetic/setup.bash ; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find pick_objects)/../worlds/building5.world" & 
sleep 5
xterm  -e  " source /opt/ros/kinetic/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find pick_objects)/../map/map.yaml initial_pose_a:=4.71" &
sleep 5
xterm  -e  " source /opt/ros/kinetic/setup.bash; rviz rviz -d $(rospack find pick_objects)/../rvizConfig/home_service.rviz" &
sleep 5 
xterm  -e  " source /opt/ros/kinetic/setup.bash; cd catkin_ws; source devel/setup.bash ; rosrun pick_objects pick_objects" &
sleep 5 
xterm  -e  " source /opt/ros/kinetic/setup.bash; cd catkin_ws; source devel/setup.bash ; rosrun add_markers add_markers" &
