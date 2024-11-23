#include <opencv2/opencv.hpp>
#include <vector>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif


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



