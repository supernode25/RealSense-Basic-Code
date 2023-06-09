#include "ros_opencv/image_class.h"

int main(int argc, char**argv)
{
    ros::init(argc, argv, "sub_pub_image");
    D435_Image d435_image;
    ros::spin();
}