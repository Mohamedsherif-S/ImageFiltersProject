#include <iostream>
#include <cmath>
#include <cstdlib>
#include "image.h"
using namespace std;

// ======================== BLUR FILTER ==========================
Image applyBlur(const Image& img, int level) {
    Image result(img.width, img.height);
    int radius = level; // blur radius

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int ky = -radius; ky <= radius; ky++) {
                for (int kx = -radius; kx <= radius; kx++) {
                    int nx = x + kx;
                    int ny = y + ky;
                    if (nx >= 0 && nx < img.width && ny >= 0 && ny < img.height) {
                        sumR += img.getPixel(nx, ny, 0);
                        sumG += img.getPixel(nx, ny, 1);
                        sumB += img.getPixel(nx, ny, 2);
                        count++;
                    }
                }
            }

            result.setPixel(x, y, 0, sumR / count);
            result.setPixel(x, y, 1, sumG / count);
            result.setPixel(x, y, 2, sumB / count);
        }
    }
    return result;
}

// ======================== FRAME FILTER ==========================
Image addFrame(const Image& img, int thickness, int r, int g, int b) {
    int newW = img.width + 2 * thickness;
    int newH = img.height + 2 * thickness;
    Image framed(newW, newH);

    for (int y = 0; y < newH; y++) {
        for (int x = 0; x < newW; x++) {
            if (x < thickness || x >= img.width + thickness ||
                y < thickness || y >= img.height + thickness) {
                framed.setPixel(x, y, 0, r);
                framed.setPixel(x, y, 1, g);
                framed.setPixel(x, y, 2, b);
            }
            else {
                for (int c = 0; c < 3; c++) {
                    framed.setPixel(x, y, c, img.getPixel(x - thickness, y - thickness, c));
                }
            }
        }
    }
    return framed;
}

// ======================== OLD TV EFFECT ==========================
Image oldTVEffect(const Image& img) {
    Image result = img;

    // dec brightness
    for (int y = 0; y < result.height; y += 2) {
        for (int x = 0; x < result.width; x++) {
            for (int c = 0; c < 3; c++) {
                unsigned char val = result.getPixel(x, y, c);
                result.setPixel(x, y, c, static_cast<unsigned char>(val * 0.7));
            }
        }
    }

    // add noise
    for (int y = 0; y < result.height; y++) {
        for (int x = 0; x < result.width; x++) {
            int noise = rand() % 30 - 15; // noise range -15 to +15
            for (int c = 0; c < 3; c++) {
                int val = result.getPixel(x, y, c) + noise;
                if (val < 0) val = 0;
                if (val > 255) val = 255;
                result.setPixel(x, y, c, static_cast<unsigned char>(val));
            }
        }
    }

    // decrease saturation
    for (int y = 0; y < result.height; y++) {
        for (int x = 0; x < result.width; x++) {
            int r = result.getPixel(x, y, 0);
            int g = result.getPixel(x, y, 1);
            int b = result.getPixel(x, y, 2);
            r = static_cast<int>(r * 0.9);
            g = static_cast<int>(g * 0.9);
            b = static_cast<int>(b * 0.8);
            result.setPixel(x, y, 0, r);
            result.setPixel(x, y, 1, g);
            result.setPixel(x, y, 2, b);
        }
    }

    return result;
}

// ======================== MAIN PROGRAM ==========================
int main() {
    string inputFile;
    cout << "Enter input image filename (e.g. input.jpg): ";
    cin >> inputFile;

    Image img(inputFile);

    cout << "\nChoose filter:\n";
    cout << "1 - Blur Filter\n";
    cout << "2 - Frame Filter\n";
    cout << "3 - Old TV Effect\n";
    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        int level;
        cout << "Enter blur level (1-10): ";
        cin >> level;
        if (level < 1) level = 1;
        if (level > 10) level = 10;

        Image blurred = applyBlur(img, level);
        blurred.saveImage("blur_output.jpg");
        cout << " Saved as blur_output.jpg\n";
    }

    else if (choice == 2) {
        int thickness, r, g, b;
        cout << "Enter frame thickness (e.g. 10): ";
        cin >> thickness;
        cout << "Enter frame color (R G B): ";
        cin >> r >> g >> b;

        Image framed = addFrame(img, thickness, r, g, b);
        framed.saveImage("frame_output.jpg");
        cout << " Saved as frame_output.jpg\n";
    }

    else if (choice == 3) {
        Image tv = oldTVEffect(img);
        tv.saveImage("oldtv_output.jpg");
        cout << " Saved as oldtv_output.jpg\n";
    }

    else {
        cout << "Invalid choice!\n";
    }

    return 0;
}