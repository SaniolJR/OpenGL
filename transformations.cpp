#include "transformations.h"

void transformBedVertices(float* verts, int count, float posX, float posY, float posZ, int orientation) {
    // orientation: 0=0°,1=90°,2=180°,3=270°
    float angle = orientation * (3.1415926f / 2.0f);
    float cosA = cos(angle);
    float sinA = sin(angle);

    for (int i = 0; i < count; i++) {
        float x = verts[i * 5 + 0];
        float y = verts[i * 5 + 1];
        float z = verts[i * 5 + 2];

        // Obrót wokó³ Y
        float xNew = x * cosA - z * sinA;
        float zNew = x * sinA + z * cosA;

        // Translacja
        verts[i * 5 + 0] = xNew + posX;
        verts[i * 5 + 1] = y + posY;
        verts[i * 5 + 2] = zNew + posZ;
    }
}