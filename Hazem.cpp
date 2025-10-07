#include <iostream>
#include <fstream>
#include "Image_Class.h"
#include <windows.h>
using namespace std;

bool validExtension(const string& name) {
    string ext = name.substr(name.find_last_of('.') + 1);
    for (auto& c : ext) c = tolower(c);
    return (ext == "jpg" || ext == "bmp" || ext == "png");
}

bool fileExists(const string& name) {
    ifstream f(name.c_str());
    return f.good();
}

int main() {
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
        cout << "\n================ IMAGE MENU ================\n";
        cout << "1 - Load new image\n";
        cout << "2 - Black & White (Gray)\n";
        cout << "3 - Pure Black & White (Threshold)\n";
        cout << "4 - Invert Colors\n";
        cout << "5 - Merge Two Images\n";
        cout << "6 - Flip Image\n";
        cout << "7 - Lighten/Darken Image\n";
        cout << "8 - Save Image\n";
        cout << "9 - Rotate Image\n";
        cout << "10 - Edge Detection\n";
        cout << "13 - Sunlight\n";
        cout << "0 - Exit\n";
        cout << "===========================================\n";
        cout << "Enter choice: ";

        int f;
        cin >> f;

        if (f == 0) {
            string out = "output.png";
            currentImage.saveImage(out);
            cout << "Image saved as " << out << ". Exiting...\n";
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
        else if (f == 2) {
            for (int x = 0; x < currentImage.width; x++)
                for (int y = 0; y < currentImage.height; y++) {
                    unsigned int avg = 0;
                    for (int c = 0; c < 3; c++) avg += currentImage(x, y, c);
                    avg /= 3;
                    for (int c = 0; c < 3; c++) currentImage(x, y, c) = avg;
                }
            cout << "Applied Gray filter.\n";
        }
        else if (f == 3) {
            for (int x = 0; x < currentImage.width; x++)
                for (int y = 0; y < currentImage.height; y++) {
                    unsigned int avg = 0;
                    for (int c = 0; c < 3; c++) avg += currentImage(x, y, c);
                    avg /= 3;
                    unsigned char bw = (avg > 127) ? 255 : 0;
                    for (int c = 0; c < 3; c++) currentImage(x, y, c) = bw;
                }
            cout << "Applied Threshold filter.\n";
        }
        else if (f == 4) {
            for (int x = 0; x < currentImage.width; x++)
                for (int y = 0; y < currentImage.height; y++)
                    for (int c = 0; c < 3; c++)
                        currentImage(x, y, c) = 255 - currentImage(x, y, c);
            cout << "Applied Invert filter.\n";
        }
        else if (f == 5) {
            string name2;
            cout << "Enter second image: ";
            cin >> name2;
            Image img2(name2);
            int w = min(currentImage.width, img2.width);
            int h = min(currentImage.height, img2.height);
            Image out(w, h);
            for (int y = 0; y < h; y++)
                for (int x = 0; x < w; x++)
                    for (int c = 0; c < 3; c++)
                        out(x, y, c) = (currentImage(x, y, c) + img2(x, y, c)) / 2;
            currentImage = out;
            currentImage.saveImage("merged.png");
            cout << "Merged image saved as merged.png.\n";
        }
        else if (f == 6) {
            int w = currentImage.width, h = currentImage.height;
            cout << "Flip type? 1=Horizontal 2=Vertical: ";
            int choice; cin >> choice;
            Image out(w, h);
            if (choice == 1) {
                for (int y = 0; y < h; y++)
                    for (int x = 0; x < w; x++)
                        for (int c = 0; c < 3; c++)
                            out(w - 1 - x, y, c) = currentImage(x, y, c);
            }
            else {
                for (int y = 0; y < h; y++)
                    for (int x = 0; x < w; x++)
                        for (int c = 0; c < 3; c++)
                            out(x, h - 1 - y, c) = currentImage(x, y, c);
            }
            currentImage = out;
            cout << "Applied Flip filter.\n";
        }
        else if (f == 7) {
            int ch;
            cout << "1 - Lighten image\n";
            cout << "2 - Darken image\n";
            cout << "Choose: ";
            cin >> ch;
            for (int x = 0; x < currentImage.width; x++)
                for (int y = 0; y < currentImage.height; y++)
                    for (int c = 0; c < 3; c++) {
                        if (ch == 1) {
                            int val = currentImage(x, y, c) + 50;
                            if (val > 255) val = 255;
                            currentImage(x, y, c) = val;
                        }
                        else if (ch == 2) {
                            int val = currentImage(x, y, c) - 50;
                            if (val < 0) val = 0;
                            currentImage(x, y, c) = val;
                        }
                    }
            if (ch == 1)
                cout << "Applied Lighten filter.\n";
            else
                cout << "Applied Darken filter.\n";
        }
        else if (f == 8) {
            string out;
            cout << "Enter output file name: ";
            cin >> out;
            if (validExtension(out)) {
                currentImage.saveImage(out);
                cout << "Image saved.\n";
            }
            else cout << "Invalid extension!\n";
        }
        else if (f == 9) {
            int w = currentImage.width, h = currentImage.height;
            cout << "Rotate: 1=90 2=180 3=270: ";
            int ch; cin >> ch;
            int newW = (ch == 1 || ch == 3) ? h : w;
            int newH = (ch == 1 || ch == 3) ? w : h;
            Image out(newW, newH);
            if (ch == 1) {
                for (int y = 0; y < h; y++)
                    for (int x = 0; x < w; x++)
                        for (int c = 0; c < 3; c++)
                            out(h - 1 - y, x, c) = currentImage(x, y, c);
            }
            else if (ch == 2) {
                for (int y = 0; y < h; y++)
                    for (int x = 0; x < w; x++)
                        for (int c = 0; c < 3; c++)
                            out(w - 1 - x, h - 1 - y, c) = currentImage(x, y, c);
            }
            else if (ch == 3) {
                for (int y = 0; y < h; y++)
                    for (int x = 0; x < w; x++)
                        for (int c = 0; c < 3; c++)
                            out(y, w - 1 - x, c) = currentImage(x, y, c);
            }
            currentImage = out;
            cout << "Applied Rotate filter.\n";
        }
        else if (f == 10) {
            Image out(currentImage.width, currentImage.height);
            for (int y = 0; y < currentImage.height - 1; y++)
                for (int x = 0; x < currentImage.width - 1; x++) {
                    int diff = abs(currentImage(x, y, 0) - currentImage(x + 1, y, 0))
                        + abs(currentImage(x, y, 0) - currentImage(x, y + 1, 0));
                    unsigned char edge = (diff > 50) ? 255 : 0;
                    for (int c = 0; c < 3; c++)
                        out(x, y, c) = edge;
                }
            currentImage = out;
            cout << "Applied Edge Detection filter.\n";
        }
        else if (f == 13) {
            for (int y = 0; y < currentImage.height; y++)
                for (int x = 0; x < currentImage.width; x++) {
                    currentImage(x, y, 0) = min(255, currentImage(x, y, 0) + 30);
                    currentImage(x, y, 1) = min(255, currentImage(x, y, 1) + 20);
                    currentImage(x, y, 2) = min(255, currentImage(x, y, 2) + 10);
                }
            cout << "Wano sunlight fixed!\n";
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
