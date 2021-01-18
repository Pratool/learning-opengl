#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

float vertices[] = {
     0.5F,   0.5F,  0.0F,
     0.5F,  -0.5F,  0.0F,
    -0.5F,  -0.5F,  0.0F,
    -0.5F,   0.5F,  0.0F
};
unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0F);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "  FragColor = vec4(1.0F, 0.5F, 0.2F, 1.0F);\n"
    "}\0";

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    std::cerr << "MIT 6.837 Assignment 0 solution." << std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(360, 360, "6.837 Assignment 0", nullptr, nullptr);
    if (nullptr == window)
    {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD." << std::endl;
        glfwTerminate();
        return 1;
    }
    glViewport(0, 0, 360, 360);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);


    int shaderCompileSuccess;
    char shaderInfoLog[512];

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCompileSuccess);
    if (not static_cast<bool>(shaderCompileSuccess))
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, shaderInfoLog);
        std::cerr << "Failed to compile vertex shader." << std::endl
                  << shaderInfoLog << std::endl;
    }


    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shaderCompileSuccess);
    if (not static_cast<bool>(shaderCompileSuccess))
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, shaderInfoLog);
        std::cerr << "Failed to compile fragment shader." << std::endl
                  << shaderInfoLog << std::endl;
    }


    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderCompileSuccess);
    if (not static_cast<bool>(shaderCompileSuccess))
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, shaderInfoLog);
        std::cerr << "Failed to link shader program." << std::endl
                  << shaderInfoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);


    while (not glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
