#ifndef VIDALG_HPP
#define VIDALG_HPP

#include <vector>
#include <string>
#include <cassert>
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
     int sizePerValue_;
     void openOutput();
     void setArray();
     void shuffle();  
     void closeOutput();
     void paintAndClose(int comp,int swaps);
     int partition(int primero, int ultimo,int &comp,int &swap);
     void quick(int primero, int ultimo,int &comp,int &swaps);
     cv::Mat paintArray(int comp,int desp);
   public:

     VidAlg(int size,int sizePerValue=1,int fps=30,std::string vid="VidAlg.avi"){
       assert(size>0);
        size_=size;
        setArray();
        videoName_=vid;
        fps_=fps;
        sizePerValue_=sizePerValue;
     }
     inline int getFps(){return fps_;}
     inline int getSize(){return size_;}
     inline std::string getVideoName(){return videoName_;}
     inline void setFps(int fps){fps_=fps;}
     inline void setVideoName(std::string name){videoName_=name;}
     inline void setSize(int size){size_=size; setArray();}
     void selectionSort();
     void bubble();
     void shakerSort();
     void oddEvenSort();
     void combSort();
     void bogoSort();
     void quicksort();
     void insertionSort();
};
#endif
