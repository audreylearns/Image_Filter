#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h> 
#include <string>
#include <chrono> // for time duration
#include "menu.h" 
// INSTRUCTIONS!!!!! =================================================
//      comment out parallelized to run regularly
//      comment out regular to not run in parallel
//====================================================================

#define parallelized
// #define regular

#ifdef regular
    #include "colorize_filters.h" //move all colorize methods here to run
    #include "blur.h" 
    #include "edge.h"
#endif

#ifdef parallelized
    #include "parallel.h"
#endif


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
            break;
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
    

    cv::waitKey(0);
    return 0;
}