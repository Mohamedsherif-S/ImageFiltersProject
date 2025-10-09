
void applyGrayscale(Image& img) {
    for (int x = 0; x < img.width; x++)
        for (int y = 0; y < img.height; y++) {
            int avg = (img(x, y, 0) + img(x, y, 1) + img(x, y, 2)) / 3;
            for (int c = 0; c < 3; c++)
                img(x, y, c) = avg;
        }
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
    } else {
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


