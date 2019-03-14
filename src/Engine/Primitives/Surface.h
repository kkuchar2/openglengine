#ifndef OPENGL_SURFACE_H
#define OPENGL_SURFACE_H

#include "Mesh.h"

class Surface : public Mesh {
    public:

        int rows;
        int cols;

        explicit Surface(int rows, int cols) : Mesh() {
            this->rows = rows;
            this->cols = cols;

            int verticesSize = rows * cols;

            float x_left =  -14.0f;
            float x_right =  14.0f;

            float z_top =  -14.0f;
            float z_bottom =  14.0f;

            float scale = 20.0f / 10.0f;

            float step_x = (scale * (x_right - x_left)) / cols;
            float step_z = (scale * (z_bottom - z_top)) / cols;

            for (unsigned int vertexId = 0; vertexId < verticesSize; vertexId++) {

                int row = static_cast<int>(floor(vertexId / cols));
                int col = vertexId % cols;

                // Generate indices
                float x_mesh = x_left * scale + step_x * col;
                float z_mesh = z_top * scale + step_z * row;

                float x = x_mesh / scale;
                float z = z_mesh / scale;

                float y_mesh = abs(cos(x) * sin(cos(z)));

                vertices.insert(vertices.end(), {x_mesh, y_mesh, z_mesh});

                // Generate indices
                if (col == cols - 1) continue;

                if (row == 0) {
                    indices.insert(indices.end(), { vertexId, vertexId + cols, vertexId + 1 });
                }
                else if (row != rows - 1) {
                    indices.insert(indices.end(), { vertexId - cols + 1, vertexId, vertexId + 1 });
                    indices.insert(indices.end(), { vertexId, vertexId + cols, vertexId + 1 });
                }
                else {
                    indices.insert(indices.end(), { vertexId - cols + 1, vertexId, vertexId + 1 });
                }
            }
        }
};

#endif //OPENGL_SURFACE_H