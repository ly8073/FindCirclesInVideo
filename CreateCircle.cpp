#include<opencv/cv.h>
#include<opencv.hpp>
#include<string>
using namespace std;
using namespace cv;
//生成圆环图
void CircleCreate(string file_name)
{
	Mat paper = 255 * Mat::ones(1080, 1920, CV_8UC1);
	int x_step = 320;
	int y_step = 180;
	for (int i = 0; i < 3; i++)
	{
		int center_x = (2 * i + 1) * x_step;
		for (int j = 0; j < 3; j++)
		{
			int center_y = (2 * j + 1) * y_step;
			circle(paper, Point(center_x, center_y), 130, (0, 0, 0), 30);
		}
	}
	imwrite(file_name, paper);
	/*
	imshow("paper", paper);
	waitKey();
	destroyWindow("paper");
	*/
}
//寻找圆心与半径
void FindCircle(Mat& frame)
{
	Mat gray;
	cvtColor(frame, gray, COLOR_BGR2GRAY);
	vector<Vec3f> circles;
	HoughCircles(gray, circles, HOUGH_GRADIENT, 1, 50, 100, 100, 0, 200);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心
		circle(frame, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓
		circle(frame, center, radius, Scalar(255, 50, 0), 3, 8, 0);
	}
}
//处理视频
void DealVideo(string file_name)
{
	VideoCapture Video;
	Video.open(file_name);
	while (true)
	{
		Mat frame;
		Video >> frame;
		if (frame.empty())
		{
			break;
		}
		FindCircle(frame);
		imshow("Video", frame);
		waitKey(10);
	}
}


int main()
{
	//CircleCreate(".\\imgs\\circles.jpg");
	DealVideo(".\\imgs\\video.mp4");
	return 0;
}