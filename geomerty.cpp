#include "geometry.h"

void buildRoom(std::vector<float>& verts, std::vector<unsigned int>& inds){
    float pokoj_vert[] = {
        // Podloga (rozmiar 5x8)
   -2.5f, 0.0f, -4.0f,  0.0f, 0.0f,
    2.5f, 0.0f, -4.0f,  1.0f, 0.0f,
    2.5f, 0.0f,  4.0f,  1.0f, 1.0f,
   -2.5f, 0.0f,  4.0f,  0.0f, 1.0f,
   // Sufit
   -2.5f, 3.0f, -4.0f,  0.0f, 0.0f,
    2.5f, 3.0f, -4.0f,  1.0f, 0.0f,
    2.5f, 3.0f,  4.0f,  1.0f, 1.0f,
   -2.5f, 3.0f,  4.0f,  0.0f, 1.0f,
   // Sciana przednia
   -2.5f, 0.0f,  4.0f,  0.0f, 0.0f,
    2.5f, 0.0f,  4.0f,  1.0f, 0.0f,
    2.5f, 3.0f,  4.0f,  1.0f, 1.0f,
   -2.5f, 3.0f,  4.0f,  0.0f, 1.0f,

   // Sciana tylna
   -2.5f, 0.0f, -4.0f,  0.0f, 0.0f,
    2.5f, 0.0f, -4.0f,  1.0f, 0.0f,
    2.5f, 3.0f, -4.0f,  1.0f, 1.0f,
   -2.5f, 3.0f, -4.0f,  0.0f, 1.0f,
   // Sciana lewa
   -2.5f, 0.0f,  4.0f,  0.0f, 0.0f,
   -2.5f, 0.0f, -4.0f,  1.0f, 0.0f,
   -2.5f, 3.0f, -4.0f,  1.0f, 1.0f,
   -2.5f, 3.0f,  4.0f,  0.0f, 1.0f,
   // Sciana prawa
    2.5f, 0.0f, -4.0f,  0.0f, 0.0f,
    2.5f, 0.0f,  4.0f,  1.0f, 0.0f,
    2.5f, 3.0f,  4.0f,  1.0f, 1.0f,
    2.5f, 3.0f, -4.0f,  0.0f, 1.0f,
    // Drzwi (w scianie tylnej)
    -0.8f, 0.0f, -4.001f,  0.0f, 0.0f,
     0.8f, 0.0f, -4.001f,  1.0f, 0.0f,
     0.8f, 2.2f, -4.001f,  1.0f, 1.0f,
    -0.8f, 2.2f, -4.001f,  0.0f, 1.0f
    };

    unsigned int pokoj_ind[] = {
    0, 1, 2, 0, 2, 3,       // podloga
    4, 5, 6, 4, 6, 7,       // sufit
    8, 9,10, 8,10,11,       // przednia
    12,13,14,12,14,15,      // tyl
    16,17,18,16,18,19,      // lewa
    20,21,22,20,22,23,      // prawa
    24,25,26,24,26,27,      // drzwi
    };
    //dok³adamy do wektora
    verts.insert(verts.end(), std::begin(pokoj_vert), std::end(pokoj_vert));
	inds.insert(inds.end(), std::begin(pokoj_ind), std::end(pokoj_ind));

}


void buildBed(std::vector<float>& verts, std::vector<unsigned int>& inds) {
    unsigned int liczba_start = verts.size() / 5;

    float bed_vert[] = {
        // Lozko - blat
        -1.5f, 0.3f, 1.5f,  0.0f, 0.0f,
         1.5f, 0.3f, 1.5f,  1.0f, 0.0f,
         1.5f, 0.3f, 3.5f,  1.0f, 1.0f,
        -1.5f, 0.3f, 3.5f,  0.0f, 1.0f,
        // Nogi lozka (4 sztuki)
        -1.5f, 0.0f, 1.5f,  0.0f, 0.0f,
        -1.4f, 0.0f, 1.5f,  1.0f, 0.0f,
        -1.4f, 0.3f, 1.5f,  1.0f, 1.0f,
        -1.5f, 0.3f, 1.5f,  0.0f, 1.0f,

         1.4f, 0.0f, 1.5f,  0.0f, 0.0f,
         1.5f, 0.0f, 1.5f,  1.0f, 0.0f,
         1.5f, 0.3f, 1.5f,  1.0f, 1.0f,
         1.4f, 0.3f, 1.5f,  0.0f, 1.0f,

        -1.5f, 0.0f, 3.5f,  0.0f, 0.0f,
        -1.4f, 0.0f, 3.5f,  1.0f, 0.0f,
        -1.4f, 0.3f, 3.5f,  1.0f, 1.0f,
        -1.5f, 0.3f, 3.5f,  0.0f, 1.0f,

         1.4f, 0.0f, 3.5f,  0.0f, 0.0f,
         1.5f, 0.0f, 3.5f,  1.0f, 0.0f,
         1.5f, 0.3f, 3.5f,  1.0f, 1.0f,
         1.4f, 0.3f, 3.5f,  0.0f, 1.0f,
    };
    
    unsigned int bed_ind[] = {
    0,1,2,0,2,3,      // lozko
    4,5,6,4,6,7,      // noga 1
    8,9,10,8,10,11,      // noga 2
    12,13,14,12,14,15,      // noga 3
    16,17,18,16,18,19      // noga 4
    };

    for (int i = 0; i < 30; i++ ) {
		bed_ind[i] += liczba_start;
	}

    verts.insert(verts.end(), std::begin(bed_vert), std::end(bed_vert));
    inds.insert(inds.end(), std::begin(bed_ind), std::end(bed_ind));
}


float vertices[] = {
    // Podloga (rozmiar 5x8)
    -2.5f, 0.0f, -4.0f,  0.0f, 0.0f,
     2.5f, 0.0f, -4.0f,  1.0f, 0.0f,
     2.5f, 0.0f,  4.0f,  1.0f, 1.0f,
    -2.5f, 0.0f,  4.0f,  0.0f, 1.0f,
    // Sufit
    -2.5f, 3.0f, -4.0f,  0.0f, 0.0f,
     2.5f, 3.0f, -4.0f,  1.0f, 0.0f,
     2.5f, 3.0f,  4.0f,  1.0f, 1.0f,
    -2.5f, 3.0f,  4.0f,  0.0f, 1.0f,
    // Sciana przednia
    -2.5f, 0.0f,  4.0f,  0.0f, 0.0f,
     2.5f, 0.0f,  4.0f,  1.0f, 0.0f,
     2.5f, 3.0f,  4.0f,  1.0f, 1.0f,
    -2.5f, 3.0f,  4.0f,  0.0f, 1.0f,

    // Sciana tylna
    -2.5f, 0.0f, -4.0f,  0.0f, 0.0f,
     2.5f, 0.0f, -4.0f,  1.0f, 0.0f,
     2.5f, 3.0f, -4.0f,  1.0f, 1.0f,
    -2.5f, 3.0f, -4.0f,  0.0f, 1.0f,
    // Sciana lewa
    -2.5f, 0.0f,  4.0f,  0.0f, 0.0f,
    -2.5f, 0.0f, -4.0f,  1.0f, 0.0f,
    -2.5f, 3.0f, -4.0f,  1.0f, 1.0f,
    -2.5f, 3.0f,  4.0f,  0.0f, 1.0f,
    // Sciana prawa
     2.5f, 0.0f, -4.0f,  0.0f, 0.0f,
     2.5f, 0.0f,  4.0f,  1.0f, 0.0f,
     2.5f, 3.0f,  4.0f,  1.0f, 1.0f,
     2.5f, 3.0f, -4.0f,  0.0f, 1.0f,
     // Drzwi (w scianie tylnej)
     -0.8f, 0.0f, -4.001f,  0.0f, 0.0f,
      0.8f, 0.0f, -4.001f,  1.0f, 0.0f,
      0.8f, 2.2f, -4.001f,  1.0f, 1.0f,
     -0.8f, 2.2f, -4.001f,  0.0f, 1.0f,
     // Lozko - blat
     -1.5f, 0.3f, 1.5f,  0.0f, 0.0f,
      1.5f, 0.3f, 1.5f,  1.0f, 0.0f,
      1.5f, 0.3f, 3.5f,  1.0f, 1.0f,
     -1.5f, 0.3f, 3.5f,  0.0f, 1.0f,
     // Nogi lozka (4 sztuki)
     -1.5f, 0.0f, 1.5f,  0.0f, 0.0f,
     -1.4f, 0.0f, 1.5f,  1.0f, 0.0f,
     -1.4f, 0.3f, 1.5f,  1.0f, 1.0f,
     -1.5f, 0.3f, 1.5f,  0.0f, 1.0f,

      1.4f, 0.0f, 1.5f,  0.0f, 0.0f,
      1.5f, 0.0f, 1.5f,  1.0f, 0.0f,
      1.5f, 0.3f, 1.5f,  1.0f, 1.0f,
      1.4f, 0.3f, 1.5f,  0.0f, 1.0f,

     -1.5f, 0.0f, 3.5f,  0.0f, 0.0f,
     -1.4f, 0.0f, 3.5f,  1.0f, 0.0f,
     -1.4f, 0.3f, 3.5f,  1.0f, 1.0f,
     -1.5f, 0.3f, 3.5f,  0.0f, 1.0f,

      1.4f, 0.0f, 3.5f,  0.0f, 0.0f,
      1.5f, 0.0f, 3.5f,  1.0f, 0.0f,
      1.5f, 0.3f, 3.5f,  1.0f, 1.0f,
      1.4f, 0.3f, 3.5f,  0.0f, 1.0f,
};

unsigned int indices[] = {
    0, 1, 2, 0, 2, 3,       // podloga
    4, 5, 6, 4, 6, 7,       // sufit
    8, 9,10, 8,10,11,       // przednia
    12,13,14,12,14,15,      // tyl
    16,17,18,16,18,19,      // lewa
    20,21,22,20,22,23,      // prawa
    24,25,26,24,26,27,      // drzwi
    28,29,30,28,30,31,      // lozko
    32,33,34,32,34,35,      // noga 1
    36,37,38,36,38,39,      // noga 2
    40,41,42,40,42,43,      // noga 3
    44,45,46,44,46,47,      // noga 4
};