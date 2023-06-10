//
// Created by 孙浩博 on 2023/3/21.
//
#include <iostream>
#include <string>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
int threshold_value = 0;
Mat gray_image;
Mat img;
Mat thresholded_image_otsu;
Mat thresholded_image_binary;
int version(int argc, char *argv[])
{
//Print the OpenCV version
    printf ("OpenCV version: %d.%d\n", CV_MAJOR_VERSION,
            CV_MINOR_VERSION);
    return 0;
}

void track_bar(int, void*) {

    threshold(gray_image, thresholded_image_binary, threshold_value, 255, THRESH_BINARY);

    imshow("threshold image binary", thresholded_image_binary);
}


int main(int argc, char** argv) {
    // Check if an image path was provided
    string name = argv[1];

    img = imread(argv[1], IMREAD_UNCHANGED);
    if (img.empty()) {
        cout << "Failed to load image" << endl;
        return 1;
    }


    cvtColor(img, gray_image, cv::COLOR_BGR2GRAY, 0);


    threshold(gray_image, thresholded_image_otsu, 0,255,THRESH_OTSU);
//    threshold(gray_image, thresholded_image_otsu, 0,255,THRESH_BINARY);




//
    namedWindow("threshold image binary", cv::WINDOW_AUTOSIZE);
    namedWindow("threshold image otsu", cv::WINDOW_AUTOSIZE);
    imshow("threshold image otsu",thresholded_image_otsu);
    threshold(gray_image, thresholded_image_binary, 0, 255, THRESH_BINARY);
    imshow("threshold image binary", thresholded_image_binary);
    createTrackbar("track","threshold image binary",&threshold_value,255, track_bar);



//    namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
//    imshow("Original Image", img);
    waitKey(0);
    imwrite("OTSU" + name, thresholded_image_otsu);
    imwrite("BINARY" + name, thresholded_image_binary);

    return 0;


}




