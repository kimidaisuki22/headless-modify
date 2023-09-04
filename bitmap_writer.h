#pragma once

#include "bitmap.h"
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
template<typename T,int C>
void flip_v(Bitmap<T,C> & b){
    for(int i=0;i<b.height()/2;i++){
        for(int j=0;j<b.width();j++){
            swap(b[i][j],b[b.height()-1-i][j]);
        }
    }
}
template<typename T,int C>
void write_bitmap(std::string filename,Bitmap<T,C> &b){
    auto buffer =  b.flatten();
    stbi_write_png(filename.c_str(), b.width(),b.height(), C, buffer.data() , sizeof(T)*C * b.width());
    // stbi_write_jpg(filename.c_str(), b.width(),b.height(), C, buffer.data() ,70);
}