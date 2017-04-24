#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main()
{
    cv::VideoCapture wc;
    /*Open camera, close if we can't.*/
    if(!wc.open(0)) return 0;
    
    /*Frame to be captured*/
    cv::Mat frame;
    
    /*Start our continous loop.*/
    for(;;)
    {
        /*Grab frame*/
        wc.read(frame);
        
        /*Set up our cv::Mat's*/
        cv::Mat gray, edge, draw;
        
        /*We need Grayscale for Canny Edge Detection*/
        cv::cvtColor(frame, gray, CV_BGR2GRAY);
        
        /*Use OpenCV's implementation of Canny 
         Canny ( input_mat, output_mat, low_threshold, upper_threshold, aperture )*/
        cv::Canny(gray, edge, 50, 150, 3);
        
        /*Canny ( ) outputs an array of edges, we want to combine all these back into an image*/
        edge.convertTo(draw, CV_8U);
        
        /*Show our image*/
        cv::namedWindow("image", CV_WINDOW_AUTOSIZE);
        imshow("image", draw);
        
        /*Stop webcam if key is pressed*/
        char key = (char) cv::waitKey(1);
        if(key != -1) break;
    }
    
    /*Wait for second keypress to close program*/
    cv::waitKey(0);
    return 0;
}
