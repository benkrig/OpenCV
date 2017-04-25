#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main()
{
    /*Open camera, close if we can't.*/
    cv::VideoCapture wc;
    if(!wc.open(0)) return 0;
    cv::Mat frame;
    
    int scale = 1;
    int delta = 0;
    
    int ddepth = CV_16S;
    
    /*Start our continous loop.*/
    for(;;)
    {
        wc.read(frame);
        
        GaussianBlur(frame, frame, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT);
        
        cv::Mat gray, draw, grad;
        cvtColor(frame, gray, CV_BGR2GRAY);
        
        cv::Mat dx, dy;
        cv::Mat abs_grad_x, abs_grad_y;
        
        Sobel(gray, dx, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT);
        convertScaleAbs(dx, abs_grad_x);
        
        Sobel(gray, dy, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT);
        convertScaleAbs(dy, abs_grad_y);
        
        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
        cv::namedWindow("image", CV_WINDOW_AUTOSIZE);
        imshow("image", grad);
        
        char key = (char) cv::waitKey(1);
        if(key != -1) break;
    }
    
    cv::waitKey(0);
    return 0;
}
