#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main()
{
    /*I will be hard coding scope for practice and better understanding of what I'm building Objects from.
     If you do not understand or know what class I am instancing these objects from, click the links in the #include section.*/
    cv::VideoCapture wc;
    /*Open camera, close if we can't.*/
    if(!wc.open(0)) return 0;
    
    /*Set up our Haar Cascade.
     haarcascade_frontalface_alt2.xml comes prepackaged with OpenCV, you can create your own or find another if you'd like.*/
    cv::CascadeClassifier frontal_face_cascade;
    frontal_face_cascade.load("/Users/benkrig/opencv/opencv/data/haarcascades/haarcascade_frontalface_alt2.xml");
    
    /*Set up our storage frame*/
    cv::Mat frame;
    
    /*Start our continous loop.*/
    for(;;)
    {
        /*Capture current frame from camera*/
        wc.read(frame);
        
        /*Go to grayscale*/
        cv::Mat g_value;
        cvtColor(frame, g_value, CV_BGR2GRAY);
        
        /*Store faces found from frame*/
        std::vector < cv::Rect_< int > > faces;
        /*detect faces FROM g_value and store in our vectore faces*/
        frontal_face_cascade.detectMultiScale(g_value, faces);
        
        /*iterate and draw rect around each face*/
        for(int i = 0; i < faces.size(); i ++)
        {
            /*Get current face*/
            cv::Rect face_i = faces[i];
            
            /*Draw rectangle on our frame*/
            rectangle(frame, face_i, CV_RGB(255,0,0), 1);
            
            /*Not needed, but draw text over rectangle to show face count*/
            int pos_x = std::max(face_i.tl().x - 10, 0);
            int pos_y = std::max(face_i.tl().y - 10, 0);
            putText(frame, "Face " + std::to_string(i), cv::Point(pos_x, pos_y), cv::FONT_ITALIC, 1.0, CV_RGB(255,0,0), 2.0);
        }
        /*Show window with frame*/
        imshow("facial_recognition", frame);
        
        /*end if any key is pressed*/
        char key = (char) cv::waitKey(1);
        if(key != -1) break;
    }
    
    cv::waitKey(0);
    return 0;
}
