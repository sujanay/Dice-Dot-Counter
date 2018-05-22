//==========================================================================
//   Detects the number of dots in dice image
//   Uses SimpleBlobDetector to detect the dots 
//  
//   Sujan Tamang
//   05/02/2018
//==========================================================================

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string> 
#include <sstream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    string image = argv[1];

    if(argc != 2)
    {
      return -1;
    }

    // ==========================================================================
    // Load the image passed from command line
    // ==========================================================================
    Mat img = imread(image, CV_LOAD_IMAGE_GRAYSCALE);   
    Mat color_img = imread(image, CV_LOAD_IMAGE_COLOR);
    if(img.empty())   
    {
        cout << "Error: Cannot read image: " << image << endl;
        return -1;
    }

    // Setup SimpleBlobDetector parameters.
    SimpleBlobDetector::Params params;
    
    // Change the value for thresholds
    params.minThreshold = 10;
    params.maxThreshold = 200;
  
    // Filter by Area
    params.filterByArea = true;
    params.minArea = 250;

    // Filter by Circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.3;

    // Filter by Convexity
    params.filterByConvexity = true;
    params.minConvexity = 0.87;

    // Filter by Inertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.01;

    // Storage for blobs
    vector<KeyPoint> keypoints;

    // Setup detector with params
    SimpleBlobDetector detector(params);

    // Detect blobs
    detector.detect(img, keypoints);
    
    ///// Point2f p=keypoints.pt;
    ///// cout << "p = " << p << ";" << endl; 
    vector< Point2f > p;
    KeyPoint::convert (keypoints, p);	

    // Draw detected blobs as yellowgreen circles.
    Mat img_with_keypoints;
    drawKeypoints(color_img, keypoints, img_with_keypoints, Scalar(100,255,47), 
                      DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    
    // Put text at the top left corner to
    // specify the number of blobs detected.
    std::ostringstream ss;     // used stringstream to convert the number of detected blobs to string
    ss << p.size();

    // string str_disp = p.size()>0?"Sum=" + to_string(p.size()) : "";       // String to be displayed
    string str_disp ="Sum=" + ss.str(); 
    if(str_disp!="")
    {
        putText(img_with_keypoints, str_disp, Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 4); 
    }   

    // Show blobs
    imshow("keypoints", img_with_keypoints);
    waitKey(0);

    return 0;
}

