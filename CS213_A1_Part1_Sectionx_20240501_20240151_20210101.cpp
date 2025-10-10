/*
Project: Image Filters Program

File: CS213_A1_Part1_Sectionx_20240501_20240151_20210101.cpp

 Description:
        This program allows the user to load an image and apply
        different filters. The user can:
          1. Load a new image
          2. Apply filters (Gray, Threshold, Invert, Merge, Flip, Rotate , ....etc)
          3. Save the current image
          4. Exit (with save option)

students name :
1 - Mohamed sherif ahmed / 20240501 / B&W & Flip Image & Crop Images & Resizing Images & Oil painting / section x
2 - hazem hussen ahmed / 20240151 / grayscale & Merge Images & Darken and Lighten &  Detect Image Edges & sunlight fix / section x
3 - gasser ahmed said / 20210101 / Invert Colors & Rotate Image & Adding a Frame & Blur Images & TV images / section x

repo link : https://github.com/Mohamedsherif-S/ImageFiltersProject.git
drive link: https://drive.google.com/drive/folders/1ky2Yq2Bpc0_RXPH76hjX7gtXnoaiTy_z?usp=sharing
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "Image_Class.h"
using namespace std;

bool validExtension(string fileName) {
    int pos = fileName.find_last_of('.');
    string end = fileName.substr(pos + 1);
    if (end == "jpg" || end == "JPG" || end == "jpeg" || end == "JPEG") return true;
    if (end == "bmp" || end == "BMP") return true;
    if (end == "png" || end == "PNG") return true;
    return false;
}

bool fileExists(string fileName) {
    ifstream myFile(fileName.c_str());
    return myFile.good();
}

void applyGrayscale(Image& img) {
    for (int x = 0; x < img.width; x++)
        for (int y = 0; y < img.height; y++) {
            int avg = (img(x, y, 0) + img(x, y, 1) + img(x, y, 2)) / 3;
            for (int c = 0; c < 3; c++)
                img(x, y, c) = avg;
        }
}

void applyBlackWhite(Image& img) {
    for (int x = 0; x < img.width; x++)
        for (int y = 0; y < img.height; y++) {
            int avg = (img(x, y, 0) + img(x, y, 1) + img(x, y, 2)) / 3;
            unsigned char bw = (avg > 127) ? 255 : 0;
            for (int c = 0; c < 3; c++)
                img(x, y, c) = bw;
        }
}

void applyInvert(Image& img) {
    for (int x = 0; x < img.width; x++)
        for (int y = 0; y < img.height; y++)
            for (int c = 0; c < 3; c++)
                img(x, y, c) = 255 - img(x, y, c);
}

void applyMerge(Image& img1) {
    string name2;
    cout << "Enter second image name: ";
    cin >> name2;
    Image img2(name2);

    cout << "1- Resize smaller\n2- Merge common part\n";
    int n; cin >> n;

    int w, h;
    if (n == 1) {
        w = max(img1.width, img2.width);
        h = max(img1.height, img2.height);
    }
    else {
        w = min(img1.width, img2.width);
        h = min(img1.height, img2.height);
    }

    Image merged(w, h);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int x1 = x * img1.width / w;
            int y1 = y * img1.height / h;
            int x2 = x * img2.width / w;
            int y2 = y * img2.height / h;

            for (int c = 0; c < 3; c++)
                merged(x, y, c) = (img1(x1, y1, c) + img2(x2, y2, c)) / 2;
        }
    }

    img1 = merged;
    cout << "Images merged!\n";
}



void applyFlip(Image& img) {
    int w = img.width, h = img.height;
    int choice;
    cout << "Flip type? 1=Horizontal 2=Vertical: ";
    cin >> choice;
    Image out(w, h);
    if (choice == 1) {
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
                for (int c = 0; c < 3; c++)
                    out(w - 1 - x, y, c) = img(x, y, c);
    }
    else {
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
                for (int c = 0; c < 3; c++)
                    out(x, h - 1 - y, c) = img(x, y, c);
    }
    img = out;
}

void applyRotate(Image& img) {
    int w = img.width, h = img.height;
    cout << "Rotate: 1=90 2=180 3=270: ";
    int ch;
    cin >> ch;
    int newW = (ch == 1 || ch == 3) ? h : w;
    int newH = (ch == 1 || ch == 3) ? w : h;
    Image out(newW, newH);
    if (ch == 1) {
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
                for (int c = 0; c < 3; c++)
                    out(h - 1 - y, x, c) = img(x, y, c);
    }
    else if (ch == 2) {
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
                for (int c = 0; c < 3; c++)
                    out(w - 1 - x, h - 1 - y, c) = img(x, y, c);
    }
    else {
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
                for (int c = 0; c < 3; c++)
                    out(y, w - 1 - x, c) = img(x, y, c);
    }
    img = out;
}

void applyCrop(Image& img) {
    int x, y, w, h;
    cout << "Enter starting X and Y: ";
    cin >> x >> y;
    cout << "Enter width and height to crop: ";
    cin >> w >> h;
    if (x + w > img.width || y + h > img.height) return;
    Image out(w, h);
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            for (int c = 0; c < 3; c++)
                out(i, j, c) = img(x + i, y + j, c);
    img = out;
}

void applyResize(Image& img) {
    int newW, newH;
    cout << "Enter new width: ";
    cin >> newW;
    cout << "Enter new height: ";
    cin >> newH;
    Image out(newW, newH);
    for (int y = 0; y < newH; y++)
        for (int x = 0; x < newW; x++) {
            int oldX = x * img.width / newW;
            int oldY = y * img.height / newH;
            for (int c = 0; c < 3; c++)
                out(x, y, c) = img(oldX, oldY, c);
        }
    img = out;
}

void applyOil(Image& img) {
    Image out(img.width, img.height);
    for (int y = 1; y < img.height - 1; y++)
        for (int x = 1; x < img.width - 1; x++)
            for (int c = 0; c < 3; c++)
                out(x, y, c) = (img(x, y, c) + img(x + 1, y, c) + img(x - 1, y, c) + img(x, y + 1, c) + img(x, y - 1, c)) / 5;
    img = out;
}

void applyFrame(Image& img) {
    int thickness = 10;
    char choice;
    cout << "Do you want a decorated frame? (y/n): ";
    cin >> choice;

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            bool inFrame = (x < thickness || y < thickness ||
                            x >= img.width - thickness || y >= img.height - thickness);

            if (inFrame) {
                if (choice == 'y' || choice == 'Y') {

                    if ((x / 5 + y / 5) % 2 == 0) { img(x, y, 0) = 255;
                        img(x, y, 1) = 215;
                        img(x, y, 2) = 0;
                    } else {img(x, y, 0) = 139;
                        img(x, y, 1) = 69;
                        img(x, y, 2) = 19;
                    }
                } else {img(x, y, 0) = 0;
                    img(x, y, 1) = 0;
                    img(x, y, 2) = 255;
                }
            }
        }
    }
}

void applyEdge(Image& img) {
    Image out(img.width, img.height);
    for (int y = 0; y < img.height - 1; y++)
        for (int x = 0; x < img.width - 1; x++) {
            int diff = abs(img(x, y, 0) - img(x + 1, y, 0)) + abs(img(x, y, 0) - img(x, y + 1, 0));
            unsigned char edge = (diff > 50) ? 0 : 255;
            for (int c = 0; c < 3; c++) out(x, y, c) = edge;
        }
    img = out;
}


void applyWano(Image& img) {
    for (int y = 0; y < img.height; y++)
        for (int x = 0; x < img.width; x++) {
            img(x, y, 0) = min(255, img(x, y, 0) + (255 - img(x, y, 0)) / 2);
            img(x, y, 1) = min(255, img(x, y, 1) + (255 - img(x, y, 1)) / 3);
            img(x, y, 2) = min(255, img(x, y, 2) + (255 - img(x, y, 2)) / 6);
        }
}
void applyBlur(Image& img) {
    Image out(img.width, img.height);
    for (int repeat = 0; repeat < 3; repeat++) {

        for (int y = 3; y < img.height - 3; y++)
            for (int x = 3; x < img.width - 3; x++)
                for (int c = 0; c < 3; c++) {
                    int sum = 0;
                    for (int j = -3; j <= 3; j++)
                        for (int i = -3; i <= 3; i++) {
                            int weight = (i == 0 && j == 0) ? 5 : (abs(i) + abs(j) == 1 ? 3 : 1);
                            sum += img(x + i, y + j, c) * weight;
                        }
                    out(x, y, c) = sum / 65;
                }
        img = out;
    }
}



void applyOldTV(Image& img) {
    srand(time(0));
    for (int y = 0; y < img.height; y++)
        for (int x = 0; x < img.width; x++)
            for (int c = 0; c < 3; c++) {
                int noise = rand() % 100 - 50;
                int val = img(x, y, c) + noise;
                if (val < 0) val = 0;
                if (val > 255) val = 255;
                img(x, y, c) = val;
            }
}

void applyLightDark(Image& img) {
    int ch;
    double percent;
    cout << "1 - Lighten image\n2 - Darken image\nChoose: ";
    cin >> ch;
    cout << "Enter level (0-100%): ";
    cin >> percent;
    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;

    int amount;
    for (int x = 0; x < img.width; x++)
        for (int y = 0; y < img.height; y++)
            for (int c = 0; c < 3; c++) {

                if (ch == 1)
                    amount = ((255 - img(x, y, c)) * percent) / 100;
                else
                    amount = (img(x, y, c) * percent) / 100;
                img(x, y, c) = img(x, y, c) + ((ch == 1) ? amount : -amount);
            }
}

void saveImage(Image& img) {
    string out;
    cout << "Enter output file name: ";
    cin >> out;
    if (validExtension(out)) img.saveImage(out);
    else cout << "Invalid extension!\n";
}

int main() {
    srand(time(0));
    string filename;
    cout << "Enter image file to load: ";
    cin >> filename;
    while (!fileExists(filename) || !validExtension(filename)) {
        cout << "Invalid file or extension. Try again: ";
        cin >> filename;
    }
    Image currentImage(filename);
    bool running = true;
    while (running) {
        cout << "\n============== IMAGE MENU ==============\n";
        cout << "1 - Load new image\n";
        cout << "2 - Grayscale\n";
        cout << "3 - Black & White\n";
        cout << "4 - Invert Colors\n";
        cout << "5 - Merge Two Images\n";
        cout << "6 - Flip Image\n";
        cout << "7 - Rotate Image\n";
        cout << "8 - Crop Image\n";
        cout << "9 - Resize Image\n";
        cout << "10 - Oil Painting\n";
        cout << "11 - Add Frame\n";
        cout << "12 - Edge Detection\n";
        cout << "13 - Wano Sunlight Fix\n";
        cout << "14 - Blur Image\n";
        cout << "15 - Old TV Effect\n";
        cout << "16 - Lighten / Darken Image\n";
        cout << "17 - Save Image\n";
        cout << "0 - Exit\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        int f; cin >> f;

        if (f == 0) {
            char s;
            cout << "Do you want to save before exit? (y/n): ";
            cin >> s;
            if (s == 'y' || s == 'Y') saveImage(currentImage);
            running = false;
        }
        else if (f == 1) {
            cout << "Enter new image file: ";
            cin >> filename;
            while (!fileExists(filename) || !validExtension(filename)) {
                cout << "Invalid file or extension. Try again: ";
                cin >> filename;
            }
            currentImage = Image(filename);
        }
        else if (f == 2) applyGrayscale(currentImage);
        else if (f == 3) applyBlackWhite(currentImage);
        else if (f == 4) applyInvert(currentImage);
        else if (f == 5) applyMerge(currentImage);
        else if (f == 6) applyFlip(currentImage);
        else if (f == 7) applyRotate(currentImage);
        else if (f == 8) applyCrop(currentImage);
        else if (f == 9) applyResize(currentImage);
        else if (f == 10) applyOil(currentImage);
        else if (f == 11) applyFrame(currentImage);
        else if (f == 12) applyEdge(currentImage);
        else if (f == 13) applyWano(currentImage);
        else if (f == 14) applyBlur(currentImage);
        else if (f == 15) applyOldTV(currentImage);
        else if (f == 16) applyLightDark(currentImage);
        else if (f == 17) saveImage(currentImage);
        else cout << "Invalid choice!\n";
    }
    return 0;
}
