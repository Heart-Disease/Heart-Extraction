//opencv
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
//C
#include <stdio.h>
//C++
#include <iostream>
#include <sstream>
#include <unistd.h>
using namespace cv;
using namespace std;
bool roi_captured = false;
bool got_roi = false;
Point pt1, pt2;
Mat cap_img;
VideoWriter vw;
//Callback for mousclick event, the x-y coordinate of mouse button-up and button-down 
//are stored in two points pt1, pt2.
void mouse_click(int event, int x, int y, int flags, void *param)
{

    switch(event)
    {
        case CV_EVENT_LBUTTONDOWN:
        {
            std::cout<<"Mouse Pressed"<<std::endl;

            if(!roi_captured)
            {
                pt1.x = 20;
                pt1.y = 20;
            }
            else
            {
                std::cout<<"ROI Already Acquired"<<std::endl;
            }
        break;
        }
        case CV_EVENT_LBUTTONUP:
        {
          if(!got_roi)
        {
            Mat cl;
            std::cout<<"Mouse LBUTTON Released"<<std::endl;

            pt2.x = 200;
            pt2.y = 200;
            cl = cap_img.clone();
            Mat roi(cl, Rect(pt1, pt2));
            Mat prev_imgT = roi.clone();
            std::cout<<"PT1"<<pt1.x<<", "<<pt1.y<<std::endl;
            std::cout<<"PT2"<<pt2.x<<","<<pt2.y<<std::endl;

            imshow("Clone",cl);

            got_roi = true;
        }
        else
        {
            std::cout<<"ROI Already Acquired"<<std::endl;
        }
        break;  
        }

    }

}
//In main open video and wait for roi event to complete by the use.
// You capture roi in pt1 and pt2 you can use the same coordinates for processing // //subsequent frame
int main(int argc, char *argv[])
{
    int frame_num = 0;
    int non_decode_frame =0;
    int count = 1, idx =0;
    int frame_pos =0;

    std::cout<<"Video File "<<argv[1]<<std::endl;

    cv::VideoCapture input_video(argv[1]);

    namedWindow("My_Win",1);

    cvSetMouseCallback("My_Win", mouse_click, 0);

    sleep(1);

    while(input_video.grab())
    {
        cap_img.release();

        if(input_video.retrieve(cap_img))
        {
            imshow("My_Win", cap_img);
            if(!got_roi)
            {
                            //Wait here till user select the desire ROI
                waitKey(0);
            }
            else
            {
                std::cout<<"Got ROI disp prev and curr image"<<std::endl;
                std::cout<<"PT1"<<pt1.x<<" "<<pt1.y<<std::endl;
                std::cout<<"PT2"<<pt2.x<<" "<<pt2.y<<std::endl;
			
		if(vw.isOpened()){
			std::cout<<"VW Opened\n";
		}
                Mat curr_img_t1;
                Mat roi2(cap_img,Rect(pt1, pt2));
                Mat curr_imgT = roi2.clone();
                cvtColor(curr_imgT, curr_img_t1, CV_RGB2GRAY);
    //vw = VideoWriter();         
    //vw.open("output.avi", CV_FOURCC('X','V','I','D'), 30, cv::Size (200,200), true);
                    imshow("curr_img", curr_imgT);
		vw.write(curr_imgT);
//		vw = VideoWriter();			
            // Do remaining processing here on capture roi for every frame
//		if(vw.isOpened())
//			std::cout<<"VW Opened\n";
                               waitKey(30);
                        }
                  }
}
vw.release();
}
