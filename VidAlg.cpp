#include "VidAlg.hpp"

cv::Mat VidAlg::paintArray(int comp,int desp){
   cv::namedWindow("myimage");
  cv::Mat ojala(size_+50,size_*sizePerValue_+50,CV_8UC3);
  ojala=cv::Mat::zeros(size_+50,size_*sizePerValue_+50,CV_8UC3);
  cv::cvtColor(ojala, ojala,cv::COLOR_BGR2HSV);
  int k=0;
  for(int i=0;i<arr_.size();i++){
   while(k<((i+1)*sizePerValue_)){
    for(int j=ojala.rows-1;j>=0;j--){
      if(arr_[i]+j>size_){
       ojala.at<cv::Vec3b>(j,k+50)[0]=((arr_[i]*255)/size_);
       ojala.at<cv::Vec3b>(j,k+50)[1]=200;
       ojala.at<cv::Vec3b>(j,k+50)[2]=200;
      }
    } 
   k++;
   }
  }
 cv::cvtColor(ojala, ojala, cv::COLOR_HSV2BGR);
 std::string i="Comp: "+std::to_string(comp);std::string j="Desp: "+std::to_string(desp);
 cv::Scalar color(255,255,255);
 cv::putText(ojala,i.c_str(),cv::Point(0,size_/8), cv::FONT_HERSHEY_SIMPLEX, 0.7,color,1,cv::LINE_4);
 cv::putText(ojala,j.c_str(),cv::Point(0,(size_/8)*2), cv::FONT_HERSHEY_SIMPLEX, 0.7 ,color,1,cv::LINE_4);
 return ojala;
}

void VidAlg::setArray()
{
  arr_.clear();
  for(int i=1;i<=size_;i++)
       arr_.push_back(i);
}

void VidAlg::shuffle()
{
  std::random_shuffle(arr_.begin(), arr_.end());
}

void VidAlg::openOutput(){
   output_.open(videoName_,CV_FOURCC('M','J','P','G'),fps_,cv::Size(size_*sizePerValue_+50,size_+50),true);
}

void VidAlg::closeOutput(){
   output_.release();
}

void VidAlg::selectionSort(){
       shuffle();
       openOutput();
       int comp=0,swaps=0;
       int pos_min,temp;

        for (int i=0; i < arr_.size()-1; i++)
        {
            pos_min = i;//set pos_min to the current index of array
  
                for (int j=i+1; j < arr_.size(); j++)
                {
                comp++;
                if (arr_[j] < arr_[pos_min])
                   pos_min=j;
        //pos_min will keep track of the index that min is in, this is needed when a swap happens
                }
                
        //if pos_min no longer equals i than a smaller value must have been found, so a swap must occur
            if (pos_min != i)
            {
                 swaps++;
                 temp = arr_[i];
                 arr_[i] = arr_[pos_min];
                 arr_[pos_min] = temp;
            }
          output_<<paintArray(comp,swaps);
          
        }
    cv::Mat x= paintArray(comp,swaps);
    for(int i=0;i<fps_;i++) output_<<x;
    closeOutput();
}

void VidAlg::bubble(){
      shuffle();
       openOutput();
      bool swapped = true;
      int comp=0,swaps=0;
      int j = 0;

      int tmp;

      while (swapped) {

            swapped = false;

            j++;

            for (int i = 0; i < arr_.size() - j; i++) {
                  comp++;
                  if (arr_[i] > arr_[i + 1]) {
                        std::swap(arr_[i], arr_[i+1]);
                        swaps++;
                        swapped = true;
                        
                        output_<<paintArray(comp,swaps);

                  }

            }

      }
    cv::Mat x= paintArray(comp,swaps);
    for(int i=0;i<fps_;i++) output_<<x;
    closeOutput();
}



void VidAlg::shakerSort() {
   shuffle();
   openOutput();
  int comp=0,swaps=0;
  for (int i = 0; i < size_/2; i++) {
    bool swapped = false;

    for (int j = i; j < size_ - i - 1; j++) { //one way
        comp++;
        if (arr_[j] > arr_[j+1]) {
           std::swap(arr_[j], arr_[j+1]);
            swaps++;
            swapped = true;
            output_<<paintArray(comp,swaps);
          }

     }

     for (int j = size_ - 2 - i; j > i; j--) { //and back
         comp++;
         if (arr_[j] < arr_[j-1]) {

           std::swap(arr_[j], arr_[j-1]);
           swaps++;
           swapped = true;
           output_<<paintArray(comp,swaps);
         }

     }

     if(!swapped) break; //block (break if no element was swapped - the array is sorted)

   }
    
    cv::Mat x= paintArray(comp,swaps);
    for(int i=0;i<fps_;i++) output_<<x;
    closeOutput();
}


void VidAlg::oddEvenSort() 
{ 
    shuffle();
    openOutput();
    int comp=0,swaps=0;
    bool isSorted = false; // Initially array is unsorted 
  
    while (!isSorted) 
    { 
        isSorted = true; 
  
        // Perform Bubble sort on odd indexed element 
        for (int i=1; i<=size_-2; i=i+2) 
        { 
           comp++;
            if (arr_[i] > arr_[i+1]) 
             { 
                std::swap(arr_[i], arr_[i+1]); 
                swaps++;
                isSorted = false; 
                output_<<paintArray(comp,swaps);
              } 
        } 
  
        // Perform Bubble sort on even indexed element 
        for (int i=0; i<=size_-2; i=i+2) 
        { 
            comp++;
            if (arr_[i] > arr_[i+1]) 
            { 
                swaps++;
                std::swap(arr_[i], arr_[i+1]); 
                isSorted = false; 
                output_<<paintArray(comp,swaps);
            } 
        } 
    } 
  
    cv::Mat x= paintArray(comp,swaps);
    for(int i=0;i<fps_;i++) output_<<x;
    closeOutput();
} 

int getNextGap(int gap) 
{ 
    // Shrink gap by Shrink factor 
    gap = (gap*10)/13; 
  
    if (gap < 1) 
        return 1; 
    return gap; 
} 
  

void VidAlg::combSort() 
{ 

    shuffle();
    openOutput();
    int comp=0,swaps=0;
    // Initialize gap 
    int gap = size_; 
  
    // Initialize swapped as true to make sure that loop runs 
    bool swapped = true; 
  
    // Keep running while gap is more than 1 and last 
    // iteration caused a swap 
    while (gap != 1 || swapped == true) 
    { 
        // Find next gap 
        gap = getNextGap(gap); 
  
        // Initialize swapped as false so that we can 
        // check if swap happened or not 
        swapped = false; 
  
        // Compare all elements with current gap 
        for (int i=0; i<size_-gap; i++) 
        { 
            comp++;
            if (arr_[i] > arr_[i+gap]) 
            { 
                swaps++;
                std::swap(arr_[i], arr_[i+gap]); 
                swapped = true; 
                output_<<paintArray(comp,swaps);
            } 
        } 
    }
    cv::Mat x= paintArray(comp,swaps);
    for(int i=0;i<fps_;i++) output_<<x;
    closeOutput();
} 

