#ifndef __IMAGE_CLASS_H_
#define __IMAGE_CLASS_H_

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
// #include "opencv2/core/mat.hpp"
// #include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

class D435_Image
{
    ros::NodeHandle n;
    ros::Publisher image_pub;
    ros::Subscriber first_image_sub;
    ros::Subscriber image_sub;
    int wait_esc_key;

public:
    D435_Image();
    void tempImageCallback(const sensor_msgs::Image::ConstPtr& sub_temp_image);
    void ImageCallback(const sensor_msgs::Image::ConstPtr& sub_image);
    ~D435_Image();
};

#endif