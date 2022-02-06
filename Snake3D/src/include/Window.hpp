#pragma once
#include "Type.hpp"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

struct Color {
    Color(float value) : r(value), g(value), b(value) {}
    Color(float r, float g, float b) : r(r), g(g), b(b) {}
    float r, g, b;
};

enum FLAGS : uint64 {
    MOUSE_DISABLED = 0x00034003,
};

class Window {
public:
    Window(int width_, int height_, const char *title_, uint64 flags = 0);
    ~Window();

    bool isOpen();
    void pollEvents();
    void clear(const Color &color = Color(0.2f));
    void display();

    void close(bool value);

private:
    bool init(unsigned int flags);

private:
    int m_width, m_height;
    const char *m_title;

    GLFWwindow *m_window;
};