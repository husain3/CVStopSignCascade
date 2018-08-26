#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/* Function Headers */
void detectAndDisplay(Mat frame);

/* Global Variables */
String stop_sign_cascade_name = "cascade.xml"; //Will need to modify this for path or put this code in the same direct
String test_video = "cropstopsignvid2.mp4";
CascadeClassifier stop_sign_cascade;
String window_name = "Capture - Stop Sign Detection";

int main(int argc, const char ** argv)
{
	Mat stop_sign_img;
	Mat empty_mat;

	std::vector<Rect> stopSigns;
	Mat frame_gray;

	CvCapture* capture;
	Mat frame;

	//LOAD THE CASCADE
	if(!stop_sign_cascade.load(stop_sign_cascade_name))
	{
		printf("--Error loading trained cascade\n");
		return -1;
	}

	//FOR LOADING VIDEOS
	VideoCapture cap(test_video);
	if(!cap.isOpened())
	{
		printf("--Error loading video\n");
		return -1;
	}
	
	//FOR LOADING PICTURES
	//stop_sign_img = imread("infiniti.png");
	//imshow("manhan", stop_sign_img);

	//GRAB VIDEO FRAME
	while(cap.read(frame))
	{
		//imshow("manhan", frame);
		if(!frame.empty())
		{
			//detectAndDisplay(frame);
			cvtColor(frame, frame_gray, CV_BGR2GRAY);
			equalizeHist(frame_gray, frame_gray);
			stop_sign_cascade.detectMultiScale(frame_gray, stopSigns, 1.1, 4, 0|CV_HAAR_SCALE_IMAGE, Size(50, 50));
			for(std::vector<Rect>::size_type i = 0; i != stopSigns.size(); i++)
			{
				cv::Rect rect(stopSigns[i].x, stopSigns[i].y, stopSigns[i].width, stopSigns[i].height);
				cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 12);
			}
			imshow("stopsigndetect", frame);
			waitKey(1);
		}
		else
		{
			printf("-- No captured frame -- Break!\n");
			break;
		}

	}
	//detectAndDisplay(stop_sign_img);

	//waitKey(0);
}

void detectAndDisplay(Mat frame)
{
	std::vector<Rect> stopSigns;
	Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	cout << "Size: " << stopSigns.size() << '\n';
	stop_sign_cascade.detectMultiScale(frame_gray, stopSigns, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, Size(50, 50));
	cout << "Size: " << stopSigns.size() << '\n';
	//cout << stopSigns[0].x << " " << stopSigns[0].y << " " << stopSigns[0].width << " " << stopSigns[0].height << '\n';

	//cv::Rect rect(stopSigns[0].x, stopSigns[0].y, stopSigns[0].width, stopSigns[0].height);
	//cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 12);

	for(std::vector<Rect>::size_type i = 0; i != stopSigns.size(); i++)
	{
		cv::Rect rect(stopSigns[i].x, stopSigns[i].y, stopSigns[i].width, stopSigns[i].height);
		cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 12);
	}
	
	//cv::namedWindow("stopsigndetect", WINDOW_NORMAL);
	imshow("stopsigndetect", frame); //1024, 768
	//cv::resizeWindow("stopsigndetect", 1024, 768);
	
	waitKey(0);
}


//TO BUILD: g++ `pkg-config --cflags --libs opencv` stopSignDetectorForVideo.cc
//TO MOVE TO CLASSIFIER FOLDER: mv a.out classifier/
///Volumes/Macintosh SD/arshadhusain/Desktop/Computer Vision and Autonomous Car Work/All Computer Vision Projects/traffic_signs/stop_sign_detection/opencv_cctraining_real/classifier


