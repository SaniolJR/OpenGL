#include "drawMeshs.h"

Mesh::Mesh(const std::vector<float>& verts, const std::vector<unsigned int>& inds)
    : vbo(verts.data(), verts.size() * sizeof(float)), ebo(inds.data(), inds.size() * sizeof(unsigned int)), indexCount(inds.size()) {
    vao.Bind();
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);               // pozycja
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // tekstura
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float))); // normalne
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void drawSegments(Shader& shader, Mesh& mesh, const std::vector<Segment>& segments, std::unordered_map<std::string, Texture>& texs, Texture& defaultTex) {
   mesh.vao.Bind();
   for (const auto& s : segments) { // Fixed the loop to iterate over the 'segments' vector
       Texture* tex = nullptr;
       auto it = texs.find(s.material);
       if (it != texs.end()) tex = &it->second;
       else                 tex = &defaultTex; // Use the provided default texture
       tex->Bind();
       tex->texUnit(shader, "tex0", 0);
       glDrawElements(GL_TRIANGLES, s.count, GL_UNSIGNED_INT, (void*)(s.start * sizeof(unsigned int)));
   }
   mesh.vao.Unbind();
}
