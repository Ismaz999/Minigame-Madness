#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include <windows.h>

#include "monty.h"

using namespace cv;

int MontyClick() {

    std::string image = "C:/Users/Aziz2/Desktop/projet_cpp/mario_opencv/Whack_a_Monty/test.png";
    std::string temp_monty = "C:/Users/Aziz2/Desktop/projet_cpp/mario_opencv/Whack_a_Monty/template_monty.png";
    Mat img = imread(image, IMREAD_COLOR);
    Mat temp = imread(temp_monty);
    Mat result;

    int method = TM_CCORR_NORMED;

    matchTemplate(img, temp, result, method);

    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;

    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

    std::cout << "Coordonées maxloc x : " << maxLoc.x << "coordonnées maxloc y : " << maxLoc.y << std::endl;

    imshow("IMAGE MARIO", img);
    int k = waitKey(0);

    return 0;
}
