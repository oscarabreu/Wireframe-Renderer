/*
// Garbage. If we create a longer line and hold the constant the same we get a dotted line.

// void line(int x_0, int y_0, int x_1, int y_1, TGAImage &image, TGAColor color) {
// 	for (float t = 0; t <= 1; t += 0.01) {
// 		int x = x_0 + (x_1 - x_0)*t;
// 		int y = y_0 + (y_1 - y_0)*t;
// 		image.set(x, y, color);
// 	}
// }

// Garbage. We iterate on x_0 and compute y for each x_0.
// We assume x_0 < x_1, and that delta y < delta x.
// Won't work for all lines.

// void line(int x_0, int y_0, int x_1, int y_1, TGAImage &image, TGAColor color) { 
//     for (int x=x_0; x<=x_1; x++) { 
//         float t = (x-x_0)/(float)(x_1-x_0); 
//         int y = y_0*(1.-t) + y_1*t; 
//         image.set(x, y, color); 
//     } 
// }
*/
#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
Model *model = NULL;
const int width  = 800;
const int height = 800;

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bool steep = false;
    
    // Transpose the line if it's steep
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    
    // Ensure the line is drawn from left to right
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    // Draw the line using linear interpolation
    for (int x = x0; x <= x1; x++) {
        float t = (x - x0) / static_cast<float>(x1 - x0);
        int y = y0 * (1.0f - t) + y1 * t;
        
        // If the line was transposed, de-transpose when drawing
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
    }
}

int main(int argc, char** argv) {
    // Load the model
    Model *model = nullptr;
    if (argc == 2) {
        model = new Model(argv[1]);
    } else {
        model = new Model("obj/basketball.obj");
    }

    // Create an image object
    TGAImage image(width, height, TGAImage::RGB);
    
    // Draw the wireframe
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j = 0; j < 3; j++) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j + 1) % 3]);
            int x0 = static_cast<int>((v0.x + 1.0f) * width / 2.0f);
            int y0 = static_cast<int>((v0.y + 1.0f) * height / 2.0f);
            int x1 = static_cast<int>((v1.x + 1.0f) * width / 2.0f);
            int y1 = static_cast<int>((v1.y + 1.0f) * height / 2.0f);
            line(x0, y0, x1, y1, image, white);
        }
    }

    // Process the image
    image.flip_vertically(); // Set the origin to the bottom-left corner
    image.write_tga_file("output.tga");
    
    // Clean up
    delete model;
    return 0;
}