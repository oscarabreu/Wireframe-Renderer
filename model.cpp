#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char *filename) : verts_(), faces_() {
    std::ifstream in(filename); // Automatically opens the file
    if (in.fail()) {
        std::cerr << "Failed to open " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        char trash;
        if (line.substr(0, 2) == "v ") {
            iss >> trash; // Read and discard the 'v' character
            Vec3f v;
            for (int i = 0; i < 3; ++i) {
                iss >> v.raw[i];
            }
            verts_.push_back(v);
        } else if (line.substr(0, 2) == "f ") {
            std::vector<int> f;
            int itrash, idx;
            iss >> trash; // Read and discard the 'f' character
            while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                idx--; // Adjust for 0-based indexing
                f.push_back(idx);
            }
            faces_.push_back(f);
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;
}
Model::~Model() {
    // Destructor - currently empty as vectors are automatically cleaned up
}

int Model::nverts() {
    return static_cast<int>(verts_.size());
}

int Model::nfaces() {
    return static_cast<int>(faces_.size());
}

std::vector<int> Model::face(int idx) {
    return faces_.at(idx); // Using .at() for bounds checking
}

Vec3f Model::vert(int i) {
    return verts_.at(i); // Using .at() for bounds checking
}