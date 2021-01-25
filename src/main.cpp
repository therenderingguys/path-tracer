#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

int WINDOW_WIDTH  = 640;
int WINDOW_HEIGHT = 480;
std::string title = "Test";


void draw() {
}

void update_loop(GLFWwindow* window) {
    glViewport( 0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 1 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    while (!glfwWindowShouldClose(window)) {
        glClear( GL_COLOR_BUFFER_BIT );
        draw();
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char* argv[]) {
    
    GLFWwindow* window;
    if (glfwInit() != GL_TRUE) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title.c_str(), nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        std::cerr << "Failed to initialize GLFW Window!" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    update_loop(window);

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}