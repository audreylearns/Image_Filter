#include <opencv2/opencv.hpp>
#include <iostream>
#include "colorize_filters.h" //move all colorize methods here to run

//resize the image for display, param 1 source, param 2 target
void imageResize(cv::Mat image, cv::Mat& resizedImage){
    int windowWidth = 800;  // Desired width of the window
    int windowHeight = 600; // Desired height of the window

    // Calculate the aspect ratio of the original image
    double aspectRatio = static_cast<double>(image.cols) / static_cast<double>(image.rows);

    // Calculate new dimensions while maintaining the aspect ratio
    int newWidth, newHeight;
    if (aspectRatio > 1) { // Image is wider than it is tall
        newWidth = windowWidth;
        newHeight = static_cast<int>(windowWidth / aspectRatio);
    } else { // Image is taller than it is wide
        newHeight = windowHeight;
        newWidth = static_cast<int>(windowHeight * aspectRatio);
    }

    // Resize the image to fit the window
    
    cv::resize(image, resizedImage, cv::Size(newWidth, newHeight));

}

int main(){
    

    std::string imagePath = "tifa.jpeg";
    //Mat is a structure that keeps matrix/image characteristics
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);

    //cv::imshow("Original", image);
    cv::Mat original_resized; //for resized
    imageResize(image, original_resized);
    cv::imshow("original resized", original_resized);

    filterToViolet(image);

    std::string outputPath = "img_alt.jpeg"; 
    cv::imwrite(outputPath, image); //saving to new file
    
    std::cout << "Filtered image saved as: " << outputPath << std::endl;
    cv::Mat alt_resized = cv::imread(outputPath, cv::IMREAD_COLOR);
    imageResize(alt_resized, alt_resized);
    cv::imshow("Altered", alt_resized);


    cv::waitKey(0);
    return 0;
}