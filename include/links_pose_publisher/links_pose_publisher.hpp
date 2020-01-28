#ifndef LINKS_POSE_PUBLISHER_HPP
#define LINKS_POSE_PUBLISHER_HPP

#include <ros/ros.h>
#include <tf/transform_listener.h>

class LinksPosePublisher
{
public:
  LinksPosePublisher();
  ~LinksPosePublisher();
  void print_hello();
  void getAllTfs();

private:
  tf::TransformListener listener;
};

#endif // LINKS_POSE_PUBLISHER_HPP
