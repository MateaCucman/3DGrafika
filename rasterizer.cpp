#include <iostream>
#include <cmath>
#include <algorithm>
#include "tgaimage.h"

const int width  = 512;
const int height = 512;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0, 0, 255);
const TGAColor blue  = TGAColor(0, 0, 255, 255);
const TGAColor green  = TGAColor(0, 255, 0, 255);

float area(float x0, float y0, float x1, float y1, float x2, float y2){
    return std::abs(x0*(y1-y2) + x1*(y2-y0) + x2*(y0-y1))/2;
}

void draw_triangle_2d(TGAImage& image, float x0, float y0, float x1, float y1, float x2, float y2, TGAColor color){
    float A, A1, A2, A3;
    A = area(x0,y0,x1,y1,x2,y2);
    for(int i = 0; i<image.get_width(); i++)
        for(int j = 0; j< image.get_height(); j++){
            A1 = area(i,j,x1,y1,x2,y2);
            A2 = area(x0,y0,i,j,x2,y2);
            A3 = area(x0,y0,x1,y1,i,j);
            if(A == A1+A2+A3)
                image.set(i,j,color);
        }

}

void draw_triangle_2d_gouraurd(TGAImage& image, float x0, float y0, float x1, float y1, float x2, float y2, TGAColor c1, TGAColor c2, TGAColor c3){
 /*   image.set(x0,y0,c1);
    image.set(x1,y1,c2);
    image.set(x2,y2,c3);*/
    float A, A1, A2, A3;
    float a1,a2,a3;
    TGAColor k,k1,k2,k3;
    A = area(x0,y0,x1,y1,x2,y2);
    for(int i = 0; i<image.get_width(); i++)
        for(int j = 0; j< image.get_height(); j++){
            A1 = area(i,j,x1,y1,x2,y2);
            A2 = area(x0,y0,i,j,x2,y2);
            A3 = area(x0,y0,x1,y1,i,j);
            if(A == A1+A2+A3){
                a1 = A1/A; a2 = A2/A; a3 = A3/A;
                k.r = (c1.r+c2.r+c3.r)*a1;
                k.g = (c1.g+c2.g+c3.g)*a2;
                k.b = (c1.b+c2.b+c3.b)*a3;
                image.set(i,j,k);
            }
        }
}

void draw_triangle_tex(TGAImage& image, float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float u0, float v0, float u1, float v1, float u2, float v2, const char* path)
{

}

void draw_triangle_tex_corrected(TGAImage& image, float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float u0, float v0, float u1, float v1, float u2, float v2, const char* path)
{

}

int main(){
    // definiraj sliku
    TGAImage image(width, height, TGAImage::RGB);
    for(int i = 0; i<image.get_width(); i++)
        for(int j = 0; j< image.get_height(); j++)
            image.set(i,j,white);

    draw_triangle_2d(image, 20, 30, 180, 80, 100, 200, blue);
    draw_triangle_2d(image, 120, 230, 280, 180, 230, 300, red);
    draw_triangle_2d_gouraurd(image,470,420,300,400,450,320,blue, green, red);

    // spremi sliku
    image.flip_vertically();
    image.write_tga_file("triangles.tga");
}