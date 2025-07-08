#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

int main(void)
{
       /* Initialize the library */
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

    glClearColor(255.f, 255.f, 0.f, 255.f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}