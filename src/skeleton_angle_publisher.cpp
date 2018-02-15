#include <ros/ros.h>
#include <std_msgs/String.h>
#include <math.h>
#include <sstream>
#include <string>
#include <iostream>
std::string bodyJointArr;
std::string test="hole,boole,hoh";
void cb(const std_msgs::String::ConstPtr& msg){
    istringstream iss(test);
    while (getline(iss,bodyJointArr,',')) {
        ROS_INFO("hi");
    }

}
int main(int argc, int**argv){
    ros::init(argc,argv,"skeleton_angle_publisher");
    ros::NodeHandle node;
    ros::Rate rate(10.0);
    ros::Publisher waist_angle_pub=node.advertise<std_msgs::String>("body_angle_publisher/waist",10);
    ros::Publisher rightshoulder_angle_pub=node.advertise<std_msgs::String>("body_angle_publisher/rightshoulder",10);
    ros::Publisher rightelbow_angle_pub=node.advertise<std_msgs::String>("body_angle_publisher/rightelbow",10);
    ros::Publisher rightpit_angle_pub=node.advertise<std_msgs::String>("body_angle_publisher/rightpit",10);
    ros::Subscriber sub=node.subscribe("openni2_camera_node/bodyJointArr",1000,cb);




    while(ros::ok()){



    }
}
