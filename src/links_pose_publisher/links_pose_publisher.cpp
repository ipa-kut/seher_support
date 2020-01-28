#include "links_pose_publisher/links_pose_publisher.hpp"

LinksPosePublisher::LinksPosePublisher()
{
}

LinksPosePublisher::~LinksPosePublisher()
{

}

void LinksPosePublisher::print_hello()
{
  ROS_INFO("Hello");
}

void LinksPosePublisher::getAllTfs()
{
  tf::StampedTransform tf_link1;
  while(ros::ok())
  {
    try
    {
      listener.lookupTransform("shoulder_link","world",ros::Time(0), tf_link1);
    }
    catch (tf::TransformException e)
    {
      //ROS_ERROR_STREAM("Error looking up transform : " << e.what());
    }
    if(tf_link1.frame_id_ == "shoulder_link")
    {
      ROS_INFO_STREAM("Found tf. Trans : " << tf_link1.getOrigin().getX() << " " << tf_link1.getOrigin().getY() << " " << tf_link1.getOrigin().getZ()
                      << " Orient: "  << tf_link1.getRotation().getX() << " " << tf_link1.getRotation().getY()
                      << " " << tf_link1.getRotation().getZ() << " " << tf_link1.getRotation().getW()) ;
      return;
    }
  }
}

