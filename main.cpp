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

const unsigned int width = 1280;
const unsigned int height = 720;

//ustawienie startowej pozycji kamery na srodek pokoju
Camera camera(width, height, glm::vec3(0.0f, 1.5f, -4.0f));



int main() {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> vertices1;
    std::vector<unsigned int> indices1;
	buildRoom(vertices, indices);
    //uwaga tutaj jest nieco inny uklad wspolrzednych - tak jakbys narsowa³ sb wykres widz¹c przed kamer¹
    //x - pozioma, y - pionowa, z - oddalenie
	buildBed(vertices, indices, 3.61f, 0.f, 2.5f, 1, 1.0f, 0.75f);
    buildBed(vertices, indices, 3.61f, 0.f, -2.5f, 1, 1.0f, 0.75f);


    int num = 0;
    //parseFromObj(vertices, indices, "stol.obj", num); // <- œcie¿ka do twojego pliku
    parseFromObj(vertices1, indices1, "stol.obj", num); // <- œcie¿ka do twojego pliku

	std::cout << "Vertices from OBJ file:" << std::endl;
	for (int i = 0; i < vertices1.size(); i += 5) {
        std::cout << vertices1[i] << " ";
        std::cout << vertices1[i+1] << " ";
        std::cout << vertices1[i+2] << " ";
        std::cout << vertices1[i+3] << " ";
        std::cout << vertices1[i+4] << std::endl;
	}
    std::cout << "Indices from OBJ file:" << std::endl;

    for (int i = 0; i < indices1.size(); i += 6) {
        std::cout << indices1[i] << " ";
        std::cout << indices1[i + 1] << " ";
        std::cout << indices1[i + 2] << " ";
        std::cout << indices1[i + 3] << " ";
        std::cout << indices1[i + 4] << " ";
        std::cout << indices1[i + 5] << std::endl;
    }
	std::cout << "Number of indices: " << num << std::endl;

    
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

    Shader shader("default.vert", "default.frag");
    VAO vao;
    vao.Bind();

    VBO vbo(vertices.data(), vertices.size() * sizeof(float));
    EBO ebo(indices.data(), indices.size() * sizeof(unsigned int));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.Unbind(); vbo.Unbind(); ebo.Unbind();

    //trzeba sprawdzaæ czy bliki s¹ w RGB czy RGBA - zmiana na RGBA naprawi³a problemygit
    Texture floorTex("floor.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture ceilingTex("ceiling.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture wallTex("wall.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture doorTex("door.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture bedTex("bed.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture tableTex("drewno.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    // po wczytaniu sto³u:
    VAO vaoTable;
    VBO vboTable(vertices1.data(), vertices1.size() * sizeof(float));
    EBO eboTable(indices1.data(), indices1.size() * sizeof(unsigned int));


    // po utworzeniu vaoTable, vboTable, eboTable:
    vaoTable.Bind();
    vboTable.Bind();
    eboTable.Bind();
    // skonfiguruj dok³adnie tak samo jak dla g³ównego VAO:
    vaoTable.LinkAttrib(vboTable, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vaoTable.LinkAttrib(vboTable, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // odwi¹¿:
    vaoTable.Unbind();
    vboTable.Unbind();
    eboTable.Unbind();

    // skonfiguruj atrybuty tak samo jak dla pokoju


    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        camera.Inputs(window);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Activate();
        camera.Matrix(shader, "camMatrix");
        camera.updateMatrix(45.0f, 0.1f, 100.0f);
        vao.Bind();

        // pod³oga
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

        // ³ó¿ko blat 
        bedTex.Bind();
		bedTex.texUnit(shader, "tex0", 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(42 * sizeof(unsigned int)));

        // nogi ³ó¿ka
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(48 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(54 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(60 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(66 * sizeof(unsigned int)));

        // ³ó¿ko blat 
        bedTex.Bind();
        bedTex.texUnit(shader, "tex0", 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(72 * sizeof(unsigned int)));

        // nogi ³ó¿ka
        
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, (void*)(96 * sizeof(unsigned int)));
        
        //stol
        vaoTable.Bind();
        tableTex.Bind(); tableTex.texUnit(shader, "tex0", 0);
        glDrawElements(GL_TRIANGLES, indices1.size(), GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
    }

    vao.Delete(); vbo.Delete(); ebo.Delete(); shader.Delete();
    floorTex.Delete(); wallTex.Delete(); ceilingTex.Delete(); doorTex.Delete(); bedTex.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}