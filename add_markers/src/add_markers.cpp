#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  bool marker_on = true;
  bool object_picked = false;
  bool object_delivered = false;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;

    //
    
    n.getParam("/object_picked", object_picked);
    
    n.getParam("/object_delivered", object_delivered);
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header [PICK UP]
    if((!object_picked)){
      marker.pose.position.x = -3.5;
      marker.pose.position.y = 5.5;
      marker.pose.position.z = 0;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = 0.0;
      marker.pose.orientation.w = 1.0;
    }

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    if((!object_picked)){
      ROS_INFO("Marker at pick up");
      marker_pub.publish(marker);
      ros::Duration(5.0).sleep();  // Sleep for five seconds
    }

    if((object_picked) && (!object_delivered) && marker_on ){
      marker.pose.position.x = -3.5;
      marker.pose.position.y = 5.5;
      marker.pose.position.z = 0;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = 0.0;
      marker.pose.orientation.w = 1.0;
      marker.action = visualization_msgs::Marker::DELETE;
      ROS_INFO("Marker picked up");
      marker_pub.publish(marker);
      ros::Duration(5.0).sleep();  // Sleep for five seconds
      marker_on = false;
    }
    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header [DROP OFF]
    if(object_delivered){
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = 3.5;
      marker.pose.position.y = -3.5;

      marker.pose.orientation.w = 1.0;
      ROS_INFO("Marker delivered");
      marker_pub.publish(marker);
      ros::Duration(5.0).sleep();  // Sleep for five seconds
    }
   
  }


  // Handle ROS communication events
  ros::spin();
  return 0;
}