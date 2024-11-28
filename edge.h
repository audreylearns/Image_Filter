#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

//3x3
cv::Mat differenceOfGaussian(cv::Mat& image, double sigma1, double sigma2, int kernelSz) {

    cv::Mat im1 = image.clone(); //clone for blur less intensity
    cv::Mat im2 = image.clone(); //clone for higher intensity
    gaussianBlur(im1, kernelSz, sigma1); //7 
    //cv::imshow("low", im1);
    gaussianBlur(im2, kernelSz, sigma2); //13
    //cv::imshow("high", im2);
    cv::Mat im1Gray = filterToGrey(im1);
    cv::Mat im2Gray = filterToGrey(im2); //convert to gray
    // cv::imshow("low", im1Gray);
    // cv::imshow("high", im2Gray);
    //dOg
    cv::Mat difference = cv::Mat::zeros(image.size(),  cv::IMREAD_GRAYSCALE);
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            uchar pixel1 = im1Gray.at<uchar>(i, j);
            uchar pixel2 = im2Gray.at<uchar>(i, j);

            // Calculate the absolute difference
            int diff = static_cast<int>(pixel1) - static_cast<int>(pixel2);
            difference.at<uchar>(i, j) = static_cast<uchar>(std::abs(diff));
        }
    }
    //cv::imshow("diff", difference);
    //threshold sequence to invert color
    for (int i = 0; i < difference.rows; ++i) {
        for (int j = 0; j < difference.cols; ++j) {
            uchar pixel = difference.at<uchar>(i, j);
            if (pixel > 4) {
                difference.at<uchar>(i, j) = 0; // Black for edges
            } else {
                difference.at<uchar>(i, j) = 255; // White for non-edges
            }
        }
    }

    return difference;

}