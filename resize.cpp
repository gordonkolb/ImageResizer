#include <cstdlib>
#include <fstream>
#include <iostream>
#include "Matrix.h"
#include "Image.h"
#include "processing.h"

int main(int argc, char *argv[]){
    if (argc != 4 && argc != 5) {
        std::cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH";
        std::cout << "[HEIGHT]\n" "WIDTH and HEIGHT must be less";
        std::cout << "than or equal to original" << std::endl;
        return 1;
    }
    
    Image *ptr = new Image;
    std::ifstream fin;
    std::string filename  = argv[1];
    fin.open(filename);
    if (!fin.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        delete ptr;
        return 1;
    }
    Image_init(ptr, fin);
    fin.close();

    
    int height = 0;
    int width = atoi(argv[3]);
    if(argc == 5){
        height = atoi(argv[4]);
    }
    else if(argc == 4){
        height = Image_height(ptr);
    }
    
    if(width < 0 || width > Image_width(ptr) || height < 0 ||
       height > Image_height(ptr)) {
        std::cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH";
        std::cout << "[HEIGHT]\n" "WIDTH and HEIGHT must be less";
        std::cout << "than or equal to original" << std::endl;
        delete ptr;
        return 1;
    }
    
    seam_carve(ptr, width, height);
    
    std::ofstream fout;
    std::string newFile = argv[2];
    fout.open(newFile);
    if (!fout.is_open()) {
        std::cout << "Error opening file: " << newFile << std::endl;
    }
    Image_print(ptr, fout);
    fout.close();
    
    delete ptr;
    
    return 0;
}
