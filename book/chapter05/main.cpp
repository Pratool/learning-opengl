#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <utilities/GlfwWindow.hpp>

#include <iostream>

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWWindow &window)
{
    if (GLFWWindow::KeyInput::press == window.getKeyPress<GLFW_KEY_ESCAPE>())
    {
        window.setShouldClose();
    }
}

int main()
{
    GLFWWindow win({800, 600, "title"});

    glfwMakeContextCurrent(win.get());

    if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD." << std::endl;
        return 1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(win.get(), framebufferSizeCallback);

    while (not win.getShouldClose())
    {
        processInput(win);
        glfwPollEvents();
    }

    return 0;
}
