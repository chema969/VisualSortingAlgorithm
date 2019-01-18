#ifndef VIDALG_HPP
#define VIDALG_HPP

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

class VidAlg{
   private:
     std::vector<int> arr_;
     cv::VideoWriter output_;  
     int size_;
     std::string videoName_;
     int fps_;
     void openOutput();
     void setArray();
     void shuffle();  
     void closeRecords();
   public:

     VidAlg(int size,std::string vid="VidArg.avi",int fps=30){
       cv::assert(size>0);
        size=size_;
        setArray();
        videoName_=vid;
        fps_=fps;
     }



};
#endif
