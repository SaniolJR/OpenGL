#pragma once
#include <vector>
#include <cmath>
#include "transformations.h"
void buildRoom(std::vector<float>& verts, std::vector<unsigned int>& inds);
void buildBed(std::vector<float>& verts, std::vector<unsigned int>& inds, float posX, float posY, float posZ, int orientation, float scaleX, float scaleZ);
void buildRoomNew(std::vector<float>& verts, std::vector<unsigned int>& inds);
void buildBedNew(std::vector<float>& verts, std::vector<unsigned int>& inds, float posX, float posY, float posZ, int orientation, float scaleX, float scaleZ);