#include <opencv2/opencv.hpp>
#include <iostream>
//Methods to filter the image paramter to primary colors (Red, Green, Blue) OR secondary Colors (Orange, green, purple)
//[0] :blue, [1] :green, [2] : red
void filterToRed(cv::Mat& image) {
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            pixel[0] = 0; // BLUE
            pixel[1] = 0; // green
        }
    }
}

void filterToBlue(cv::Mat& image) {
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            pixel[1] = 0; // green
            pixel[2] = 0; // red
        }
    }
}

void filterToGreen(cv::Mat& image) {
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            pixel[0] = 0; // BLUE
            pixel[2] = 0; // red
        }
    }
}

//Secondary colors
void filterToYellow(cv::Mat& image){
        for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            pixel[1] = 255; // Set green to 255
            pixel[2] = 255; // Set red to 255
        }
    }
}

void filterToOrange(cv::Mat& image) {
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            pixel[1] = 165;   // Set green to a value (e.g., 165 for orange)
            pixel[2] = 255;   // Set red to 255
        }
    }
}

void filterToPink(cv::Mat& image) {
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            pixel[0] = 255;   // Set blue to 255
            pixel[2] = 255;   // Set red to 255
        }
    }
}

void filterToViolet(cv::Mat& image) {
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            pixel[0] = 128;   // Set blue to 255
            pixel[2] = 128;   // Set red to 255
        }
    }
}


cv::Mat filterToGrey(cv::Mat image) {
    cv::Mat gray(image.rows, image.cols, cv::IMREAD_GRAYSCALE); // Create a grayscale new gray img, as single channel grayscale image
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            // Calculate the grayscale value of the pixel using Luma Grayscale conversion
            uchar grayValue = static_cast<uchar>(0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0]);
            gray.at<uchar>(i, j) = grayValue; // Set the grayscale value, single channel
            if (i==100 && j == 100){
                std::cout << pixel;
                std::cout << (int)grayValue;
                std::cout << (int)gray.at<uchar>(i, j);
            }

        }
    }
    return gray;
}

void filterToInverse(cv::Mat& image) {
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            auto green = pixel[1];
            pixel[1] = pixel[2]; // green to red
            pixel[2] = green; // red to green
        }
    }
}