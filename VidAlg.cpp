#include "VidAlg.hpp"

cv::Mat VidAlg::paintArray(){
  cv::Mat ojala(size_,size_,CV_8UC3);
  cv::cvtColor(ojala, ojala,CV_BGR2HSV);
  for(int i=0;i<arr_.size();i++){
    for(int j=ojala.rows;j>=0;j--){
      if(arr_[i]+j>size_){
       ojala.at<cv::Vec3b>(j,i)[0]=((arr_[i]*255)/500);
       ojala.at<cv::Vec3b>(j,i)[1]=200;
       ojala.at<cv::Vec3b>(j,i)[2]=200;
      }
      else{    
       ojala.at<cv::Vec3b>(j,i)[0]=0;
       ojala.at<cv::Vec3b>(j,i)[1]=0;
       ojala.at<cv::Vec3b>(j,i)[2]=0;
      }
    } 
  }
 cv::cvtColor(ojala, ojala,CV_HSV2RGB);
 return ojala;
}

void VidAlg::setArray()
{
  for(int i=1;i<=500;i++)
       array.push_back(i);
}

void VidAlg::shuffle()
{
  std::random_shuffle(array.begin(), array.end());
}

void VidAlg::openOutput(){
   output_.open(videoName_,CV_FOURCC('M','J','P','G'),fps_,cv::Size(size_,size_),true);
}
