#include "links_pose_publisher/links_pose_publisher.hpp"


LinksPosePublisher::LinksPosePublisher(ros::NodeHandle nh, std::string reference_frame, short frequency):
  nh(nh),
  reference_frame(reference_frame),
  loop_rate_(frequency)
{
  pub_poses = this->nh.advertise<seher_support::PoseStampedArray>("links_poses", 1000);
}

LinksPosePublisher::~LinksPosePublisher()
{

}

seher_support::PoseStampedArray LinksPosePublisher::getAllPoses()
{
  seher_support::PoseStampedArray msg;

  for(std::string link : links)
  {
    msg.stamped_poses.push_back(getPoseOfLink(link));
  }

  return msg;
}

void LinksPosePublisher::setReferencerame(std::string frame_name)
{
  reference_frame = frame_name;
}

void LinksPosePublisher::setLoop_rate(const short hz)
{
  loop_rate_ = ros::Rate(hz);
}

geometry_msgs::PoseStamped LinksPosePublisher::getPoseOfLink(std::string source_link)
{
  tf::StampedTransform transform;
  geometry_msgs::PoseStamped pose_link;

  try
  {
    listener.waitForTransform(reference_frame, source_link,ros::Time(0),ros::Duration(tf_lookup_timeout) );
    listener.lookupTransform(reference_frame, source_link, ros::Time(0),transform);
  }
  catch (tf::LookupException e)
  {
    ROS_ERROR_STREAM("Error looking up transform : " << e.what());
  }
  if(transform.child_frame_id_ == source_link)
  {
//    ROS_INFO_STREAM("Found tf. Trans : " << transform.getOrigin().getX() << " " << transform.getOrigin().getY() << " " << transform.getOrigin().getZ()
//                    << " Orient: "  << transform.getRotation().getX() << " " << transform.getRotation().getY()
//                    << " " << transform.getRotation().getZ() << " " << transform.getRotation().getW()
//                    << " stamp : " << transform.stamp_
//                    << " parent_frame_id: " << transform.frame_id_
//                    << " child_id: " << transform.child_frame_id_
//                    ) ;
    pose_link.header.seq = seq;
    pose_link.header.stamp = ros::Time::now();
    pose_link.header.frame_id = source_link;
    pose_link.pose.position.x = transform.getOrigin().getX();
    pose_link.pose.position.y = transform.getOrigin().getY();
    pose_link.pose.position.z = transform.getOrigin().getZ();
    pose_link.pose.orientation.x = transform.getRotation().getX();
    pose_link.pose.orientation.y = transform.getRotation().getY();
    pose_link.pose.orientation.z = transform.getRotation().getZ();
    pose_link.pose.orientation.w = transform.getRotation().getW();
  }
  else
  {
    ROS_ERROR_STREAM("Could not find transform for " << source_link << " within " << tf_lookup_timeout << "s! Returning empty pose.");
  }
//  ROS_INFO_STREAM("Returning pose :" << pose_link);
  return pose_link;

}

void LinksPosePublisher::publishAllPoses()
{
  while(ros::ok())
  {
    publishAllPosesOnce();
    loop_rate_.sleep();
  }
}

void LinksPosePublisher::publishAllPosesOnce()
{
  pub_poses.publish(getAllPoses());
  seq++;
}

