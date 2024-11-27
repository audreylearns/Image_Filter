#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h> 
#include <string>
#include "colorize_filters.h" //move all colorize methods here to run
#include "menu.h" 
#include "blur.h" 
#include "edge.h"

#define kernel 7
#define sigma 7
int main(){
    int imageOpt = menuImage();
    int filterby = menu();
    cv::Mat image = imgLoad(imageOpt);
    cv::Mat cpy_image = imgLoad(imageOpt);
    cv::Mat grayImg;

    if (imageOpt == 1){
        cv::imshow("Original", image );
    }else{ //resize to fit window
        imageResize(image,cpy_image);
        cv::imshow("Original", cpy_image);
    }

    switch (filterby){
        case 1:
            filterToRed(image);
            break;
        case 2:
            filterToOrange(image);
            break;
        case 3:
            filterToYellow(image);
            break;
        case 4:
            filterToGreen(image);
            break;
        case 5:
            filterToBlue(image);
            break;
        case 6:
            filterToViolet(image);
            break;
        case 7:
            filterToPink(image);
            break;
        case 8: //gray case 
            grayImg = filterToGrey(image);
            break;                                           
        case 9:
            grayImg = differenceOfGaussian(image, 2, 9, kernel);
            break;
        case 10:
            gaussianBlur(image,kernel,sigma);
            break;
        case 11:
            filterToInverse(image);    
        // code block
    }
    
    std::string outputPath = "img_alt.jpeg"; 
    //case gray
    if (filterby == 8 || filterby == 9){
        cv::imwrite(outputPath, grayImg);
    }else{ //BGR
        cv::imwrite(outputPath, image);
    }
    
    cv::Mat alt = cv::imread(outputPath, cv::IMREAD_COLOR);
    //resizing if-else
    if (imageOpt == 1){
        cv::imshow("Altered", alt );
    }else{ //resize to fit window
        cv::Mat alt_cpy = cv::imread(outputPath, cv::IMREAD_COLOR);
        imageResize(alt,alt_cpy);
        cv::imshow("Altered", alt_cpy);
    }
    
    {
        //std::string imagePath = "336x297.jpg";
        //Mat is a structure that keeps matrix/image characteristics
        //cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR); //BGR values

        //cv::imshow("Original", image);
        //cv::Mat original_resized; //for resized
        //imageResize(image, original_resized);
        //cv::imshow("original resized", original_resized);
        //cv::imshow("original", image);

        //cv::Mat grayImg = filterToGrey(image);

        //std::string outputPath = "img_alt.jpeg"; 
        //cv::imwrite(outputPath, grayImg);
        //cv::imwrite(outputPath, image); //saving to new file
        
        //std::cout << "Filtered image saved as: " << outputPath << std::endl;
        //cv::Mat alt_resized = cv::imread(outputPath, cv::IMREAD_COLOR);
        
        //imageResize(alt_resized, alt_resized);
        // cv::imshow("Altered", alt_resized);
        // cv::imshow("Altered", alt_resized);
    }


    cv::waitKey(0);
    return 0;
}