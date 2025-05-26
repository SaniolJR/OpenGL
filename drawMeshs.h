#pragma once
#include <vector>
#include <glad/glad.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "Texture.h"
#include "Camera.h"
#include <map>
#include "geometry.h"

//struktura od reprezentacji segmentu
struct Mesh {
   VAO vao;
   VBO vbo;
   EBO ebo;
   size_t indexCount;

   // Konstruktor: inicjalizuje i konfiguruje VAO, VBO oraz EBO
   Mesh(const std::vector<float>& verts,
       const std::vector<unsigned int>& inds);
};

//funkcja od rysowanai tekstur na odpowiednich miejscach "w locie"
void drawSegments(Shader& shader,
   Mesh& mesh, // Changed from VAO& to Mesh&
   const std::vector<Segment>& segments,
   std::unordered_map<std::string, Texture>& texs, // Changed from std::map to std::unordered_map
   Texture& defaultTex);