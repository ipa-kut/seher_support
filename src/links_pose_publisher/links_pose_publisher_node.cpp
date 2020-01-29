#include "ros/ros.h"
#include "std_msgs/String.h"
#include "links_pose_publisher/links_pose_publisher.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "link_pose_publisher_node");
  ros::NodeHandle nh;

  LinksPosePublisher lpp;

  ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);

  ros::Rate loop_rate(10);

  lpp.setReferencerame("world");
  lpp.getAllTfs();


  return 0;
}
