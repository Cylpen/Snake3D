#include "Camera.hpp"
#include "Cube.hpp"
#include "Input.hpp"
#include "Shader.hpp"
#include "Window.hpp"

#include <iostream>

#define MAP_SIZE 10.f
bool yUP = true;
bool animation = false;

float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;
glm::vec3 direction(0.0f, 0.0f, 0.0f);

void updateInput();
bool checkCollision(Cube &snake, const glm::vec3 &direction);

int main() {
    Window window(1280, 720, "Project", FLAGS::MOUSE_DISABLED);
    Shader shader("assets/shaders/default.vs", "assets/shaders/default.fs");
    Camera3D camera(glm::vec3(0.0f, 0.0f, 45.0f));
    camera.update(deltaTime);

    Cube snake(glm::vec3(0.0f), 1.f);
    Cube arena(glm::vec3(0.0f), MAP_SIZE, false);

    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 1280.f / 720.f, 0.1f, 100.f);

    shader.bind();
    shader.setMat4fv("uProjection", projection);

    int counter = 0;
    while (window.isOpen()) {
        if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
            window.close(true);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.pollEvents();
        window.clear(Color(0.2f));

        shader.setMat4fv("uView", camera.getViewMatrix());
        if (!animation) {
            updateInput();
            if (counter >= 5) {
                if (!checkCollision(snake, direction))
                    snake.move(direction);
                counter = 0;
            }
        }

        snake.render(shader);
        arena.render(shader);

        window.display();
        counter++;
    }
}

void updateInput() {
    if (Input::isKeySinglePress(GLFW_KEY_SPACE)) yUP = !yUP;
    if (yUP) {
        if (Input::isKeyPressed(GLFW_KEY_UP))
            direction = glm::vec3(0.0f, 1.0f, 0.0f);
        else if (Input::isKeyPressed(GLFW_KEY_DOWN))
            direction = glm::vec3(0.0f, -1.0f, 0.0f);
    } else {
        if (Input::isKeyPressed(GLFW_KEY_UP))
            direction = glm::vec3(0.0f, 0.0f, -1.0f);
        else if (Input::isKeyPressed(GLFW_KEY_DOWN))
            direction = glm::vec3(0.0f, 0.0f, +1.0f);
    }

    if (Input::isKeyPressed(GLFW_KEY_RIGHT))
        direction = glm::vec3(1.0f, 0.0f, 0.0f);
    else if (Input::isKeyPressed(GLFW_KEY_LEFT))
        direction = glm::vec3(-1.0f, 0.0f, 0.0f);

    if (Input::isKeyPressed(GLFW_KEY_S)) direction = glm::vec3(0.0f);
}

bool checkCollision(Cube &snake, const glm::vec3 &direction) {
    if ((snake.getPosition().x + direction.x) >= MAP_SIZE) {
        glm::vec3 newPos(-MAP_SIZE, snake.getPosition().y, snake.getPosition().z);
        snake.setPosition(newPos);
    }
    if ((snake.getPosition().x + direction.x) <= -MAP_SIZE) {
        glm::vec3 newPos(MAP_SIZE, snake.getPosition().y, snake.getPosition().z);
        snake.setPosition(newPos);
    }

    if (yUP) {
        if ((snake.getPosition().y + direction.y) >= MAP_SIZE) {
            glm::vec3 newPos(snake.getPosition().x, -MAP_SIZE, snake.getPosition().z);
            snake.setPosition(newPos);
        }
        if ((snake.getPosition().y + direction.y) <= -MAP_SIZE) {
            glm::vec3 newPos(snake.getPosition().x, MAP_SIZE, snake.getPosition().z);
            snake.setPosition(newPos);
        }
    } else {
        if ((snake.getPosition().z + direction.z) >= MAP_SIZE) {
            glm::vec3 newPos(snake.getPosition().x, snake.getPosition().y, -MAP_SIZE);
            snake.setPosition(newPos);
        }
        if ((snake.getPosition().z + direction.z) <= -MAP_SIZE) {
            glm::vec3 newPos(snake.getPosition().x, snake.getPosition().y, MAP_SIZE);
            snake.setPosition(newPos);
        }
    }
    return false;
}