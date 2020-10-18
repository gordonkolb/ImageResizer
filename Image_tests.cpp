// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);



  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(image_width_and_height){
    Image *img = new Image;
    
    const Pixel red = {255, 0, 0};
    const Pixel green = {0, 255, 0};
    const Pixel blue = {0, 0, 255};
    const Pixel white = {255, 255, 255};
    
    Image_init(img, 2, 2);
    Image_set_pixel(img, 0, 0, red);
    Image_set_pixel(img, 0, 1, green);
    Image_set_pixel(img, 1, 0, blue);
    Image_set_pixel(img, 1, 1, white);
    
    int w = Image_width(img);
    ASSERT_EQUAL(w, 2);
    int h = Image_height(img);
    ASSERT_EQUAL(h, 2);
    
    delete img;
}

TEST(image_get_pixel){
    Image *img = new Image;
    
    const Pixel red = {255, 0, 0};
    const Pixel green = {0, 255, 0};
    const Pixel blue = {0, 0, 255};
    const Pixel random = {123, 45, 67};
    
    Image_init(img, 2, 2);
    Image_set_pixel(img, 0, 0, red);
    Image_set_pixel(img, 0, 1, green);
    Image_set_pixel(img, 1, 0, blue);
    Image_set_pixel(img, 1, 1, random);
    
    Pixel p1 = Image_get_pixel(img, 1, 1);
    ASSERT_EQUAL(p1.r, 123);
    ASSERT_EQUAL(p1.g, 45);
    ASSERT_EQUAL(p1.b, 67);
    
    delete img;
}

TEST(image_fill){
    
    Image *img = new Image;

    const Pixel random = {123, 45, 67};
    
    Image_init(img, 2, 2);
    Image_fill(img, random);
    for(int r = 0; r < Image_height(img); r++){
        for(int c = 0; c < Image_width(img); c++){
            Pixel p = Image_get_pixel(img, r, c);
            ASSERT_EQUAL(p.r, 123);
            ASSERT_EQUAL(p.g, 45);
            ASSERT_EQUAL(p.b, 67);
        }
    }
    
    delete img;
}


TEST_MAIN() // Do NOT put a semicolon here
