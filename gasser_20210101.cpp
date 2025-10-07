

//filter 9

#include <opencv2/opencv4.hpp>
#include <string>
#include <iostream>

using namespace cv;
using namespace std;


Mat addSolidFrame(const Mat& img, int thickness, int padding, const Scalar& color) {
    // Add inner space
    Mat withPadding;
    copyMakeBorder(img, withPadding, padding, padding, padding, padding, BORDER_CONSTANT, Scalar(255, 255, 255)); // white padding
    // Add frame
    Mat framed;
    copyMakeBorder(withPadding, framed, thickness, thickness, thickness, thickness, BORDER_CONSTANT, color);
    return framed;
}

Mat addDoubleFrame(const Mat& img, int outerThickness, int padding, const Scalar& outerColor, const Scalar& innerColor, int innerThickness = 8) {
    Mat temp;
    // inner space
    copyMakeBorder(img, temp, padding, padding, padding, padding, BORDER_CONSTANT, Scalar(255, 255, 255));
    //inner frame (thin)
    copyMakeBorder(temp, temp, innerThickness, innerThickness, innerThickness, innerThickness, BORDER_CONSTANT, innerColor);
    //outer frame
    Mat framed;
    copyMakeBorder(temp, framed, outerThickness, outerThickness, outerThickness, outerThickness, BORDER_CONSTANT, outerColor);
    return framed;
}

Mat addCornerFrame(const Mat& img, int thickness, int padding, const Scalar& frameColor, int cornerSize = 30, int cornerThickness = 6) {
    //base framed image
    Mat padded;
    copyMakeBorder(img, padded, padding, padding, padding, padding, BORDER_CONSTANT, Scalar(255, 255, 255));
    Mat framed;
    copyMakeBorder(padded, framed, thickness, thickness, thickness, thickness, BORDER_CONSTANT, frameColor);

    // Draw corner decorations
    Scalar cornerColor = Scalar(255, 255, 255); // white decoration by default
    int h = framed.rows, w = framed.cols;

    // top-left
    rectangle(framed, Point(thickness / 2, thickness / 2), Point(thickness / 2 + cornerSize, thickness / 2 + cornerThickness), cornerColor, FILLED);
    rectangle(framed, Point(thickness / 2, thickness / 2), Point(thickness / 2 + cornerThickness, thickness / 2 + cornerSize), cornerColor, FILLED);

    // top-right
    rectangle(framed, Point(w - thickness / 2 - cornerSize, thickness / 2), Point(w - thickness / 2, thickness / 2 + cornerThickness), cornerColor, FILLED);
    rectangle(framed, Point(w - thickness / 2 - cornerThickness, thickness / 2), Point(w - thickness / 2, thickness / 2 + cornerSize), cornerColor, FILLED);

    // bottom-left
    rectangle(framed, Point(thickness / 2, h - thickness / 2 - cornerThickness), Point(thickness / 2 + cornerSize, h - thickness / 2), cornerColor, FILLED);
    rectangle(framed, Point(thickness / 2, h - thickness / 2 - cornerSize), Point(thickness / 2 + cornerThickness, h - thickness / 2), cornerColor, FILLED);

    // bottom-right
    rectangle(framed, Point(w - thickness / 2 - cornerSize, h - thickness / 2 - cornerThickness), Point(w - thickness / 2, h - thickness / 2), cornerColor, FILLED);
    rectangle(framed, Point(w - thickness / 2 - cornerThickness, h - thickness / 2 - cornerSize), Point(w - thickness / 2, h - thickness / 2), cornerColor, FILLED);

    return framed;
}

int main(int argc, char** argv) {
    if (argc < 8) {
        cout << "Usage: " << argv[0] << " input.jpg output.jpg style thickness padding B G R\n";
        cout << "styles: solid | double | corner\n";
        return 1;
    }

    string inputPath = argv[1];
    string outputPath = argv[2];
    string style = argv[3];
    int thickness = stoi(argv[4]); // frame thickness in pixels
    int padding = stoi(argv[5]); // inner padding between image and frame
    int b = stoi(argv[6]);
    int g = stoi(argv[7]);
    int r = stoi(argv[8]);
    Scalar frameColor(b, g, r); // BGR

    Mat img = imread(inputPath, IMREAD_UNCHANGED);
    if (img.empty()) {
        cerr << "Error: couldn't open image: " << inputPath << endl;
        return 2;
    }

    Mat result;
    if (style == "solid") {
        result = addSolidFrame(img, thickness, padding, frameColor);
    }
    else if (style == "double") {
        // choose an inner contrasting color automatically (or you can pass it)
        Scalar innerColor = Scalar(255 - b, 255 - g, 255 - r); // simple contrast
        result = addDoubleFrame(img, thickness, padding, frameColor, innerColor, max(4, thickness / 4));
    }
    else if (style == "corner") {
        result = addCornerFrame(img, thickness, padding, frameColor, max(20, thickness * 2), max(2, thickness / 5));
    }
    else {
        cerr << "Unknown style: " << style << endl;
        return 3;
    }

    // Save result
    if (!imwrite(outputPath, result)) {
        cerr << "Failed to write: " << outputPath << endl;
        return 4;
    }

    cout << "Saved framed image to: " << outputPath << endl;
    return 0;
}

 
// filter 12

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;


Mat applyBlur(const Mat& img, int level) {
    Mat blurred;

    int kernelSize = level * 2 + 1;

    blur(img, blurred, Size(kernelSize, kernelSize));

    return blurred;
}

int main() {
    Mat image = imread("input.jpg");

    if (image.empty()) {
        cout << "image not found!" << endl;
        return -1;
    }

    int level;
    cout << "enter pixel level(1 to 10): ";
    cin >> level;

    if (level < 1) level = 1;
    if (level > 10) level = 10;

    Mat blurred = applyBlur(image, level);

    imshow("اmain image", image);
    imshow("اblured image", blurred);

    imwrite("blurred_output.jpg", blurred);

    waitKey(0);
    return 0;
}

// filter 15

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat oldTVEffect(const Mat& img) {
    Mat tvImage = img.clone();

    for (int y = 0; y < tvImage.rows; y += 2) {
        for (int x = 0; x < tvImage.cols; x++) {
            Vec3b& pixel = tvImage.at<Vec3b>(y, x);
            // decrease brightness
            pixel[0] = saturate_cast<uchar>(pixel[0] * 0.7);
            pixel[1] = saturate_cast<uchar>(pixel[1] * 0.7);
            pixel[2] = saturate_cast<uchar>(pixel[2] * 0.7);
        }
    }

    Mat noise(tvImage.size(), tvImage.type());
    randn(noise, 0, 15);
    tvImage += noise;

    Mat hsv;
    cvtColor(tvImage, hsv, COLOR_BGR2HSV);
    for (int y = 0; y < hsv.rows; y++) {
        for (int x = 0; x < hsv.cols; x++) {
            Vec3b& pixel = hsv.at<Vec3b>(y, x);
            pixel[1] = saturate_cast<uchar>(pixel[1] * 0.7);
        }
    }
    cvtColor(hsv, tvImage, COLOR_HSV2BGR);

    return tvImage;
}

int main() {

    Mat image = imread("input.jpg");
    if (image.empty()) {
        cout << "no image found!" << endl;
        return -1;
    }

    Mat tvEffect = oldTVEffect(image);

    imshow("main image", image);
    imshow("otveffected", tvEffect);

    // saving image
    imwrite("old_tv_output.jpg", tvEffect);

    waitKey(0);
    return 0;
}