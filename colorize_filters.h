#include <opencv2/opencv.hpp>
//Methods to filter the image paramter to primary colors (Red, Green, Blue) OR secondary Colors (Orange, green, purple)

void filterToRed(cv::Mat& image) {
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            //[0] : blue, //[1] : green, //[2] : red,  
            pixel[0] = 0; // BLUE
            pixel[1] = 0; // green
        }
    }
}

void filterToBlue(cv::Mat& image) {
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            //[0] : blue, //[1] : green, //[2] : red,  
            pixel[1] = 0; // green
            pixel[2] = 0; // red
        }
    }
}

void filterToGreen(cv::Mat& image) {
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            //[0] : blue, //[1] : green, //[2] : red,  
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
            //[0] : blue, //[1] : green, //[2] : red
            pixel[1] = 255; // Set green to 255
            pixel[2] = 255; // Set red to 255
        }
    }
}

void filterToOrange(cv::Mat& image) {
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            //[0] : blue, //[1] : green, //[2] : red
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
            pixel[0] = 255;   // Set blue to 255
            pixel[2] = 165;   // Set red to 255
        }
    }
}