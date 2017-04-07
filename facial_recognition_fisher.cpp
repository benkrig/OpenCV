/*
My output for running this is:
First Label: 1
First Confidence: 14.203817
second Label: 0
second Confidence: 0.000000
third Label: 0
third Confidence: 910.301280
Program ended with exit code: 0

So, first image is analyzed correctly. That was an image of my face and the trainers were labeled as 1.

Second image was analyzed correctly also, that was a picture of harrison ford, and trainers were labeled at 0.

Third image was analyzed incorrectly, but we can see that the confidence (or distance) was really high.

That's where model -> setThreshold(DOUBLE); comes into play. You'd play around with that value until it was rejecting
the third label.

*/



#include <iostream>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/face.hpp"



int main()
{
    std::vector<cv::Mat> images;
    std::vector<int> labels;
    
    
    //Default to resize images too. This doesn't matter too much
    cv::Size size(250,250);
    

    //These are the images we will be identifying, 1 image of myself, 1 image of harrison ford, 1 image of hillary clinton
    cv::Mat ben;
    cv::Mat harrison;
    cv::Mat hillary;
    resize(cv::imread("/Users/benkrig/Desktop/ben9.jpg", CV_LOAD_IMAGE_GRAYSCALE), ben, size, 1.0, 1.0, cv::INTER_CUBIC);
    resize(cv::imread("/Users/benkrig/wwwbenkrigcom/public/blogs/ford/0.jpeg", CV_LOAD_IMAGE_GRAYSCALE), harrison, size, 1.0, 1.0, cv::INTER_CUBIC);
    resize(cv::imread("/Users/benkrig/Desktop/hillary.jpg", CV_LOAD_IMAGE_GRAYSCALE), obama, size, 1.0, 1.0, cv::INTER_CUBIC);
    
    //These are ALL different images of Harrison Ford's face.
    images.push_back(cv::imread("/Users/benkrig/wwwbenkrigcom/public/blogs/ford/0.jpeg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(0);
    images.push_back(cv::imread("/Users/benkrig/wwwbenkrigcom/public/blogs/ford/1.jpeg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(0);
    images.push_back(cv::imread("/Users/benkrig/wwwbenkrigcom/public/blogs/ford/2.jpeg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(0);
    images.push_back(cv::imread("/Users/benkrig/wwwbenkrigcom/public/blogs/ford/3.jpeg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(0);
    images.push_back(cv::imread("/Users/benkrig/wwwbenkrigcom/public/blogs/ford/4.jpeg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(0);
    images.push_back(cv::imread("/Users/benkrig/wwwbenkrigcom/public/blogs/ford/5.jpeg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(0);
    
    //These are ALL different images of my face
    images.push_back(cv::imread("/Users/benkrig/Desktop/ben1.jpg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(1);
    images.push_back(cv::imread("/Users/benkrig/Desktop/ben2.jpg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(1);
    images.push_back(cv::imread("/Users/benkrig/Desktop/ben3.jpg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(1);
    images.push_back(cv::imread("/Users/benkrig/Desktop/ben4.jpg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(1);
    images.push_back(cv::imread("/Users/benkrig/Desktop/ben5.jpg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(1);
    images.push_back(cv::imread("/Users/benkrig/Desktop/ben6.jpg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(1);
    images.push_back(cv::imread("/Users/benkrig/Desktop/ben7.jpg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(1);
    images.push_back(cv::imread("/Users/benkrig/Desktop/ben8.jpg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(1);
    
    
    
    
    //Resize all of our images
    std::vector<cv::Mat> resized_imgs;
    for(int i = 0; i < images.size(); i ++)
    {
        cv::Mat images_index;
        resize(images[i], images_index, size, 1.0, 1.0, cv::INTER_CUBIC);
        
        resized_imgs.push_back(images_index);
    }
    
    
    
    //Create our FisherFaceRecognizer
    cv::Ptr<cv::face::FaceRecognizer> model =  cv::face::createFisherFaceRecognizer();
    
    //Train it with our resized images and labels
    model->train(resized_imgs, labels);
    
    //Set these initially to -1 and 0.0 to prove we are ACTUALLY changing the value.
    int predicted_label = -1;
    double predicted_confidence = 0.0;
    //model->setThreshold(5000);
    // Get the prediction and associated confidence from the model
    model->predict(ben, predicted_label, predicted_confidence);
    std::printf("First Label: %d\n", predicted_label);
    std::printf("First Confidence: %f\n", predicted_confidence);
    
    model->predict(harrison, predicted_label, predicted_confidence);
    std::printf("second Label: %d\n", predicted_label);
    std::printf("second Confidence: %f\n", predicted_confidence);
    
    model->predict(obama, predicted_label, predicted_confidence);
    std::printf("third Label: %d\n", predicted_label);
    std::printf("third Confidence: %f\n", predicted_confidence);
    
    return 0;
}


