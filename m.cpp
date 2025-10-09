#include <iostream>
#include <fstream>
#include "Image_Class.h"
#include <windows.h>
using namespace std;

bool validExtension(string fileName) {
    int pos = fileName.find_last_of('.');
    string end = fileName.substr(pos + 1);
    if (end == "jpg" || end == "JPG" || end == "bmp" || end == "BMP" || end == "png" || end == "PNG")
        return true;
    return false;
}

bool fileExists(string fileName) {
    ifstream myFile(fileName.c_str());
    return myFile.good();
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
        cout << "2 - Grayscale\n";
        cout << "3 - Black & White\n";
        cout << "4 - Invert Colors\n";
        cout << "5 - Merge Two Images\n";
        cout << "6 - Flip Image\n";
        cout << "7 - Rotate Image\n";
        cout << "8 - Crop Image\n";
        cout << "9 - Resize Image\n";
        cout << "10 - Oil Painting\n";
        cout << "11 - Save Image\n";
        cout << "0 - Exit\n";
        cout << "===========================================\n";
        cout << "Enter choice: ";

        int f;
        cin >> f;

        if (f == 0) {
            char save;
            cout << "Do you want to save before exit? (y/n): ";
            cin >> save;
            if (save == 'y' || save == 'Y') {
                string out;
                cout << "Enter output file name: ";
                cin >> out;
                if (validExtension(out)) currentImage.saveImage(out);
            }
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
            cout << "Applied Grayscale filter.\n";
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
            cout << "Applied Black and White filter.\n";
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
            cout << "Applied Merge filter.\n";
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

        else if (f == 8) {
            int x, y, w, h;
            cout << "Enter starting X and Y: ";
            cin >> x >> y;
            cout << "Enter width and height to crop: ";
            cin >> w >> h;
            if (x + w > currentImage.width || y + h > currentImage.height) {
                cout << "Invalid crop size!\n";
            }
            else {
                Image out(w, h);
                for (int i = 0; i < w; i++)
                    for (int j = 0; j < h; j++)
                        for (int c = 0; c < 3; c++)
                            out(i, j, c) = currentImage(x + i, y + j, c);
                currentImage = out;
                cout << "Applied Crop filter.\n";
            }
        }

        else if (f == 9) {
            int newW, newH;
            cout << "Enter new width: ";
            cin >> newW;
            cout << "Enter new height: ";
            cin >> newH;
            if (newW <= 0 || newH <= 0) cout << "Invalid dimensions!\n";
            else {
                Image out(newW, newH);
                for (int y = 0; y < newH; y++)
                    for (int x = 0; x < newW; x++) {
                        int oldX = x * currentImage.width / newW;
                        int oldY = y * currentImage.height / newH;
                        for (int c = 0; c < 3; c++)
                            out(x, y, c) = currentImage(oldX, oldY, c);
                    }
                currentImage = out;
                cout << "Applied Resize filter.\n";
            }
        }

        else if (f == 10) {
            Image out(currentImage.width, currentImage.height);
            for (int y = 1; y < currentImage.height - 1; y++)
                for (int x = 1; x < currentImage.width - 1; x++)
                    for (int c = 0; c < 3; c++) {
                        int avg = (
                            currentImage(x, y, c) +
                            currentImage(x + 1, y, c) +
                            currentImage(x - 1, y, c) +
                            currentImage(x, y + 1, c) +
                            currentImage(x, y - 1, c)
                            ) / 5;
                        out(x, y, c) = avg;
                    }
            currentImage = out;
            cout << "Applied Oil Painting filter.\n";
        }

        else if (f == 11) {
            string out;
            cout << "Enter output file name: ";
            cin >> out;
            if (validExtension(out)) currentImage.saveImage(out);
            else cout << "Invalid extension!\n";
        }

        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
