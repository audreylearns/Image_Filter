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

// #define parallelized
#define regular

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
    auto start = chrono::high_resolution_clock::now();
    auto stop = chrono::high_resolution_clock::now();
    auto nano_duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    

    if (imageOpt == 1){
        cv::imshow("Original", image );
    }else{ //resize to fit window
        imageResize(image,cpy_image);
        cv::imshow("Original", cpy_image);
    }

    switch (filterby){
        case 1:
            start = chrono::high_resolution_clock::now();
            filterToRed(image);
            stop = chrono::high_resolution_clock::now();
            nano_duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            break;
        case 2:
            start = chrono::high_resolution_clock::now();
            filterToOrange(image);
            stop = chrono::high_resolution_clock::now();
            nano_duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            break;
        case 3:
            start = chrono::high_resolution_clock::now();
            filterToYellow(image);
            stop = chrono::high_resolution_clock::now();
            nano_duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            break;
        case 4:
            start = chrono::high_resolution_clock::now();
            filterToGreen(image);
            stop = chrono::high_resolution_clock::now();
            nano_duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            break;
        case 5:
            start = chrono::high_resolution_clock::now();
            filterToBlue(image);
            stop = chrono::high_resolution_clock::now();
            nano_duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            break;
        case 6:
            start = chrono::high_resolution_clock::now();
            filterToViolet(image);
            stop = chrono::high_resolution_clock::now();
            nano_duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            break;
        case 7:
            start = chrono::high_resolution_clock::now();
            filterToPink(image);
            stop = chrono::high_resolution_clock::now();
            nano_duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            break;
        case 8: //gray case 
            start = chrono::high_resolution_clock::now();
            grayImg = filterToGrey(image);
            stop = chrono::high_resolution_clock::now();
            nano_duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            break;                                           
        case 9:
            start = chrono::high_resolution_clock::now();
            grayImg = differenceOfGaussian(image, 2, 9, kernel);
            stop = chrono::high_resolution_clock::now();
            nano_duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            break;
        case 10:
            start = chrono::high_resolution_clock::now();
            gaussianBlur(image,kernel,sigma);
            stop = chrono::high_resolution_clock::now();
            nano_duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            break;
        case 11:
            start = chrono::high_resolution_clock::now();
            filterToInverse(image);    
            stop = chrono::high_resolution_clock::now();
            nano_duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            break;
    }
    
    std::cout << "Image processed for " << nano_duration.count() << " nanoseconds" << endl;
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