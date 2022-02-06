#pragma once
#include <GLM/glm.hpp>

class Shader;

class Cube {
public:
    Cube(const glm::vec3 &position, const float &scale, bool fill = true);
    ~Cube();

    void render(Shader &shader);

    void move(const glm::vec3 &direction);
    void scale(const float &scale);

    // Getters & setters
    void setPosition(glm::vec3 &position);

    glm::vec3 getPosition() const { return m_position; }

private:
    unsigned int m_vao, m_vbo, m_ebo;
    glm::vec3 m_position;
    float m_scale;
    glm::mat4 m_model;
    bool m_fill;
};