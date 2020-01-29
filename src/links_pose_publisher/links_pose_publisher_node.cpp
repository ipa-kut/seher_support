#include "ros/ros.h"
#include "std_msgs/String.h"
#include "links_pose_publisher/links_pose_publisher.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "link_pose_publisher_node");
  ros::NodeHandle nh;

  LinksPosePublisher lpp(nh, "world", 100);
  lpp.publishAllPoses();

  return 0;
}
