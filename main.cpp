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
    std::vector<float> verticesStol;
    std::vector<unsigned int> indicesStol;
	buildRoom(vertices, indices);
       
    //uwaga tutaj jest nieco inny uklad wspolrzednych - tak jakbys narsowa³ sb wykres widz¹c przed kamer¹
    //x - pozioma, y - pionowa, z - oddalenie
    //uwaga tutaj jest nieco inny uklad wspolrzednych - tak jakbys narsował sb wykres widząc przed kamerą
	buildRoom(vertices, indices);
    //uwaga tutaj jest nieco inny uklad wspolrzednych - tak jakbys narsowa� sb wykres widz�c przed kamer�
    //x - pozioma, y - pionowa, z - oddalenie
	buildBed(vertices, indices, 3.61f, 0.f, 2.5f, 1, 1.0f, 0.75f);
    buildBed(vertices, indices, 3.61f, 0.f, -2.5f, 1, 1.0f, 0.75f);


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
    VAO vao;
    vao.Bind();

    VBO vbo(vertices.data(), vertices.size() * sizeof(float));
    EBO ebo(indices.data(), indices.size() * sizeof(unsigned int));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);               // pozycja
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // tekstura
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float))); // normalne


    vao.Unbind(); vbo.Unbind(); ebo.Unbind();


    //------------------------stol
    int inds_stol_liczba = 0;
    parseFromObj(verticesStol, indicesStol, "stol.obj", inds_stol_liczba);

    std::cout << "Vertices from OBJ file:" << std::endl;
    for (int i = 0; i < verticesStol.size(); i += 5) {
        std::cout << verticesStol[i] << " ";
        std::cout << verticesStol[i + 1] << " ";
        std::cout << verticesStol[i + 2] << " ";
        std::cout << verticesStol[i + 3] << " ";
        std::cout << verticesStol[i + 4] << std::endl;
    }
    std::cout << "Indices from OBJ file:" << std::endl;

    for (int i = 0; i < indicesStol.size(); i += 6) {
        std::cout << indicesStol[i] << " ";
        std::cout << indicesStol[i + 1] << " ";
        std::cout << indicesStol[i + 2] << " ";
        std::cout << indicesStol[i + 3] << " ";
        std::cout << indicesStol[i + 4] << " ";
        std::cout << indicesStol[i + 5] << std::endl;
    }
    std::cout << "Number of indices: " << inds_stol_liczba << std::endl;


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


    //------------------------ladowanie tekstur
    //trzeba sprawdzać czy bliki są w RGB czy RGBA - zmiana na RGBA naprawiła problemygit
    Texture floorTex("floor.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture ceilingTex("ceiling.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture wallTex("wall.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture doorTex("door.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture bedTex("bed.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
   	Texture tableTex("drewno.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);


    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        camera.Inputs(window);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Activate();
        glm::mat4 model = glm::mat4(1.0f);
        glm::vec3 lightPos(0.0f, 3.8f, 0.0f); // pozycja lampy
        glm::vec4 lightColor(1.0f, 1.0f, 0.9f, 1.0f); // lekko ciepłe światło
        glm::vec4 lightColor(1.0f, 1.0f, 0.9f, 1.0f); // lekko ciep�e �wiat�o

        float ka = 0.2f;
        float kd = 1.0f;
        float ks = 0.5f;
        float shininess = 32.0f;

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

        // łóżko blat 
        bedTex.Bind();
		bedTex.texUnit(shader, "tex0", 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(42 * sizeof(unsigned int)));

        // nogi łóżka
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(48 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(54 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(60 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(66 * sizeof(unsigned int)));

        // łóżko blat 
        bedTex.Bind();
        bedTex.texUnit(shader, "tex0", 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(72 * sizeof(unsigned int)));

        // nogi łóżka
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(78 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(84 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(90 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(96 * sizeof(unsigned int)));

        //stol
        vaoTable.Bind();
        tableTex.Bind(); tableTex.texUnit(shader, "tex0", 0);
        glUniform1f(glGetUniformLocation(shader.ID, "kd"), 1.0f);
        glUniform1f(glGetUniformLocation(shader.ID, "ks"), 0.0f);
        glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), 0, 0, 0);

        glDrawElements(GL_TRIANGLES, indicesStol.size(), GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
    }

    vao.Delete(); vbo.Delete(); ebo.Delete(); shader.Delete();
    floorTex.Delete(); wallTex.Delete(); ceilingTex.Delete(); doorTex.Delete(); bedTex.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}