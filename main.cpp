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
	buildRoom(vertices, indices);
	buildBed(vertices, indices);

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

    //trzeba sprawdza� czy bliki s� w RGB czy RGBA - zmiana na RGBA naprawi�a problemygit
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

        // pod�oga
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

        // ��ko blat
        bedTex.Bind();
		bedTex.texUnit(shader, "tex0", 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(42 * sizeof(unsigned int)));

        // nogi ��ka
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(48 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(54 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(60 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(66 * sizeof(unsigned int)));

        glfwSwapBuffers(window);
    }

    vao.Delete(); vbo.Delete(); ebo.Delete(); shader.Delete();
    floorTex.Delete(); wallTex.Delete(); ceilingTex.Delete(); doorTex.Delete(); bedTex.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}