#include "bedVertices.h"

void insertBedVertices(float x, float y, float z, std::vector<float>& vertices) {
	float dx = 2.0f; // szeroko�� ��ka
	float dz = 1.0f; // g��boko�� ��ka
	float lw = 0.3f; // szeroko�� n�g ��ka
	// Blat ��ka
	vertices.insert(vertices.end(), {
		x - dx, y, z - dz, 0.0f, 0.0f,	//lewy dolny r�g
		x + dx, y, z - dz, 1.0f, 0.0f,	// prawy dolny r�g
		x + dx, y, z + dz, 1.0f, 1.0f,	// prawy g�rny r�g
		x - dx, y, z + dz, 0.0f, 1.0f,	// lewy g�rny r�g
		});
	// Nogi ��ka (4 nogi)
	for (int i = 0; i < 4; ++i) {
		float legX = (i % 2 == 0) ? x - dx : x + dx;
		float legZ = (i < 2) ? z - dz : z + dz;
		vertices.insert(vertices.end(), {
			legX - lw, y - lw, legZ - lw, 0.0f, 0.0f,
			legX + lw, y - lw, legZ - lw, 1.0f, 0.0f,
			legX + lw, y + lw, legZ - lw, 1.0f, 1.0f,
			legX - lw, y + lw, legZ - lw, 0.0f, 1.0f,
			});
	}
}