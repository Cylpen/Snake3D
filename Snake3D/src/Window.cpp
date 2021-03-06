#include "Window.hpp"
#include "Input.hpp"

#include <iostream>

Window::Window(int width_, int height_, const char *title_, uint64 flags)
    : m_width(width_), m_height(height_), m_title(title_) {
    if (!init(flags)) {
        std::cout << "Failed to initialize!" << std::endl;
    }
}

Window::~Window() {
}

bool Window::init(unsigned int flags) {
    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(m_width, m_height, m_title, 0, 0);
    if (!m_window) {
        return false;
    }
    glfwMakeContextCurrent(m_window);

    if (flags & FLAGS::MOUSE_DISABLED)
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(m_window, Input::framebuffer_size_callback);

    glfwSetKeyCallback(m_window, Input::key_callback);
    glfwSetMouseButtonCallback(m_window, Input::mouse_button_callback);
    glfwSetCursorPosCallback(m_window, Input::cursor_position_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    return true;
}

bool Window::isOpen() {
    return !glfwWindowShouldClose(m_window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::clear(const Color &color) {
    glClearColor(color.r, color.g, color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::display() {
    glfwSwapBuffers(m_window);
}

void Window::close(bool value) {
    glfwSetWindowShouldClose(m_window, value);
}
