#!/bin/sh
sleep 5
xterm  -e  " source /opt/ros/kinetic/setup.bash ; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/shaza/catkin_ws/src/RoboticsNDFinalProject/worlds/building5.world" & 
sleep 5
xterm  -e  " source /opt/ros/kinetic/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/shaza/catkin_ws/src/RoboticsNDFinalProject/map/map.yaml initial_pose_a:=4.71" &
sleep 5
xterm  -e  " source /opt/ros/kinetic/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &


