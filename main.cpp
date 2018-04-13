#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>

using namespace cv;

int main(int argc, char **argv) {

    Mat image;
    image = imread("../test.jpg", IMREAD_COLOR);

    if (!image.data) {
        printf("No image data \n");
        return -1;
    }

//    Mat resizeImage;
//    resize(image, resizeImage, Size(960, 540));

    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    Mat binaryImage;
    threshold(grayImage, binaryImage, 85, 255, CV_THRESH_BINARY_INV);

    Mat element1 = getStructuringElement(MORPH_RECT, Size(1, 1));
    Mat erosionImage;
    erode(binaryImage, erosionImage, element1);

    Mat element2 = getStructuringElement(MORPH_RECT, Size(6, 6));
    Mat dilationImage;
    dilate(erosionImage, dilationImage, element2);

    tesseract::TessBaseAPI tess;
    tess.Init("../tessdata", "num", tesseract::OEM_DEFAULT);
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    tess.SetImage(dilationImage.data, dilationImage.cols, dilationImage.rows, 1, dilationImage.cols);

//    imwrite("/home/yangming/Develop/Projects/Cpp/cv_test/dilation.tiff", dilationImage);

    // Get the text
    char *out = tess.GetUTF8Text();
    std::cout << out << std::endl;

    namedWindow("Display binaryImage", WINDOW_AUTOSIZE);
    imshow("Display binaryImage", dilationImage);
    waitKey(0);

    return 0;
}