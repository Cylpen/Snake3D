#include "Cube.hpp"
#include "Shader.hpp"

#include <GLAD/glad.h>
#include <GLM/gtc/matrix_transform.hpp>
#include <iostream>

// clang-format off
    const float vertices[] = {
        // front
        -1.0, -1.0,  1.0, // Bottom left
         1.0, -1.0,  1.0, // Bottom right
         1.0,  1.0,  1.0, // Top right
        -1.0,  1.0,  1.0, // Top left

        // back
        -1.0, -1.0, -1.0, // Bottom left
         1.0, -1.0, -1.0, // Bottom right
         1.0,  1.0, -1.0, // Top right
        -1.0,  1.0, -1.0  // Top left
    };

    const unsigned int triangleIDX[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

    const unsigned int lineIDX[] = {
        0, 1, 0, 3, 3, 2, 1, 2, // Front
        4, 5, 4, 7, 7, 6, 5, 6, // Back
        0, 4, 1, 5, 2, 6, 3, 7
    };

// clang-format on

Cube::Cube(const glm::vec3 &position, const float &scale, bool fill) : m_position(position), m_scale(scale), m_fill(fill) {
    m_model = glm::mat4(1.0f);
    m_model = glm::scale(m_model, glm::vec3(scale));
    m_model = glm::translate(m_model, m_position);

    glLineWidth(1.f);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangleIDX) + sizeof(lineIDX), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(triangleIDX), triangleIDX);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangleIDX), sizeof(lineIDX), lineIDX);

    glBindVertexArray(0);
}

Cube::~Cube() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
}

void Cube::render(Shader &shader) {
    shader.setMat4fv("uModel", m_model);
    glBindVertexArray(m_vao);
    if (m_fill)
        glDrawElements(GL_TRIANGLES, sizeof(triangleIDX) / sizeof(triangleIDX[0]), GL_UNSIGNED_INT, 0);
    else
        glDrawElements(GL_LINES, sizeof(lineIDX) / sizeof(lineIDX[0]), GL_UNSIGNED_INT, (void *)(sizeof(triangleIDX)));
}

void Cube::move(const glm::vec3 &direction) {
    m_position += direction;
    m_model = glm::translate(m_model, direction);
}

void Cube::scale(const float &scale) {
    m_scale = scale;
    m_model = glm::scale(m_model, glm::vec3(scale));
}

void Cube::setPosition(glm::vec3 &position) {
    m_position = position;
    m_model = glm::mat4(1.0f);
    m_model = glm::scale(m_model, glm::vec3(m_scale));
    m_model = glm::translate(m_model, m_position);
}
