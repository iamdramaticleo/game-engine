#include "glfw/public.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <glfw/platform.hpp>

int main()
{
    glfw::Platform platform;

    platform.init();

    GLFWwindow* window = glfwCreateWindow(400, 400, "English 日本語 русский язык 官話", nullptr);
    if (!window)
    {
        platform.release();

        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        platform.update();
    }

    platform.release();

    return EXIT_SUCCESS;
}
