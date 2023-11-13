#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "geometry.h"

class Model {
private:
    std::vector<Vec3f> verts_;          // Container for vertices
    std::vector<std::vector<int>> faces_; // Container for faces

public:
    // Constructor that initializes the model by loading from a file
    explicit Model(const char* filename);

    // Destructor
    virtual ~Model();

    // Accessor for the number of vertices
    int nverts();

    // Accessor for the number of faces
    int nfaces();

    // Accessor for a vertex at index i
    Vec3f vert(int i);

    // Accessor for a face at index idx
    std::vector<int> face(int idx);
};

#endif // MODEL_H