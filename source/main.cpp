#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Renderer/ShaderProgram.hpp"
#include "Resources/ResourceManager.hpp"

GLfloat points[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f, 
    -0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
    1.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 
    0.f, 0.f, 1.f
};

int g_window_size_x = 640;
int g_window_size_y = 480;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_window_size_x = width;
    g_window_size_y = height;
    glViewport(0,0,g_window_size_x, g_window_size_y);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scanecode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

// void RotatePoints(GLfloat *points, float angle) 
// {
//     double theta = angle * M_PI / 180.0;
    
//     float center_x = (points[0] + points[3] + points[6]) / 3;
//     float center_y = (points[1] + points[4] + points[7]) / 3;

//     for(int it = 0; it < 3; ++it)
//     {
//         float translated_x = points[it * 3] - center_x;
//         float translated_y = points[it * 3 + 1] - center_y;
//         float new_x = translated_x * cos(theta) - translated_y * sin(theta);
//         float new_y = translated_x * sin(theta) + translated_y * cos(theta);

//         points[it * 3] = new_x + center_x;
//         points[it * 3 + 1] = new_y + center_y;
//     }
// }

int main(int argc, char** argv)
{
    char i = 92;

    std::cout << i << std::endl;

    ResourceManager resourceManager(argv[0]);
    
    if (!glfwInit())
    {
        std::cout << "glfw dont init (glfwInit)" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_window_size_x, g_window_size_y, "Tetris ultima", NULL, NULL);
    if (!pWindow)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "Cant load Glad!" << std::endl;
        return -1;
    }

    std::cout << "Rendere: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0.f, 0.f, 0.f, 1.f); 

    std::string  vertexShader; //(vertex_shader);
    std::string fragmentShader; //(fragment_shader);
    Renderer::ShaderProgram shaderProgram(vertexShader, fragmentShader);

    if (!shaderProgram.isCompiled())
    {
        std::cerr << "Cant create shader program!" << std::endl;
        return -1;
    }

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        // RotatePoints(points, 1.f);

        // glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);


        shaderProgram.use();
        glBindVertexArray(vao); 
        glDrawArrays(GL_TRIANGLES, 0, 3);


        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}