
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <ios>
#include <limits>
#include <ostream>
#include <vector>

namespace stl_loader {
    using Vec3 = std::array<float,3>;
    struct Triangle{
        Vec3 normal_;
        std::array<Vec3, 3> positions_;
    };  
    struct Vertex{
        Vec3 position_;
        Vec3 normal_;
    };  
    
    inline void dump_raw_vertex(std::vector<Vertex>& buffer, int index,const Triangle &t){
        const auto& n = t.normal_;
        // fixit
        // auto n = t.normal_;
        // for(int i=0;i<3;i++){
        //     n[i]= std::abs(n[i]);
        // }

        for(int i=0;i<3;i++){
            buffer[i+index*3].normal_ = n;
            buffer[i+index*3].position_ = t.positions_[i];
        }
    }

    inline std::vector<Vertex> load(std::string filename){
        std::vector<Vertex> result;
        std::ifstream file{filename,std::ios::binary | std::ios::in};
        assert(file.is_open());

        char buffer[84]{};
        file.read(buffer, sizeof(buffer));
        uint32_t triangle_size = * reinterpret_cast<uint32_t*>(buffer + 80);
        if(!file.good() || !triangle_size){
            return result;
        }

        result.resize(triangle_size*3);

        constexpr uint32_t triangle_bytes = 50;

        for(int i=0;i<triangle_size;i++){
            Triangle t{};
            file.read(reinterpret_cast<char*>(&t),sizeof t);
            char pad[triangle_bytes - sizeof(t)];
            file.read(pad, sizeof pad);
            dump_raw_vertex(result, i, t);
        }
        return result;
    }
}

namespace stl_loader {
 inline   Vec3  operator+ (Vec3 a,Vec3 b){
        Vec3 result;
        for(int i=0;i<3;i++){
            result[i] = a[i]+ b[i];
        }
        return result;
    }
 inline       Vec3  operator- (Vec3 a,Vec3 b){
        Vec3 result;
        for(int i=0;i<3;i++){
            result[i] = a[i]- b[i];
        }
        return result;
    }
inline    Vec3  operator/ (Vec3 a,float b){
        Vec3 result;
        for(int i=0;i<3;i++){
            result[i] = a[i] /b;
        }
        return result;
    }
inline    Vec3  operator* (Vec3 a,float b){
        Vec3 result;
        for(int i=0;i<3;i++){
            result[i] = a[i] * b;
        }
        return result;
    }
}
inline std::vector<stl_loader::Vertex> centerlize(std::vector<stl_loader::Vertex> vertices ) {
    if (vertices.empty()) {
        return {};
    }
    using namespace stl_loader;
    stl_loader::Vec3 min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
    stl_loader::Vec3 max = { std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() };

    // Find the bounding box.
    for (const auto& vertex : vertices) {
        const stl_loader::Vec3& pos = vertex.position_;
        for(int i =0;i<3;i++){
            if (pos[i] < min[i]) min[i] = pos[i];
            if (pos[i] > max[i]) max[i] = pos[i];
        }
    }

    // Calculate the center of the bounding box.
    Vec3 center = (min + max) / 2.0f;

    // Create a new set of vertices that are centered.
    std::vector<Vertex> centeredVertices;
    centeredVertices.reserve(vertices.size());

    for (const auto& vertex : vertices) {
        Vertex newVertex = vertex;
        newVertex.position_ = vertex.position_ - center;
        centeredVertices.push_back(newVertex);
    }

    return centeredVertices;

}
