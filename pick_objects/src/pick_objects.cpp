#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  n.setParam("/object_picked", false);
  n.setParam("/object_delivered", false);

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal_pick;
  move_base_msgs::MoveBaseGoal goal_drop;

  // set up the frame parameters
  goal_pick.target_pose.header.frame_id = "map";
  goal_pick.target_pose.header.stamp = ros::Time::now();

  goal_drop.target_pose.header.frame_id = "map";
  goal_drop.target_pose.header.stamp = ros::Time::now();


  // Define a position and orientation for the robot to reach
  // pick up
  goal_pick.target_pose.pose.position.x = -3.5;
  goal_pick.target_pose.pose.position.y = 5.5;
  goal_pick.target_pose.pose.orientation.w = 1.57;

  // drop off
  goal_drop.target_pose.pose.position.x = 3.5;
  goal_drop.target_pose.pose.position.y = -3.5;
  goal_drop.target_pose.pose.orientation.w = 1.57;

   // Send the goal position and orientation for the robot to reach
  ros::Duration(5.0).sleep();  // Sleep for five seconds
  ROS_INFO("Sending goal");
  ac.sendGoal(goal_pick);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the base moved to pick up location");
    n.setParam("/object_picked", true);
  } else
    ROS_INFO("The base failed to move to pick up location for some reason");

  
  ros::Duration(5.0).sleep();  // Sleep for five seconds
  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal_drop);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the base moved to drop off location");
    n.setParam("/object_delivered", true);
  } else
    ROS_INFO("The base failed to move to drop off location for some reason");


  return 0;
}