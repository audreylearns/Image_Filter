//Every filter method is pararellized here with duration count
#include <opencv2/opencv.hpp> 
#include <iostream> //for i/o
#include <omp.h>   //for parallelize
#include <vector>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

// INSTRUCTIONS!!!!! =================================================
//      comment out single_parallel_region to encapsulated directive
//      comment out double_parallel_region for multiple wake-sleep cycle
//====================================================================

#define single_parallel_region
// #define double_parallel_region


//color filters =========================================================
void filterToRed(cv::Mat& image) {
    #pragma omp parallel for collapse (2)
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            pixel[0] = 0; // BLUE
            pixel[1] = 0; // green
        }
    }
}

void filterToBlue(cv::Mat& image) {
    #pragma omp parallel for collapse (2)
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            pixel[1] = 0; // green
            pixel[2] = 0; // red
        }
    }
}

void filterToGreen(cv::Mat& image) {
    #pragma omp parallel for collapse (2)
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
    #pragma omp parallel for collapse (2)
        for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            pixel[1] = 255; // Set green to 255
            pixel[2] = 255; // Set red to 255
        }
    }
}

void filterToOrange(cv::Mat& image) {
    #pragma omp parallel for collapse (2)
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            pixel[1] = 165;   // Set green to a value (e.g., 165 for orange)
            pixel[2] = 255;   // Set red to 255
        }
    }
}

void filterToPink(cv::Mat& image) {
    #pragma omp parallel for collapse (2)
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            pixel[0] = 255;   // Set blue to 255
            pixel[2] = 255;   // Set red to 255
        }
    }
}

void filterToViolet(cv::Mat& image) {
    #pragma omp parallel for collapse (2)
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
    #pragma omp parallel for collapse (2)
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            // Calculate the grayscale value of the pixel using Luma Grayscale conversion
            uchar grayValue = static_cast<uchar>(0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0]);
            gray.at<uchar>(i, j) = grayValue; // Set the grayscale value, single channel

        }
    }
    return gray;
}

void filterToInverse(cv::Mat& image) {
    #pragma omp parallel for collapse (2)
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            auto green = pixel[1];
            pixel[1] = pixel[2]; // green to red
            pixel[2] = green; // red to green
        }
    }
}

//blur filter =========================================================

//clamp copy from std::clamp
//val to check if within range
template<typename T>
T clamp(T val, T mn, T mx){
    return std::max(std::min(val, mx), mn);
    //inner fn: compare val to max-boundary..... rtn mx or val
    //outer fn: res from ^ is compared to low-boundary..... rtn mn or res
}


//matrix image to be processed
//kernelsize, odd number for center pixel
//sigma, standard deviation for gaussian kernel higher sigma value == greater blur intensity
void gaussianBlur(cv::Mat& image, int kernelSize, double sigma) {
    // Create a Gaussian kernel, 
    int halfSize = kernelSize / 2; //num of neighboring pixels to access ie 5x5 pixels considered if kernel is 5 w halfsize of 2
    std::vector<std::vector<double>> kernel(kernelSize, std::vector<double>(kernelSize)); //a 5x5 matrix ex
    double sum = 0.0; //accum sum of all kernel vals for normalization
    for (int x = -halfSize; x <= halfSize; ++x) { // horizontal dimension
        for (int y = -halfSize; y <= halfSize; ++y) { // vertical
            double exponent = -(x * x + y * y) / (2 * sigma * sigma); //Gaussian distribution exponent
            kernel[x + halfSize][y + halfSize] = (1 / (2 * M_PI * sigma * sigma)) * exp(exponent); //gaussian value at position(x,y)
            sum += kernel[x + halfSize][y + halfSize]; //accum sum of all kernel vals for normalization
        }
    }

    // Normalize the kernel, sum of all the weights in the kernel equals 1
    for (int x = 0; x < kernelSize; ++x) { // rows
        for (int y = 0; y < kernelSize; ++y) { //cols
            kernel[x][y] /= sum; // divide each kernel to sum, total sum of the kernel == 1
        }
    }

    cv::Mat blurredImage = image.clone();
    // Apply the Gaussian kernel to each pixel
    #pragma omp parallel for collapse (2) num_threads(12) 
    for (int i = 0; i < image.rows; ++i) { //loop into image matrix
        for (int j = 0; j < image.cols; ++j) { //loop into image matrix
            cv::Vec3b newPixel(0, 0, 0); // black pixel
            for (int kx = -halfSize; kx <= halfSize; ++kx) { // access the neighboring pixels 
                for (int ky = -halfSize; ky <= halfSize; ++ky) { // access the neighboring pixels 
                    int xIndex = clamp(i + kx, 0, image.rows - 1); // neighbow pixel x coordinate
                    int yIndex = clamp(j + ky, 0, image.cols - 1); // neighbow pixel y coordinate
                    cv::Vec3b pixel = image.at<cv::Vec3b>(xIndex, yIndex); // neighbor pixel
                    double weight = kernel[kx + halfSize][ky + halfSize]; //gaussian kernel weight

                    newPixel[0] += static_cast<uchar>(pixel[0] * weight);  //new blue channel
                    newPixel[1] += static_cast<uchar>(pixel[1] * weight); //new green channel
                    newPixel[2] += static_cast<uchar>(pixel[2] * weight); //new red channel
                }
            }
            blurredImage.at<cv::Vec3b>(i, j) = newPixel;
        }
    }
    // Copy the blurred image back to the original image
    image = blurredImage;
}



//differenceOfGaussian =========================================================
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
    #ifdef single_parallel_region
        #pragma omp parallel num_threads(12)
        {
            #pragma omp for 
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
            #pragma omp for 
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

        }
    #endif
    
    #ifdef double_parallel_region
        #pragma omp parallel for collapse (2) num_threads(12) 
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
        #pragma omp parallel for collapse (2) num_threads(12) 
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
    #endif

    return difference;

}