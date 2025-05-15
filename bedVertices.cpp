#include "bedVertices.h"

void insertBedVertices(float x, float y, float z, std::vector<float>& vertices) {
	float dx = 2.0f; // szerokoœæ ³ó¿ka
	float dz = 1.0f; // g³êbokoœæ ³ó¿ka
	float lw = 0.3f; // szerokoœæ nóg ³ó¿ka
	// Blat ³ó¿ka
	vertices.insert(vertices.end(), {
		x - dx, y, z - dz, 0.0f, 0.0f,	//lewy dolny róg
		x + dx, y, z - dz, 1.0f, 0.0f,	// prawy dolny róg
		x + dx, y, z + dz, 1.0f, 1.0f,	// prawy górny róg
		x - dx, y, z + dz, 0.0f, 1.0f,	// lewy górny róg
		});
	// Nogi ³ó¿ka (4 nogi)
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