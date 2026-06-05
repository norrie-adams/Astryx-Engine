#pragma once

#include <vector>
#include <string>

namespace Loader {
    struct Vertex {
        double x;
        double y;
        double z;
    };

    std::vector<Vertex> loadVertices(const std::string& filename);
}