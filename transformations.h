#pragma once
#include <vector>
#include <cmath>

void transformBedVertices(float* verts, int count, float posX, float posY, float posZ, int orientation, float scaleX, float scaleZ);
void transformBedVertices8(float* verts, int count, float posX, float posY, float posZ, int orientation, float scaleX, float scaleZ);
