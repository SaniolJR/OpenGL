#include "geometry.h"

void buildRoom(std::vector<float>& verts, std::vector<unsigned int>& inds) {
    unsigned int liczba_start = verts.size() / 8;
    // Ka�da �ciana: 4 wierzcho�ki = 4 x (x, y, z, u, v, nx, ny, nz)
    float pokoj_vert[] = {
        // Pod�oga (normalna: 0, 1, 0)
       -2.5f, 0.0f, -4.0f,  0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
        2.5f, 0.0f, -4.0f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
        2.5f, 0.0f,  4.0f,  1.0f, 1.0f,   0.0f, 1.0f, 0.0f,
       -2.5f, 0.0f,  4.0f,  0.0f, 1.0f,   0.0f, 1.0f, 0.0f,

       // Sufit (normalna: 0, -1, 0)
      -2.5f, 3.0f, -4.0f,  0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
       2.5f, 3.0f, -4.0f,  1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
       2.5f, 3.0f,  4.0f,  1.0f, 1.0f,   0.0f, -1.0f, 0.0f,
      -2.5f, 3.0f,  4.0f,  0.0f, 1.0f,   0.0f, -1.0f, 0.0f,

      // �ciana przednia (normalna: 0, 0, -1)
     -2.5f, 0.0f,  4.0f,  0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
      2.5f, 0.0f,  4.0f,  1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
      2.5f, 3.0f,  4.0f,  1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
     -2.5f, 3.0f,  4.0f,  0.0f, 1.0f,   0.0f, 0.0f, -1.0f,

     // �ciana tylna (normalna: 0, 0, 1)
    -2.5f, 0.0f, -4.0f,  0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
     2.5f, 0.0f, -4.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
     2.5f, 3.0f, -4.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
    -2.5f, 3.0f, -4.0f,  0.0f, 1.0f,   0.0f, 0.0f, 1.0f,

    // �ciana lewa (normalna: 1, 0, 0)
   -2.5f, 0.0f,  4.0f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
   -2.5f, 0.0f, -4.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
   -2.5f, 3.0f, -4.0f,  1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
   -2.5f, 3.0f,  4.0f,  0.0f, 1.0f,   1.0f, 0.0f, 0.0f,

   // �ciana prawa (normalna: -1, 0, 0)
   2.5f, 0.0f, -4.0f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
   2.5f, 0.0f,  4.0f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
   2.5f, 3.0f,  4.0f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
   2.5f, 3.0f, -4.0f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,

   // Drzwi (w �cianie tylnej) (normalna: 0, 0, 1)
  -0.8f, 0.0f, -4.001f,  0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
   0.8f, 0.0f, -4.001f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
   0.8f, 2.2f, -4.001f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
  -0.8f, 2.2f, -4.001f,  0.0f, 1.0f,   0.0f, 0.0f, 1.0f
    };

    
    unsigned int pokoj_ind[] = {
        0, 1, 2, 0, 2, 3,       // pod�oga
        4, 5, 6, 4, 6, 7,       // sufit
        8, 9,10, 8,10,11,       // przednia
        12,13,14,12,14,15,      // tyl
        16,17,18,16,18,19,      // lewa
        20,21,22,20,22,23,      // prawa
        24,25,26,24,26,27       // drzwi
    };

    verts.insert(verts.end(), std::begin(pokoj_vert), std::end(pokoj_vert));
    inds.insert(inds.end(), std::begin(pokoj_ind), std::end(pokoj_ind));

   
}

void buildBed(std::vector<float>& verts, std::vector<unsigned int>& inds, float posX, float posY, float posZ, int orientation, float scaleX, float scaleZ) {
    unsigned int liczba_start = verts.size() / 8;

    float bed_vert[] = {
        // blat ��ka (normalna 0,1,0)
        -1.5f, 0.3f, 1.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         1.5f, 0.3f, 1.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         1.5f, 0.3f, 3.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
        -1.5f, 0.3f, 3.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,

        // noga 1
        -1.5f, 0.0f, 1.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        -1.4f, 0.0f, 1.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        -1.4f, 0.3f, 1.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
        -1.5f, 0.3f, 1.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,

        // noga 2
         1.4f, 0.0f, 1.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         1.5f, 0.0f, 1.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         1.5f, 0.3f, 1.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
         1.4f, 0.3f, 1.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,

         // noga 3
         -1.5f, 0.0f, 3.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         -1.4f, 0.0f, 3.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         -1.4f, 0.3f, 3.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
         -1.5f, 0.3f, 3.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,

         // noga 4
          1.4f, 0.0f, 3.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
          1.5f, 0.0f, 3.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
          1.5f, 0.3f, 3.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
          1.4f, 0.3f, 3.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f
    };

    transformBedVertices8(bed_vert, 20, posX, posY, posZ, orientation, scaleX, scaleZ);

    unsigned int bed_ind[] = {
        0,1,2,0,2,3,       // blat
        4,5,6,4,6,7,       // noga 1
        8,9,10,8,10,11,    // noga 2
        12,13,14,12,14,15, // noga 3
        16,17,18,16,18,19  // noga 4
    };

    for (int i = 0; i < 30; i++) {
        bed_ind[i] += liczba_start;
    }

    verts.insert(verts.end(), std::begin(bed_vert), std::end(bed_vert));
    inds.insert(inds.end(), std::begin(bed_ind), std::end(bed_ind));
}

void readValues(int i, std::string line, std::vector<float>& vec) {
    std::string val;

    while (i < line.size()) {
        if (line[i] != ' ') {
            val += line[i];
        }
        else {
            if (!val.empty()) {
                vec.push_back(std::stof(val));
                val.clear();
            }
        }
        i++;
    }

    if (!val.empty()) {
        vec.push_back(std::stof(val));
    }
}

void parseFromObj(std::vector<float>& verts, std::vector<unsigned int>& inds, const std::string& path, std::vector<Segment>& segments, float x, float y, float z, float scale) {
    std::ifstream in(path, std::ios::in);
    if (!in) {
        std::cerr << "Cannot open " << path << std::endl;
        std::exit(1);
    }

    std::vector<float> positions;
    std::vector<float> texcoords;
    std::vector<float> normals;
    int vertOffset = verts.size() / 8; // ile juz bylo verteksów
    std::string line;

    //zmienne do obslugi materialow
    std::string currentMtl = "default", prevMtl = currentMtl;
    int segStart = vertOffset;



    while (std::getline(in, line)) {

        std::string type;
        //zczytanie do pierwszej spacji w linii - typ
        int i = 0;
        while (line[i] != ' ' && line[i] != '\0') {
            type += line[i];
            i++;
        }
        i++; // przeskoczenie aktualnej spacji
        if (type == "usemtl") {
            // zamykamy poprzedni segment
            if (vertOffset - segStart > 0) {
                segments.push_back({ prevMtl, segStart, vertOffset - segStart });
            }
            // czytamy nową nazwę materiału
            currentMtl.clear();
            while (i < (int)line.size() && line[i] != ' ' && line[i] != '\r' && line[i] != '\n') {
                currentMtl += line[i++];
            }
            prevMtl = currentMtl;
            segStart = vertOffset;
        }
        else if (type == "v") {
            readValues(i, line, positions);
        }
        else if (type == "vt") {
            readValues(i, line, texcoords);
        }
        else if (type == "vn") {
            readValues(i, line, normals);
        }
        else if (type == "f") {
            for (int v = 0; v < 3; v++) { // zak³adamy trójk¹ty
                std::string val = "";
                int posIdx = 0, texIdx = 0, normIdx = 0;
                int valIdx = 0;

                while (line[i] != ' ' && line[i] != '\0') {
                    if (line[i] != '/') {
                        val += line[i];
                    }
                    else {
                        if (valIdx == 0) posIdx = std::stoi(val);
                        else if (valIdx == 1) texIdx = std::stoi(val);
                        val = "";
                        valIdx++;
                    }
                    i++;
                }
                // ostatnia wartoœæ (normals)
                if (!val.empty()) normIdx = std::stoi(val);

                posIdx--; texIdx--; // indeksy od 1 w .obj, u nas od 0

                // dodajemy pozycje (3 floaty)
                verts.push_back( (positions[posIdx * 3 + 0] + x) * scale );
                verts.push_back( (positions[posIdx * 3 + 1] + y) * scale );
                verts.push_back( (positions[posIdx * 3 + 2] + z) * scale );

                // dodajemy tekstury (2 floaty)
                verts.push_back(texcoords[texIdx * 2 + 0]);
                verts.push_back(texcoords[texIdx * 2 + 1]);

                // dodawanie normals

                if (normals.size() >= (size_t)(normIdx * 3 + 3)) {
                    verts.push_back(normals[normIdx * 3 + 0]);
                    verts.push_back(normals[normIdx * 3 + 1]);
                    verts.push_back(normals[normIdx * 3 + 2]);
                }
                else {
                    // defaultowa normalna (np. w górę):
                    verts.push_back(0.0f);
                    verts.push_back(1.0f);
                    verts.push_back(0.0f);
                }
                

                // liczba vertexów to verts.size() / 5 (bo ka¿dy vertex to 5 floatów)
                inds.push_back(vertOffset++);

                // przeskocz spacjê jeœli jest
                if (line[i] == ' ') i++;
            }

        }
        
    }
    if (vertOffset - segStart > 0) {
        segments.push_back({ prevMtl, segStart, vertOffset - segStart });
    }

}
