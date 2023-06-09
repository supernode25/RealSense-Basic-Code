#include "ros_opencv/image_class.h"

D435_Image::D435_Image()
{
    //realsense2_camera package에서 생성된 토픽 sub
    first_image_sub = n.subscribe("/jeonggi/camera/color/image_raw", 1000, &D435_Image::tempImageCallback, this);
    //camera/color/image_raw 토픽과 동일한 타입으로 jeonggi_image 토픽 pub
    image_pub = n.advertise<sensor_msgs::Image>("/jeonggi_image", 1000);
    //외부 pc에서 넘어온 /byoungjin_image를 받는 subscriber
    image_sub = n.subscribe("/ByoungJin_image", 1000, &D435_Image::ImageCallback, this);
    // image_sub = n.subscribe("/jeonggi_image", 1000, &D435_Image::ImageCallback, this);
};

void D435_Image::tempImageCallback(const sensor_msgs::Image::ConstPtr& sub_temp_image)
{
    //sensor_msgs::Image temp_image = *sub_temp_image;
    image_pub.publish(sub_temp_image);
};

void D435_Image::ImageCallback(const sensor_msgs::Image::ConstPtr& sub_image)
{
    //core/mat.hpp
    //original, blur image를 담을 Mat 자료형 생성
    cv::Mat img, img_blur;

    //sensor_msgs/Image->CvImage
    //cvImage(header, encoding, iamge=mat)
    //rgb8->bgr8 인코딩 변경
    //cvcopy나 cvshare는 데이터의 유효성을 확인하지 않으므로 try, catch문을 써야한다.
    try{img = cv_bridge::toCvShare(sub_image, "bgr8")->image;}
    catch(cv_bridge::Exception& e){ROS_ERROR("cv_bridge exception: %s", e.what()); return;}

    //imgproc.hpp
    //GaussianBlur(src,dst,ksize,sigmaX,sigmaY=0,borderType=BORDER_DEFAULT)
    //노이즈를 제거하기 위해 가장 일반적으로 사용되는 스무딩 기술, 가중치들의 합 1
    //Size(0, 0)-> kernel size가 sigma에 의해 결정된다.
    //원래는 양수이고 홀수여야 한다.
    //sigmaX는 x방향 가우시안 커널 표준 편차
    //sigmaY가 0이면 sigmaX와 같은 값이 설정
    //borderType은 패딩방식, default는 거울에 비친것같이 패딩
    cv::GaussianBlur(img, img_blur, cv::Size(0, 0), 5);

    //highgui.gpp
    //imshow(window name, mat)
    cv::imshow("blur", img_blur);
    cv::imshow("original", img);

    //waitkey(time(ms)), 반환값 int 아스키 값
    //waitKey가 있어야 imshow가 된다.
    //GUI 정리 작업을 수행하고, image 실제 표시, 창이 마우스 및 키보드 이벤트에 응답하도록 함
    wait_esc_key = cv::waitKey(1);

    //esc키의 아스키코드가 27, esc키가 눌리면 모든 window를 끄고 ros 종료
    if(wait_esc_key == 27){
        cv::destroyAllWindows();
        ros::shutdown();
    }
};

D435_Image::~D435_Image() {}