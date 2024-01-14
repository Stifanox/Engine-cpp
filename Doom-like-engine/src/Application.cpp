#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Exceptions/DefaultOpenGLCall.h"
#include "Exceptions/DefaultFiguresCall.h"
#include <crtdbg.h>
#include <memory>
#include <exception>


#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Core/VertexBuffer.h"
#include "Core/VertexArray.h"
#include "Core/ElementBuffer.h"
#include "Core/Shader.h"
#include "Core/Player.h"

#include "3DObjects/Cube.h"
#include "3DObjects/Cuboid.h"
#include "3DObjects/Pyramid.h"
#include "3DObjects/Figure.h"



float viewportWidth = 800;
float viewportHeight = 800;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 6.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

Player player = Player(cameraPos, cameraFront, cameraUp);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;

//Make it so that the resolution /2 is the init value
float lastX = viewportWidth/2.0f;
float lastY = viewportHeight/2.0f;


float yaw = -90.f;
float pitch;

void processInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W )
        player.moveForward(deltaTime);
    else if (key == GLFW_KEY_S)
        player.moveBackward(deltaTime);
    else if (key == GLFW_KEY_A )
        player.moveLeft(deltaTime);
    else if (key == GLFW_KEY_D )
        player.moveRight(deltaTime);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = .3f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    player.updateCameraFront(yaw, pitch);
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

   

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(viewportWidth, viewportHeight, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, processInput);
    glfwSetCursorPosCallback(window, mouseCallback);


    if (glewInit() != GLEW_OK) {
        std::cout << "Error init glew";
        exit(1);
    };

    std::cout << glGetString(GL_VERSION) << std::endl;

    std::vector<std::unique_ptr<Figure>> allFigures;

    int zPos = 0;
    for (int i = 0; i < 3; i++) {
        for (size_t j = 0; j < 10; j++)
        {
            zPos -= 3;
            try {
                switch (j%3)
                {
                case 0:
                    allFigures.push_back(std::make_unique<Cubiod>(j % 2 == 0 ? 2 : -2, -1, zPos, 1, 3, 1));
                    break;
                case 1:
                    allFigures.push_back(std::make_unique<Cube>(j % 2 == 0 ? 2 : -2, -1, zPos, 1));
                    break;
                case 2:
                    allFigures.push_back(std::make_unique<Pyramid>(j % 2 == 0 ? 2 : -2, -1, zPos, 1, 2));
                    break;
                default:
                    break;
                }
            }
            catch (DefaultFigureCall& ex) {
                std::cout << ex.what();
                exit(1);
            }
            catch (DefaultOpenGLCall& ex) {
                std::cout << ex.what();
                exit(1);
            }
            catch (std::exception& ex) {
                std::cout << ex.what();
                exit(1);
            }
        }
    }
   
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
      
        player.updateViewMatrix();
        glm::mat4 cameraMatrix = player.getViewMatrix();

        for (auto& item : allFigures) {
            item->update(cameraMatrix);
            item->draw();
        }

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        
    }

    for (auto& item : allFigures) {
        item.reset();
    }

    glfwTerminate();
    return 0;
}