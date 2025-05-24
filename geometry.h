#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "transformations.h"
#include "tiny_obj_loader.h"
#include <stdexcept> // Add this include directive at the top of the file to fix the error
#include <unordered_map>
#include <string>
#include <fstream>      // std::ifstream
#include <sstream>      // std::istringstream
#include <cstdlib>      // std::exit

void buildRoom(std::vector<float>& verts, std::vector<unsigned int>& inds);
void buildBed(std::vector<float>& verts, std::vector<unsigned int>& inds, float posX, float posY, float posZ, int orientation, float scaleX, float scaleZ);
void readValues(int i, std::string s, std::vector<float>& vec);

struct Segment {
    std::string material;
    int start;
    int count;
};

void parseFromObj(
    std::vector<float>& verts,
    std::vector<unsigned int>& inds,
    const std::string& path,
    std::vector<Segment>& segments,  // now ze struct¹
    float x,
    float y,
    float z, 
    float scale
);