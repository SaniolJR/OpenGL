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

const unsigned int width = 1280;
const unsigned int height = 720;

//ustawienie startowej pozycji kamery na srodek pokoju
Camera camera(width, height, glm::vec3(0.0f, 1.5f, -4.0f));

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
    8, 9,10, 8,10,11,       // tyl
    12,13,14,12,14,15,     // lewa
    16,17,18,16,18,19,     // prawa
    20,21,22,20,22,23,     // drzwi
    24,25,26,24,26,27,     // lozko
    28,29,30,28,30,31,     // noga 1
    32,33,34,32,34,35,     // noga 2
    36,37,38,36,38,39,     // noga 3
    40,41,42,40,42,43      // noga 4
};


int main() {
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

    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.Unbind(); vbo.Unbind(); ebo.Unbind();

    //trzeba sprawdzaæ czy bliki s¹ w RGB czy RGBA - zmiana na RGBA naprawi³a problemy
    Texture floorTex("floor.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture ceilingTex("ceiling.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture wallTex("wall.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture doorTex("door.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture bedTex("bed.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

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

        // tylna
        wallTex.Bind();
		wallTex.texUnit(shader, "tex0", 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(unsigned int)));

        // lewa
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(unsigned int)));

        // prawa
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(unsigned int)));

        // drzwi
        doorTex.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));

        // ³ó¿ko blat
        bedTex.Bind();
		bedTex.texUnit(shader, "tex0", 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(36 * sizeof(unsigned int)));

        // nogi ³ó¿ka
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(42 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(48 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(54 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(60 * sizeof(unsigned int)));

        glfwSwapBuffers(window);
    }

    vao.Delete(); vbo.Delete(); ebo.Delete(); shader.Delete();
    floorTex.Delete(); wallTex.Delete(); ceilingTex.Delete(); doorTex.Delete(); bedTex.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}