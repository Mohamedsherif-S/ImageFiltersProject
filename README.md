# 🖼️ Image Filters Application

<div align="center">

[![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://en.cppreference.com/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![FCAI](https://img.shields.io/badge/From-FCAI%20Cairo%20University-red.svg)](https://fcai.cu.edu.eg/)

**A professional image processing application with 17+ filters for image manipulation**

</div>

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Installation](#-installation)
- [Usage](#-usage)
- [Filters Explained](#-filters-explained)
- [Project Structure](#-project-structure)
- [Contributors](#-contributors)
- [License](#-license)

---

## 🎯 Overview

This is a **comprehensive image processing application** developed at FCAI Cairo University. It allows users to load images, apply various professional filters, and save the results in multiple formats (PNG, BMP, JPG, TGA).

### Key Features:
- ✅ Load images from multiple formats
- ✅ Apply 17+ different filters
- ✅ Real-time image manipulation
- ✅ Save in multiple output formats
- ✅ User-friendly CLI interface

---

## ✨ Features

### Supported Image Formats
| Format | Load | Save |
|--------|------|------|
| PNG | ✅ | ✅ |
| BMP | ✅ | ✅ |
| JPG/JPEG | ✅ | ✅ |
| TGA | ✅ | ✅ |

### Available Filters

#### Color & Tone Filters
- 🔲 **Grayscale** - Convert to black and white
- ⬜ **Black & White** - High contrast threshold
- 🔄 **Invert Colors** - Reverse all colors
- ☀️ **Wano Sunlight Fix** - Enhance bright areas
- 🌓 **Lighten/Darken** - Adjust brightness by percentage

#### Geometric Filters
- ↔️ **Flip Image** - Horizontal or vertical flip
- 🔁 **Rotate Image** - 90°, 180°, 270° rotation
- ✂️ **Crop Image** - Extract image regions
- 📐 **Resize Image** - Scale to new dimensions

#### Artistic Filters
- 🎨 **Oil Painting** - Create painterly effect
- 🖼️ **Add Frame** - Decorate image borders
- 🌀 **Blur Image** - Smooth image details
- 📺 **Old TV Effect** - Add retro noise

#### Advanced Filters
- 🔍 **Edge Detection** - Detect image boundaries
- 🔗 **Merge Images** - Combine two images
- 📷 **Custom Filters** - Easy to add new ones

---

## 🚀 Installation

### Prerequisites
- **C++ Compiler** (GCC, Clang, or MSVC)
- **CMake** (recommended) or direct compilation
- **Standard C++ Library** (C++11 or later)

### Setup Steps

#### 1️⃣ Clone the Repository
```bash
git clone https://github.com/Mohamedsherif-S/ImageFiltersProject.git
cd ImageFiltersProject
```

#### 2️⃣ Compile the Project

**Option A: Using g++/clang**
```bash
g++ -std=c++11 Filters.cpp -o image_filters -lm
```

**Option B: Using Visual Studio**
- Open `ImageFiltersProject.sln`
- Build → Build Solution (Ctrl+Shift+B)

**Option C: Using CMake**
```bash
mkdir build
cd build
cmake ..
make
```

#### 3️⃣ Run the Application
```bash
./image_filters
```

---

## 📖 Usage

### Basic Workflow

```
1. Launch the application
2. Enter image filename to load
3. Choose a filter from the menu
4. Follow on-screen prompts
5. Save the result when done
```

### Example Session

```
$ ./image_filters
Enter image file to load: photo.jpg

============== IMAGE MENU ==============
1 - Load new image
2 - Grayscale
3 - Black & White
4 - Invert Colors
...
17 - Save Image
0 - Exit
========================================
Enter choice: 2

[Image processed with Grayscale filter]

Enter choice: 17
Enter output file name: photo_gray.png
Image saved successfully!
```

### Menu Overview

```
────────────────────────────────────────
          MAIN MENU OPTIONS
────────────────────────────────────────
1  → Load new image
2  → Grayscale conversion
3  → Black & White threshold
4  → Invert colors
5  → Merge two images
6  → Flip (H/V)
7  → Rotate (90°/180°/270°)
8  → Crop region
9  → Resize image
10 → Oil painting effect
11 → Add decorative frame
12 → Edge detection
13 → Wano sunlight fix
14 → Blur filter
15 → Old TV effect
16 → Lighten/Darken
17 → Save image
0  → Exit program
────────────────────────────────────────
```

---

## 🎨 Filters Explained

### 1. Grayscale Filter
Converts RGB image to grayscale using average method.
```
Original: (R=255, G=100, B=50) 
Result:   (135, 135, 135)
```

### 2. Black & White Filter
Creates high-contrast B&W using threshold of 127.
```
If average > 127 → White (255)
Else             → Black (0)
```

### 3. Invert Colors
Reverses color values: new_value = 255 - old_value
```
Original: (R=255, G=100, B=50)
Result:   (R=0, G=155, B=205)
```

### 4. Flip Image
- **Horizontal**: Mirror left-right
- **Vertical**: Mirror top-bottom

### 5. Rotate Image
- **90°**: Clockwise rotation
- **180°**: Full rotation
- **270°**: Counter-clockwise

### 6. Merge Images
Combines two images:
- **Option 1**: Resize to larger dimensions
- **Option 2**: Use common overlapping area

### 7. Oil Painting
Applies 5-pixel weighted averaging for artistic effect.

### 8. Edge Detection
Identifies pixel boundaries using difference calculation.

### 9. Lighten/Darken
Adjusts brightness by percentage (0-100%).

### 10. Wano Sunlight Fix
Enhances bright areas with selective channel boosting:
- Red: +50%
- Green: +33%
- Blue: +17%

### 11. Blur Filter
Applies weighted Gaussian-like blur 3 times.

### 12. Frame Filter
Adds decorative 10-pixel borders (blue or patterned).

### 13. Old TV Effect
Adds random noise for vintage look.

### 14. Crop Image
Extracts rectangular region from image.

### 15. Resize Image
Scales to new dimensions using nearest-neighbor.

---

## 🏗️ Project Structure

```
ImageFiltersProject/
│
├── 📄 Image_Class.h              # Main image class
├── 📄 stb_image.h                # Image loading library
├── 📄 stb_image_write.h          # Image saving library
├── 📄 Filters.cpp                # Main program with all filters
├── 📄 README.md                  # This file
├── 📄 .gitignore                 # Git ignore rules
└── 📁 test_images/               # Sample images for testing
    ├── sample1.jpg
    ├── sample2.png
    └── sample3.bmp
```

### Key Components

#### Image_Class.h
- **Image loading** from PNG, BMP, JPG, TGA
- **Pixel access** via `operator()`
- **Memory management** with RAII
- **Image saving** in multiple formats

```cpp
// Example usage
Image img("photo.jpg");
img(x, y, 0) = 255;  // Set red channel
img.saveImage("output.png");
```

#### stb_image & stb_image_write
- External libraries for image I/O
- Single-header implementation
- Minimal dependencies

---

## 👥 Contributors

| Name | ID | Contribution | Section |
|------|-------|--------------|---------|
| **Mohamed Sherif Ahmed** | 20240501 | B&W, Flip, Crop, Resize, Oil Painting | X |
| **Hazem Hussein Ahmed** | 20240151 | Grayscale, Merge, Lighten/Darken, Edge Detection, Wano | X |
| **Gasser Ahmed Said** | 20210101 | Invert, Rotate, Frame, Blur, Old TV | X |

---

## 🔧 Technical Details

### Architecture
- **Object-Oriented Design** with Image class
- **Modular Filters** - Each filter is independent function
- **Exception Handling** for robust error management
- **Memory-Safe** pixel access with bounds checking

### Performance
- Direct pixel manipulation for speed
- Efficient memory management
- Minimal allocations per filter

### Image Format Support
- **PNG**: Lossless compression
- **BMP**: Uncompressed bitmap
- **JPG**: Lossy compression (quality: 90)
- **TGA**: Truevision format

---

## 📝 Code Examples

### Loading and Processing
```cpp
#include "Image_Class.h"

int main() {
    // Load image
    Image img("input.jpg");
    
    // Apply filter
    applyGrayscale(img);
    
    // Save result
    img.saveImage("output.png");
    
    return 0;
}
```

### Creating New Filter
```cpp
void applyCustomFilter(Image& img) {
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            // Process each pixel
            int r = img(x, y, 0);
            int g = img(x, y, 1);
            int b = img(x, y, 2);
            
            // Apply transformation
            img(x, y, 0) = r / 2;  // Modify red channel
        }
    }
}
```

### Pixel Access Safety
```cpp
try {
    unsigned char red = img(100, 50, 0);  // Safe access
    img(x, y, 2) = 128;
} catch (std::out_of_range& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

---

## 🐛 Known Issues & Fixes

### Issue 1: Boundary Check Bug ✅ FIXED
**Problem**: Condition was `x > width` instead of `x >= width`
**Solution**: Fixed boundary checks in `getPixel()` function

### Issue 2: Memory Leak ✅ FIXED
**Problem**: Assignment operator didn't properly free old memory
**Solution**: Added proper cleanup in `operator=`

### Issue 3: Channel Mismatch ✅ FIXED
**Problem**: Channels sometimes not set to 3
**Solution**: Force `channels = 3` after loading

---

## 🔍 Testing Checklist

- [x] Load PNG image
- [x] Load BMP image
- [x] Load JPG image
- [x] Apply Grayscale
- [x] Apply Invert
- [x] Save in different formats
- [x] Boundary condition handling
- [x] Memory management (no leaks)
- [x] Filter chaining
- [x] Large image support

---

## 📚 Dependencies

```
STB Libraries (included):
├── stb_image.h      (v2.29) - Image loading
└── stb_image_write.h (v1.16) - Image writing

Standard Libraries:
├── iostream         - Console I/O
├── fstream          - File I/O
├── cmath            - Math functions
├── cstdlib          - Utilities
├── algorithm        - min/max
└── ctime            - Random seed
```

---

## 🚦 Compilation Flags

```bash
# Debug mode with assertions
g++ -std=c++11 -g -O0 Filters.cpp -o image_filters

# Release mode with optimization
g++ -std=c++11 -O3 Filters.cpp -o image_filters -lm

# With address sanitizer
g++ -std=c++11 -fsanitize=address Filters.cpp -o image_filters
```

---

## 📜 License

This project is licensed under the **MIT License** - see LICENSE file for details.

```
MIT License

Copyright (c) 2024 FCAI Cairo University

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
...
```

---

## 🔗 Links & Resources

- **GitHub Repository**: [ImageFiltersProject](https://github.com/Mohamedsherif-S/ImageFiltersProject)
- **Google Drive**: [Project Files](https://drive.google.com/drive/folders/1ky2Yq2Bpc0_RXPH76hjX7gtXnoaiTy_z?usp=sharing)
- **FCAI Website**: [Faculty of Computers](https://fcai.cu.edu.eg/)
- **STB Libraries**: [nothings.org/stb](https://nothings.org/stb)

---

## 💡 Tips & Tricks

### Combining Filters
1. Apply Grayscale first
2. Then Edge Detection for nice effect
3. Finally add Frame for decoration

### Large Images
- Resize first for faster processing
- Use Blur cautiously (slow on large images)
- JPG compression helps with storage

### Best Practices
- Always keep original image backup
- Test filters on small images first
- Use PNG for lossless output

---

## 📞 Support

For issues or questions:
1. Check existing GitHub issues
2. Review the documentation
3. Contact contributors
4. Email:mohamedsherifggi@gmail.com

---

## 🎓 Educational Value

This project demonstrates:
- ✅ Object-oriented C++ design
- ✅ Image processing algorithms
- ✅ File I/O operations
- ✅ Memory management
- ✅ Exception handling
- ✅ Algorithm optimization
- ✅ Team collaboration

---

<div align="center">

**Made with ❤️ at FCAI Cairo University**

[![Stars](https://img.shields.io/github/stars/Mohamedsherif-S/ImageFiltersProject?style=social)](https://github.com/Mohamedsherif-S/ImageFiltersProject)
[![Forks](https://img.shields.io/github/forks/Mohamedsherif-S/ImageFiltersProject?style=social)](https://github.com/Mohamedsherif-S/ImageFiltersProject)
[![Issues](https://img.shields.io/github/issues/Mohamedsherif-S/ImageFiltersProject)](https://github.com/Mohamedsherif-S/ImageFiltersProject/issues)

</div>

---

