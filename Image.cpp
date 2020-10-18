// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Image.h"
#include "Matrix.h"
#include <ostream>

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
    assert(0 < width && width <= MAX_MATRIX_WIDTH);
    assert(0 < height && height <= MAX_MATRIX_HEIGHT);

    img->height = height;
    img->width = width;
    Matrix *redPtr = &img->red_channel;
    Matrix_init(redPtr, width, height);
    Matrix *greenPtr = &img->green_channel;
    Matrix_init(greenPtr, width, height);
    Matrix *bluePtr = &img->blue_channel;
    Matrix_init(bluePtr, width, height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {
    std::string type;
    is >> type;
    assert(type == "P3");
    int width;
    is >> width;
    img->width = width;
    int height;
    is >> height;
    img->height = height;
    int max;
    is >> max;
    assert(max <= 255);
    Matrix *redPtr = &img->red_channel;
    Matrix_init(redPtr, width, height);
    Matrix *greenPtr = &img->green_channel;
    Matrix_init(greenPtr, width, height);
    Matrix *bluePtr = &img->blue_channel;
    Matrix_init(bluePtr, width, height);
    int redCount = 0;
    int greenCount = 0;
    int blueCount = 0;
    for(int i = 0; i < width * height; i++){
        is >> redPtr->data[redCount];
        redCount++;
        is >> greenPtr->data[greenCount];
        greenCount++;
        is >> bluePtr->data[blueCount];
        blueCount++;
    }
}


// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
    os << "P3" << std::endl;
    os << img->width << " " << img->height << std::endl;
    os << "255" << std::endl;
    int redRow = 0, redCol = 0;
    int greenRow = 0, greenCol = 0;
    int blueRow = 0, blueCol = 0;
    const Matrix *redPtr = &img->red_channel;
    const Matrix *greenPtr = &img->green_channel;
    const Matrix *bluePtr = &img->blue_channel;
    int count = 0;
    for(int i = 0; i < ((Image_width(img) * Image_height(img))*3); i++){
        if(i % 3 == 0){
            os << *(Matrix_at(redPtr, redRow,redCol)) << " ";
            if (redCol < Matrix_width(redPtr) - 1){
                redCol++;
            }
            else{
                redCol = 0;
                redRow++;
            }
        }
        else if(i % 3 == 1){
            os << *(Matrix_at(greenPtr, greenRow,greenCol)) << " " ;
            if (greenCol < Matrix_width(greenPtr) - 1){
                greenCol++;
            }
            else{
                greenCol = 0;
                greenRow++;
            }
        }
        else if(i % 3 == 2){
            os << *(Matrix_at(bluePtr, blueRow,blueCol)) << " ";
            if (blueCol < Matrix_width(bluePtr) - 1){
                blueCol++;
            }
            else{
                blueCol = 0;
                blueRow++;
            }
        }
        count++;
        if(count == Image_width(img)*3){
            os << std::endl;
            count = 0;
        }
    }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
    return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
    return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
    assert(0 <= row && row < Image_height(img));
    assert(0 <= column && column < Image_width(img));
    
    const Matrix *redPtr = &img->red_channel;
    const Matrix *greenPtr = &img->green_channel;
    const Matrix *bluePtr = &img->blue_channel;
    Pixel p;
    p.r = *(Matrix_at(redPtr, row, column));
    p.g = *(Matrix_at(greenPtr, row, column));
    p.b = *(Matrix_at(bluePtr, row, column));
    
    return p;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
    assert(0 <= row && row < Image_height(img));
    assert(0 <= column && column < Image_width(img));
    
    
    Matrix *redPtr = &img->red_channel;
    Matrix *greenPtr = &img->green_channel;
    Matrix *bluePtr = &img->blue_channel;
    
    *(Matrix_at(redPtr, row, column)) = color.r;
    *(Matrix_at(greenPtr, row, column)) = color.g;
    *(Matrix_at(bluePtr, row, column)) = color.b;
    
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
    for(int row = 0; row < Image_height(img); row++){
        for(int column = 0; column < Image_width(img); column++){
            Image_set_pixel(img, row, column, color);
        }
    }
}
