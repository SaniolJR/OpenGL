#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"
#include "geometry.h"
#include <unordered_map>


const unsigned int width = 1920;
const unsigned int height = 1080;

//ustawienie startowej pozycji kamery na srodek pokoju
Camera camera(width, height, glm::vec3(0.0f, 1.5f, -4.0f));

std::vector<glm::vec3> lightPositions = {
    {-2.4f, 2.9f, -0.75f},
    {-2.4f, 2.9f, -0.25f},
    {-2.4f, 2.9f,  0.25f},
    {-2.4f, 2.9f,  0.75f},
    {2.4f, 2.9f, -0.75f },
    {2.4f, 2.9f, -0.25f},
    {2.4f, 2.9f, 0.25f},
    {2.4f, 2.9f, 0.75f}
};



int main() {
   //wektory do przechowywania wierzcholków - osobno dla pokoju jak i dla każdego rodzaju mabla aby nie było syfu!
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> verticesStol;
    std::vector<unsigned int> indicesStol;
    std::vector<float> verticesSzafa;
    std::vector<unsigned int> indicesSzafa;
	std::vector<float> verticesLozko;
	std::vector<unsigned int> indicesLozko;
    std::vector<float> verticesLozko1;
    std::vector<unsigned int> indicesLozko1;
	std::vector<float> verticeskrzeslo;
	std::vector<unsigned int> indiceskrzeslo;
    std::vector<float> ledVertices;
    std::vector<unsigned int> ledIndices;

	buildRoom(vertices, indices);//rosowanie pokoju
	buildSphere(ledVertices, ledIndices, 0.1f);//rysowanie sfery LED

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Pokoj z lozkiem", NULL, NULL);
    if (!window) {
        std::cerr << "Blad tworzenia okna GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    //------------------------pokoj
    Shader shader("default.vert", "default.frag");
    Shader ledShader("led.vert", "led.frag");

    VAO vao;
    vao.Bind();
    VBO vbo(vertices.data(), vertices.size() * sizeof(float));
    EBO ebo(indices.data(), indices.size() * sizeof(unsigned int));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);               // pozycja
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // tekstura
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float))); // normalne
    vao.Unbind(); vbo.Unbind(); ebo.Unbind();

    //------------------------stol
    std::vector<Segment> stolSeg;
    parseFromObj(verticesStol, indicesStol, "stol.obj", stolSeg, 2.68, 0.55, -1.75, 0.75);   //-x, -y, -z, skala
    parseFromObj(verticesStol, indicesStol, "stol.obj", stolSeg, 2.68, 0.56, 1.75, 0.75);    //-x, -y, -z

    VAO vaoTable;
    VBO vboTable(verticesStol.data(), verticesStol.size() * sizeof(float));
    EBO eboTable(indicesStol.data(), indicesStol.size() * sizeof(unsigned int));

    vaoTable.Bind();
    vboTable.Bind();
    eboTable.Bind();
    vaoTable.LinkAttrib(vboTable, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);              // pos
    vaoTable.LinkAttrib(vboTable, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoTable.LinkAttrib(vboTable, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float))); // normals

    vaoTable.Unbind();
    vboTable.Unbind();
    eboTable.Unbind();
    //------------------------szafa
    std::vector<Segment> szafaSeg;
    parseFromObj(verticesSzafa, indicesSzafa, "szafa.obj", szafaSeg, 3.95, 2.475, 6.15, 0.5);
    parseFromObj(verticesSzafa, indicesSzafa, "szafa.obj", szafaSeg, 3.95, 2.475, -6.8, 0.5);
    VAO vaoSzafa;
    VBO vboSzafa(verticesSzafa.data(), verticesSzafa.size() * sizeof(float));
    EBO eboSzafa(indicesSzafa.data(), indicesSzafa.size() * sizeof(unsigned int));
       
    vaoSzafa.Bind();
    vboSzafa.Bind();
    eboSzafa.Bind();
    vaoSzafa.LinkAttrib(vboSzafa, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);              // pos
    vaoSzafa.LinkAttrib(vboSzafa, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoSzafa.LinkAttrib(vboSzafa, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float))); // normals
       
    vaoSzafa.Unbind();
    vboSzafa.Unbind();
    eboSzafa.Unbind();
	//------------------------łóżko
    std::vector<Segment> LozkoSeg;
    parseFromObj(verticesLozko, indicesLozko, "lozko.obj", LozkoSeg, 10.5, 1.2, -6.5, 0.25);
    rotateVertices(verticesLozko, 0.0f, 90.0f, 0.0f); // np. obrót stołu o 30° wokół Y

    VAO vaoLozko;
    VBO vboLozko(verticesLozko.data(), verticesLozko.size() * sizeof(float));
    EBO eboLozko(indicesLozko.data(), indicesLozko.size() * sizeof(unsigned int));

    vaoLozko.Bind();
    vboLozko.Bind();
    eboLozko.Bind();
    vaoLozko.LinkAttrib(vboLozko, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);              // pos
    vaoLozko.LinkAttrib(vboLozko, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoLozko.LinkAttrib(vboLozko, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float))); // normals

    vaoLozko.Unbind();
    vboLozko.Unbind();
    eboLozko.Unbind();

    //lozko 2
    std::vector<Segment> Lozko1Seg;
    parseFromObj(verticesLozko1, indicesLozko1, "lozko.obj", Lozko1Seg, 10.5, 1.2, 6.5, 0.25);
    rotateVertices(verticesLozko1, 0.0f, 270.0f, 0.0f); // np. obrót stołu o 30° wokół Y

    VAO vaoLozko1;
    VBO vboLozko1(verticesLozko1.data(), verticesLozko1.size() * sizeof(float));
    EBO eboLozko1(indicesLozko1.data(), indicesLozko1.size() * sizeof(unsigned int));

    vaoLozko1.Bind();
    vboLozko1.Bind();
    eboLozko1.Bind();
    vaoLozko1.LinkAttrib(vboLozko1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);              // pos
    vaoLozko1.LinkAttrib(vboLozko1, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoLozko1.LinkAttrib(vboLozko1, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float))); // normals

    vaoLozko1.Unbind();
    vboLozko1.Unbind();
    eboLozko1.Unbind();

    VAO vaoLED;
    VBO vboLED(ledVertices.data(), ledVertices.size() * sizeof(float));
    EBO eboLED(ledIndices.data(), ledIndices.size() * sizeof(unsigned int));

    vaoLED.Bind();
    vboLED.Bind();
    eboLED.Bind();
    vaoLED.LinkAttrib(vboLED, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoLED.LinkAttrib(vboLED, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoLED.LinkAttrib(vboLED, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    vaoLED.Unbind();

    //------------------------krzeslo x2
    std::vector<Segment> krzesloSeg;
    parseFromObj(verticeskrzeslo, indiceskrzeslo, "krzeslo.obj", krzesloSeg, 7.5, 1.6, -3.5, 0.25);
    parseFromObj(verticeskrzeslo, indiceskrzeslo, "krzeslo.obj", krzesloSeg, 5.5, 1.55, -3.5, 0.25);

    rotateVertices(verticeskrzeslo, 0.0f, 90.0f, 0.0f); // np. obrót stołu o 30° wokół Y

    VAO vaokrzeslo;
    VBO vbokrzeslo(verticeskrzeslo.data(), verticeskrzeslo.size() * sizeof(float));
    EBO ebokrzeslo(indiceskrzeslo.data(), indiceskrzeslo.size() * sizeof(unsigned int));

    vaokrzeslo.Bind();
    vbokrzeslo.Bind();
    ebokrzeslo.Bind();
    vaokrzeslo.LinkAttrib(vbokrzeslo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);              // pos
    vaokrzeslo.LinkAttrib(vbokrzeslo, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaokrzeslo.LinkAttrib(vbokrzeslo, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float))); // normals

    vaokrzeslo.Unbind();
    vbokrzeslo.Unbind();
    ebokrzeslo.Unbind();

    //------------------------ladowanie tekstur
 //trzeba sprawdzać czy bliki są w RGB czy RGBA - zmiana na RGBA naprawiła problemygit
    Texture floorTex("floor.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture ceilingTex("ceiling.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture wallTex("wall.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture doorTex("door2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture tableTex("drewno1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    std::unordered_map<std::string, Texture> texs{
    { "szary",  Texture("plastic_szary.png",  GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE) },
    { "table", Texture("drewno1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE) },
    { "posciel", Texture("posciel.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE) },
    { "przescieradlo", Texture("przescieradlo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE) }
    };


  

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        camera.Inputs(window);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Activate();
        glm::mat4 model = glm::mat4(1.0f);
        glm::vec3 lightPos(0.0f, 3.8f, 0.0f); // pozycja lampy
        glm::vec4 lightColor(1.0f, 1.0f, 0.9f, 1.0f); // lekko ciepłe światło

        float ka = 0.4f;
        float kd = 0.6f;
        float ks = 0.2f;
        float shininess = 64.0f; // bardziej rozmyte odbicia


        float t = glfwGetTime();
        glm::vec3 ledColor(
            0.5f * sin(t * 2.0f) + 0.5f,
            0.5f * sin(t * 2.0f + 2.0f) + 0.5f,
            0.5f * sin(t * 2.0f + 4.0f) + 0.5f
        );

        for (int i = 0; i < 8; ++i) {
            glUniform3f(glGetUniformLocation(shader.ID, ("lightPositions[" + std::to_string(i) + "]").c_str()),
                lightPositions[i].x, lightPositions[i].y, lightPositions[i].z);

            glUniform3f(glGetUniformLocation(shader.ID, ("lightColors[" + std::to_string(i) + "]").c_str()),
                ledColor.r, ledColor.g, ledColor.b);  // wszędzie ten sam
        }


        glUniform1f(glGetUniformLocation(shader.ID, "ka"), ka);
        glUniform1f(glGetUniformLocation(shader.ID, "kd"), kd);
        glUniform1f(glGetUniformLocation(shader.ID, "ks"), ks);
        glUniform1f(glGetUniformLocation(shader.ID, "shininess"), shininess);

        glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor.r, lightColor.g, lightColor.b, lightColor.a);
        glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);

        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

        camera.updateMatrix(45.0f, 0.1f, 100.0f);
        camera.Matrix(shader, "camMatrix");

		//-------------------------rysowanie pokoju
        vao.Bind();
        // podłoga
        floorTex.Bind();
        floorTex.texUnit(shader, "tex0", 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(unsigned int)));
        // sufit
        ceilingTex.Bind();
        ceilingTex.texUnit(shader, "tex0", 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)));
        // przednia
        wallTex.Bind();
        wallTex.texUnit(shader, "tex0", 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(unsigned int)));
        // tylna
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(unsigned int)));
        // lewa
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(unsigned int)));
        // prawa
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));

        //drzwi
        doorTex.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(36 * sizeof(unsigned int)));
		//--------------------------rysowanie stolu
        vaoTable.Bind();
        for (auto& s : stolSeg) {
            Texture* tex = nullptr;
            auto it = texs.find(s.material);
            if (it != texs.end()) tex = &it->second;
            else                 tex = &tableTex;    // albo floorTex – cokolwiek domyślnego

            tex->Bind();
            tex->texUnit(shader, "tex0", 0);
            glDrawElements(GL_TRIANGLES, s.count, GL_UNSIGNED_INT, (void*)(s.start * sizeof(unsigned int)));
        }
		//-------------------------rysowanie szafy
		vaoSzafa.Bind();
		for (auto& s : szafaSeg) {
			Texture* tex = nullptr;
			auto it = texs.find(s.material);
			if (it != texs.end()) tex = &it->second;
			else                 tex = &tableTex;    // albo floorTex – cokolwiek domyślnego
			tex->Bind();
			tex->texUnit(shader, "tex0", 0);
			glDrawElements(GL_TRIANGLES, s.count, GL_UNSIGNED_INT, (void*)(s.start * sizeof(unsigned int)));
		}
		//--------------------------rysowanie łóżka
		vaoLozko.Bind();
		for (auto& s : LozkoSeg) {
            Texture* tex = nullptr;
            auto it = texs.find(s.material);
            if (it != texs.end()) tex = &it->second;
            else                 tex = &tableTex;    // albo floorTex – cokolwiek domyślnego
            tex->Bind();
            tex->texUnit(shader, "tex0", 0);
            glDrawElements(GL_TRIANGLES, s.count, GL_UNSIGNED_INT, (void*)(s.start * sizeof(unsigned int)));
        }

        vaoLozko1.Bind();
        for (auto& s : Lozko1Seg) {
            Texture* tex = nullptr;
            auto it = texs.find(s.material);
            if (it != texs.end()) tex = &it->second;
            else                 tex = &tableTex;    // albo floorTex – cokolwiek domyślnego
            tex->Bind();
            tex->texUnit(shader, "tex0", 0);
            glDrawElements(GL_TRIANGLES, s.count, GL_UNSIGNED_INT, (void*)(s.start * sizeof(unsigned int)));
        }
		//--------------------------rysowanie krzesła
		vaokrzeslo.Bind();
		for (auto& s : krzesloSeg) {
			Texture* tex = nullptr;
			auto it = texs.find(s.material);
			if (it != texs.end()) tex = &it->second;
			else                 tex = &tableTex;    // albo floorTex – cokolwiek domyślnego
			tex->Bind();
			tex->texUnit(shader, "tex0", 0);
			glDrawElements(GL_TRIANGLES, s.count, GL_UNSIGNED_INT, (void*)(s.start * sizeof(unsigned int)));
		}


        //------------------------rysowanie swaitla

        ledShader.Activate();
        camera.Matrix(ledShader, "camMatrix");

        vaoLED.Bind();
        for (int i = 0; i < 8; ++i) {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPositions[i]);
            glUniformMatrix4fv(glGetUniformLocation(ledShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

            glm::vec3 brightColor = glm::clamp(ledColor * 1.5f, 0.0f, 1.0f);
            glUniform3f(glGetUniformLocation(ledShader.ID, "ledColor"), brightColor.r, brightColor.g, brightColor.b);


            glDrawElements(GL_TRIANGLES, ledIndices.size(), GL_UNSIGNED_INT, 0);
        }


        // główne białe światło
        glm::vec3 mainLightColor = glm::vec3(1.0f, 0.95f, 0.95f);
        glm::vec3 mainLightPos = glm::vec3(0.0f, 3.8f, 0.0f);

        glUniform3f(glGetUniformLocation(shader.ID, "mainLightColor"), mainLightColor.r, mainLightColor.g, mainLightColor.b);
        glUniform3f(glGetUniformLocation(shader.ID, "mainLightPos"), mainLightPos.x, mainLightPos.y, mainLightPos.z);

        glfwSwapBuffers(window);
    }

    vao.Delete(); vbo.Delete(); ebo.Delete(); shader.Delete();
    floorTex.Delete(); wallTex.Delete(); ceilingTex.Delete(); doorTex.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}