#include <iostream> 
#include <opencv2/opencv.hpp>
#include <stdlib.h> 
using namespace std;
int menu(){
    bool selection = false;
    int filterTo = 0;
    while (!selection){
        cout << "Please enter the number of your filter type:" << endl;
        cout << "==============================" << endl << endl;
        cout << "1. RED" << endl;
        cout << "2. ORANGE" << endl;
        cout << "3. YELLOW" << endl;
        cout << "4. GREEN" << endl;
        cout << "5. BLUE" << endl;
        cout << "6. VIOLET" << endl;
        cout << "7. PINK" << endl;
        cout << "8. GRAY" << endl;
        cout << "9. Edge Outline" << endl;
        cout << "10. BLUR" << endl;
        cout << "11. Inverse" << endl;
        cout << "==============================" << endl << endl;
        cin >> filterTo;
        if (!(filterTo <1 || filterTo > 11)){
            selection = true;
        }
    }
    return filterTo;
}

int menuImage(){
    bool selection = false;
    int img_opt = 0;
    while (!selection){
        cout << "Please enter the number of "<< endl;
        cout << "image sample to use from the " << endl;
        cout << "following:" << endl;
        cout << "==============================" << endl << endl;
        cout << "0. Kernel test"<< endl;
        cout << "1. small" << endl;
        cout << "2. 1080p" << endl;
        cout << "3. 4k" << endl;
        cout << "4. 8k" << endl;
        cout << "5. large" << endl;
        cout << "==============================" << endl << endl;
        cin >> img_opt;
        if (!(img_opt <0 || img_opt > 5)){
            selection = true;
        }
    }
    return img_opt;
}

cv::Mat imgLoad(int selection){
    std::string imagePath = "";
    switch (selection){
        case 0:
            imagePath = "7x7.jpg";
            break;
        case 1:
            imagePath = "336x297.jpg";
            break;
        case 2:
            imagePath = "1080p.png";
            break;
        case 3:
            imagePath = "4k_image.jpg";
            break;
        case 4:
            imagePath = "8k_image.jpg";
            break;
        case 5:
            imagePath = "6846x4677.png";
            break;
    };
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR); //BGR values
    return image;
}

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