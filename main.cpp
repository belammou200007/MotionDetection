#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <string.h>
using namespace std;
using namespace cv;



bool status_check(Mat diff_threshold)
{
	if (countNonZero(diff_threshold) != 0)
	{
		return true;
	}
	else{
		return false;
	}
}

int sendmsg()
{
	cout << "motion is detected!!!!" << endl;
	return 0;
}



int main()
{
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cerr << "Error opening video stream" << endl;
		return -1;
	}
	namedWindow("Motion Detection", cv::WINDOW_NORMAL);
	int threshold_value = 80;


	while (true)
	{
		bool status;
		Mat frame, previousframe,frame_gray,diff, previousframe_gray, diff_threshold;
		cap >> previousframe;
		cap >> frame;
		if (!previousframe.empty())
		{
			cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
			GaussianBlur(frame_gray, frame_gray, Size(5, 5), 0);
			cvtColor(previousframe, previousframe_gray, cv::COLOR_BGR2GRAY);
			GaussianBlur(previousframe_gray, previousframe_gray, Size(5, 5), 0);
			absdiff(frame_gray, previousframe_gray, diff);
			threshold(diff, diff_threshold, threshold_value, 255, cv::THRESH_BINARY);
			imshow("Motion Detection", diff_threshold);
			status = status_check(diff_threshold);
			if (status)
			{
				sendmsg();
				break;
			}
			

		}
		
		previousframe = frame.clone();
		if (waitKey(1) == 'q') {
			break;
		}
	}
	cap.release();
	destroyAllWindows();

}
