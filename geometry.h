#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "tiny_obj_loader.h"
#include <stdexcept> // Add this include directive at the top of the file to fix the error
#include <unordered_map>
#include <string>
#include <fstream>      // std::ifstream
#include <sstream>      // std::istringstream
#include <cstdlib>      // std::exit
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void buildRoom(std::vector<float>& verts, std::vector<unsigned int>& inds)
;
void readValues(int i, std::string s, std::vector<float>& vec);

void buildSphere(std::vector<float>& vertices, std::vector<unsigned int>& indices, float radius, int sectorCount = 24, int stackCount = 16);

struct Segment {
    std::string material;
    int start;
    int count;
};

void parseFromObj(std::vector<float>& verts, 
    std::vector<unsigned int>& inds, 
    const std::string& path, 
    std::vector<Segment>& segments, 
    float x, float y, float z, 
    float scale);

void rotateVertices(std::vector<float>& verts, float angleX, float angleY, float angleZ);