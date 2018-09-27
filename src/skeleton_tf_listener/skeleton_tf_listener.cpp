#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/String.h>
#include <sstream>

#define ACTIVATE_MACROS 0
#if ACTIVATE_MACROS
    #define HEAD transform[0]
    #define NECK transform[1]
    #define RIGHT_SHOULDER transform[2]
    #define LEFT_SHOULDER transform[3]
    #define RIGHT_ELBOW transform[4]
    #define LEFT_ELBOW transform[5]
    #define RIGHT_HAND transform[6]
    #define LEFT_HAND  transform[7]
    #define TORSO transform[8]
    #define RIGHT_HIP transform[9]
    #define LEFT_HIP transform[10]
    #define RIGHT_KNEE transform[11]
    #define LEFT_KNEE transform[12]
    #define RIGHT_FOOT transform[13]
    #define LEFT_FOOT transform[14]
#endif
//Prototypes
void updateBodyJoints(geometry_msgs::Vector3 bodyJoints[15],tf::StampedTransform transform[15]);

//Global variables
std::stringstream buffer;
std_msgs::String bodyJointArr;;

int main(int argc, char** argv){
  ros::init(argc, argv, "skeleton_tf_listener");

  ros::NodeHandle node;

  ros::Publisher bodyJointAray_pub = node.advertise<std_msgs::String>("openni2_camera_node/bodyJointArr", 10);

  tf::TransformListener listener;
  geometry_msgs::Vector3 bodyJoints[15];
  tf::StampedTransform transform[15];
  ros::Rate rate(10.0);
  while (node.ok()){
    try{
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/head",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/head",ros::Time(0), transform[0]);
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/neck",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/neck",ros::Time(0), transform[1]);
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/right_shoulder",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/right_shoulder",ros::Time(0), transform[2]);
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/left_shoulder",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/left_shoulder",ros::Time(0), transform[3]);
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/right_elbow",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/right_elbow",ros::Time(0), transform[4]);
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/left_elbow",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/left_elbow",ros::Time(0), transform[5]);
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/right_hand",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/right_hand",ros::Time(0), transform[6]);
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/left_hand",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/left_hand",ros::Time(0), transform[7]);
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/torso",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/torso",ros::Time(0), transform[8]);
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/right_hip",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/right_hip",ros::Time(0), transform[9]);
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/left_hip",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/left_hip",ros::Time(0), transform[10]);
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/right_knee",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/right_knee",ros::Time(0), transform[11]);
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/left_knee",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/left_knee",ros::Time(0), transform[12]);
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/right_foot",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/right_foot",ros::Time(0), transform[13]);
      listener.waitForTransform("/tracker_depth_frame","/tracker/user_1/left_foot",ros::Time(0),ros::Duration(2.0));
      listener.lookupTransform("/tracker_depth_frame","/tracker/user_1/left_foot",ros::Time(0), transform[14]);
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }

    updateBodyJoints(bodyJoints,transform);
    bodyJointAray_pub.publish(bodyJointArr);

    rate.sleep();
  }
  return 0;
};
void updateBodyJoints(geometry_msgs::Vector3 bodyJoints[15],tf::StampedTransform transform[15]){
    buffer.str("");
    buffer<<"1";
    for(int i=0;i<15;i++){
        bodyJoints[i].x=int(1000*transform[i].getOrigin().x());
        bodyJoints[i].y=int(1000*transform[i].getOrigin().y());
        bodyJoints[i].z=int(1000*transform[i].getOrigin().z());
        buffer<<","<<bodyJoints[i].x<<","<<bodyJoints[i].y<<","<<bodyJoints[i].z;
    }
    bodyJointArr.data=buffer.str();
}
