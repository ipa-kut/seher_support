#ifndef LINKS_POSE_PUBLISHER_HPP
#define LINKS_POSE_PUBLISHER_HPP

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>

class LinksPosePublisher
{
public:
  LinksPosePublisher();
  ~LinksPosePublisher();
  void print_hello();
  void getAllTfs();
  void setReferencerame(std::string frame_name);
  geometry_msgs::PoseStamped getPoseOfLink(std::string source_link);

private:
  tf::TransformListener listener;
  std::string reference_frame;
  double tf_lookup_timeout = 2.0;

  std::vector<std::string> links{"shoulder_link", "upper_arm_link",  "forearm_link",  "wrist_1_link",  "wrist_2_link",  "wrist_3_link",  "egp_50_tip"};
};

#endif // LINKS_POSE_PUBLISHER_HPP
