
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

                    if ((x / 5 + y / 5) % 2 == 0) {

                        img(x, y, 0) = 255;
                        img(x, y, 1) = 215;
                        img(x, y, 2) = 0;
                    }
                    else {

                        img(x, y, 0) = 139;
                        img(x, y, 1) = 69;
                        img(x, y, 2) = 19;
                    }
                }
                else {

                    img(x, y, 0) = 0;
                    img(x, y, 1) = 0;
                    img(x, y, 2) = 255;
                }
            }
        }
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
        cout << "2 - Add Frame\n"; 
        cout << "3 - Blur Image\n";
        cout << "4 - Old TV Effect\n";
        cout << "5 - Save Image\n";
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
        else if (f == 2) applyFrame(currentImage);
        else if (f == 3) applyBlur(currentImage);
        else if (f == 4) applyOldTV(currentImage);
        else if (f == 5) saveImage(currentImage);
        else cout << "Invalid choice!\n";
    }
    return 0;
}