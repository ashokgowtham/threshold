#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>

char DEFAULT_OUTPUT_FODLER[] = ".";
int DEFAULT_TIME_INTERVAL = 1;
int DEFAULT_CAMERA = 0;

using namespace cv;
void writeOutputImage(Mat& image, char *src_file) {
    char path[1024] = {};
    sprintf(path, "%s.thresholded.png", src_file);
    imwrite(path, image );
}

int main( int argc, char** argv )
{
    if( argc != 2)
    {
        printf(" Usage: threshold ImageToThreshold\n");
        return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        printf("Could not open or find the image\n");
        return -1;
    }

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.
    waitKey(0);                                          // Wait for a keystroke in the window
    
    Mat gray_image;
    cvtColor( image, gray_image, CV_BGR2GRAY );
    imshow( "Display window", gray_image );                   // Show our image inside it.
    waitKey(0);                                          // Wait for a keystroke in the window

    Mat hist_image;
    equalizeHist( gray_image, hist_image );
    imshow( "Display window", hist_image );                   // Show our image inside it.
    waitKey(0);                                          // Wait for a keystroke in the window

    Mat thresholded_image;
    Mat adaptive_thresholded_image;
    Mat binary_image;
    adaptiveThreshold(gray_image,adaptive_thresholded_image,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY_INV,151,30);
    threshold(hist_image,thresholded_image,50,255,THRESH_BINARY_INV);

    imshow( "Display window", thresholded_image );                   // Show our image inside it.
    waitKey(0);                                          // Wait for a keystroke in the window

    imshow( "Display window", adaptive_thresholded_image );                   // Show our image inside it.
    waitKey(0);                                          // Wait for a keystroke in the window

    bitwise_and(thresholded_image,adaptive_thresholded_image,binary_image);
    imshow( "Display window", binary_image );                   // Show our image inside it.
    waitKey(0);                                          // Wait for a keystroke in the window

    bitwise_not(binary_image,binary_image);
    imshow( "Display window", binary_image );                   // Show our image inside it.
    waitKey(0);                                          // Wait for a keystroke in the window

    writeOutputImage(binary_image,argv[1]);

    return 0;
}