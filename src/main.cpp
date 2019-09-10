
#include <iostream>
#include <string>
#include <sstream>

// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

namespace cv_global{
    int blur_amount=15;
}

namespace cv_constants{
    
    constexpr char LENA_PATH[] = "../img/lena.jpg";
    constexpr char LENA_WINDOW_NAME[] = "Lena";
    constexpr char PHOTO_PATH[] = "../img/profile.jpg";
    constexpr char PHOTO_WINDOW_NAME[] = "Photo";
}
//Trackbar callback function
static void onChange(int pos, void* userInput){
    if(pos<=0) return;
    cv::Mat imgBlur;
    cv::Mat* img= static_cast<cv::Mat*>(userInput);
    //Apply a blur filter
    cv::blur(*img,imgBlur,cv::Size(pos,pos));
    // show result
    cv::imshow(cv_constants::LENA_WINDOW_NAME,imgBlur);

}

//Mouse callback event type , mouse pos x, mouse pos y, wheel movement, input data
static void onMouse(int event,int x, int y, int ,void* userInput){
    if(event != cv::EVENT_LBUTTONDOWN) 
        return; 

    cv::Mat* img= static_cast<cv::Mat*>(userInput); 
    
   // Draw circle inputimg , center , radius , color , thickness    
    cv::circle(*img, cv::Point(x, y), 10, cv::Scalar(0,255,0), 3); 
   // Call on change to get blurred image 
    onChange(cv_global::blur_amount, img); 

}

void addControls(){
    cv::Mat lena= cv::imread(cv_constants::LENA_PATH);
    cv::namedWindow(cv_constants::LENA_WINDOW_NAME,cv::WINDOW_GUI_EXPANDED);

    //create trackbar,trackbar name, window name, blur ,max pos, callbakc func , data to callback
    cv::createTrackbar("Lena",cv_constants::LENA_WINDOW_NAME,&cv_global::blur_amount,30,onChange,&lena);

    cv::setMouseCallback(cv_constants::LENA_WINDOW_NAME,onMouse,&lena);

    // call onChange function to init
    onChange(cv_global::blur_amount,&lena);

    // wait for key 5s
    cv::waitKey(0);

    cv::destroyWindow(cv_constants::LENA_WINDOW_NAME);
}

void createMultipleWindows(const cv::Mat& photo){
    for(unsigned int i=0;i<10;i++){
        std::ostringstream ss;
        ss << "Photo " << i;
        cv::namedWindow(ss.str());
        cv::moveWindow(ss.str(),20*i,20*i);
        cv::imshow(ss.str(),photo);
    }
    cv::waitKey(5000);
    //Destroy all windows
    cv::destroyAllWindows();
}

bool loadWindows(){
    //Read Images
    cv::Mat lena= cv::imread(cv_constants::LENA_PATH);
    // check if the image was load
    if(!lena.data){
        std::cout << "Lena img is missing! \n";
        return false;
    }

    cv::Mat photo= cv::imread(cv_constants::PHOTO_PATH);
    if(!photo.data){
        std::cout << "Photo is missing !\n";
        return false;
    }

    // create Windows
    //WINDOW_NORMAL: This flag allows the user to resize the window
    //WINDOW_AUTOSIZE: If this flag is set, the window size is automatically adjusted to fit the display image and it is not possible to resize the window
    //WINDOW_OPENGL: This flag enables the OpenGL support
    cv::namedWindow(cv_constants::LENA_WINDOW_NAME,cv::WINDOW_NORMAL);
    cv::namedWindow(cv_constants::PHOTO_WINDOW_NAME,cv::WINDOW_GUI_EXPANDED);

    // Move windows
    cv::moveWindow(cv_constants::LENA_WINDOW_NAME,10,10);
    cv::moveWindow(cv_constants::PHOTO_WINDOW_NAME,520,10);

    //show images
    cv::imshow(cv_constants::LENA_WINDOW_NAME,lena);
    cv::imshow(cv_constants::PHOTO_WINDOW_NAME,photo);

    // Resize window
    // Only windows without the WINDOW_AUTOSIZE flag enabled can be resized.
    cv::resizeWindow(cv_constants::LENA_WINDOW_NAME,512,512);

    // wait 5s for any key press
    cv::waitKey(5000);
    
    // destroy the windows

    cv::destroyWindow(cv_constants::LENA_WINDOW_NAME);
    cv::destroyWindow(cv_constants::PHOTO_WINDOW_NAME);
    createMultipleWindows(photo);
    return true;

}

int main(){

    std::cout << "Type 1 to run Windows Test\r\n "<< "Type 2 to run Controls Test\n";
    int testNum;
    std::cin>> testNum;

    switch (testNum)
    {
    case 1:
        if(!loadWindows()){
            return -1;
        }    
    break;
    case 2:
        addControls();
    break;
    default:
        break;
    }    
    return 0;
}