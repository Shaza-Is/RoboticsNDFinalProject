#!/bin/sh
sleep 5
xterm  -e  " source /opt/ros/kinetic/setup.bash ; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find pick_objects)/../worlds/building5.world" & 
sleep 5
xterm  -e  " source /opt/ros/kinetic/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find pick_objects)/../map/map.yaml initial_pose_a:=4.71" &
sleep 5
xterm  -e  " source /opt/ros/kinetic/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5 
xterm  -e  " source /opt/ros/kinetic/setup.bash; cd catkin_ws; source devel/setup.bash ; rosrun pick_objects pick_objects" &
