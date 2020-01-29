#ifndef LINKS_POSE_PUBLISHER_HPP
#define LINKS_POSE_PUBLISHER_HPP

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <seher_support/PoseStampedArray.h>

class LinksPosePublisher
{
public:
  LinksPosePublisher(ros::NodeHandle nh, std::string reference_frame, short frequency);
  ~LinksPosePublisher();

  geometry_msgs::PoseStamped getPoseOfLink(std::string source_link);
  void publishAllPoses();
  void publishAllPosesOnce();
  void setReferencerame(std::string frame_name);

  void setLoop_rate(const short hz);

private:
  double tf_lookup_timeout = 2.0;
  ros::NodeHandle nh;
  ros::Publisher pub_poses;
  std::string reference_frame;
  ros::Rate loop_rate_;
  std::vector<std::string> links{"shoulder_link", "upper_arm_link",  "forearm_link",  "wrist_1_link",  "wrist_2_link",  "wrist_3_link",  "egp_50_tip"};
  tf::TransformListener listener;

  seher_support::PoseStampedArray getAllPoses();
  unsigned int seq = 0;
};

#endif // LINKS_POSE_PUBLISHER_HPP
