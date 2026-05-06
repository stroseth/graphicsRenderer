#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "png++/png.hpp"

#include "GLSL.h"

#include "Camera.h"

float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 500.0f, lastY = 500.0f;
bool firstMouse = true;

float sensitivity = 0.1f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
}

int CheckGLErrors(const char *s)
{
    int errCount = 0;
    return errCount;
}

struct VertexData{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

int main(void)
{
    /* Initialize the library */
    if (!glfwInit()) {
        exit (-1);
    }
    // throw std::runtime_error("Error! initialization of glfw failed!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /**************** Create a windowed mode window and its OpenGL context */
    int winWidth = 1000;
    float aspectRatio = 1.0; // 16.0 / 9.0; // winWidth / (float)winHeight;
    int winHeight = winWidth / aspectRatio;
    
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "GLFW Example", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW did not create a window!" << std::endl;
        
        glfwTerminate();
        return -1;
    }

    /************ Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err=glewInit();
    if(err != GLEW_OK) {
        std::cerr <<"GLEW Error! glewInit failed, exiting."<< std::endl;
        exit(EXIT_FAILURE);
    }

    const GLubyte* renderer = glGetString (GL_RENDERER);
    const GLubyte* version = glGetString (GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0);

    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    /**************************************  
        TEXTURE MAPPING (FILE LOAD)
    ****************************************/
    std::string texFilename = "textureAtlas.png";
    std::cout << "Reading texture map data from file: " << texFilename << std::endl;
    png::image<png::rgb_pixel> texPNGImage;
    texPNGImage.read(texFilename);

    int pngWidth = texPNGImage.get_width();
    int pngHeight = texPNGImage.get_height();

    std::vector<float> texData(pngHeight * pngWidth * 3);

    size_t idx = 0;
    for (size_t row = 0; row < pngHeight; ++row){
        for (size_t col = 0; col < pngWidth; ++col){
            png::rgb_pixel pixel = texPNGImage[pngHeight - row - 1][col]; //flip of height here
            texData[idx++] = pixel.red / 255.0f;
            texData[idx++] = pixel.green / 255.0f;
            texData[idx++] = pixel.blue / 255.0f;
        }
    }

    /**************************************  
        CREATE MODEL MATRIX (Transforms)
    ****************************************/

    //GLM Model Matrix:
    glm::mat4 modelMatrix = glm::mat4(1.0); //Identity matrix
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 1.0f, 0.0f)); //translate matrix
    float rot = glm::radians(0.0f);
    //rotation
    modelMatrix = glm::rotate(modelMatrix, rot, glm::vec3(0,1,0));
    //glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(sx,sy,sz));

    // *********************** Couts version to console
    GLint major_version;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    std::cout << "GL_MAJOR_VERSION: " << major_version << std::endl;

    /**************************************  
        CREATE A VERTEX BUFFER OBJECT (new struct)
    ***************************************/

    GLuint m_triangleVBO[1], m_VAO;
    glGenBuffers(1, m_triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

    glm::vec3 triNormal = glm::vec3(0.0f, 0.0f, 1.0f);

    VertexData v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11;

    v0.pos = glm::vec3(-3.0f, -3.0f, 0.0f);
    v0.normal = triNormal;
    v0.texCoord = glm::vec2(0.0f, 0.5f);

    v1.pos = glm::vec3(3.0f, -3.0f, 0.0f);
    v1.normal = triNormal;
    v1.texCoord = glm::vec2(0.5f, 0.5f);

    v2.pos = glm::vec3(-3.0f, 3.0f, 0.0f);
    v2.normal = triNormal;
    v2.texCoord = glm::vec2(0.0f, 1.0f);

    //triangle2
    v3.pos = v1.pos;
    v3.normal = v1.normal;
    v3.texCoord = v1.texCoord;

    v4.pos = glm::vec3(3.0f, 3.0f, 0.0f);
    v4.normal = triNormal;
    v4.texCoord = glm::vec2(0.5f, 1.0f);

    v5.pos = v2.pos;
    v5.normal = v2.normal;
    v5.texCoord = v2.texCoord;

    ////side 2 of the square
    v6.pos = glm::vec3(3.0f, -3.0f, 0.0f);
    v6.normal = triNormal;
    v6.texCoord = v1.texCoord;

    v7.pos = glm::vec3(3.0f, -3.0f, -6.0f);
    v7.normal = triNormal;
    v7.texCoord = v6.texCoord + glm::vec2(0.5f, 0.0f);

    v8.pos = glm::vec3(3.0f, 3.0f, 0.0f);
    v8.normal = triNormal;
    v8.texCoord = v6.texCoord + glm::vec2(0.0f, 0.5f);

    //triangle2
    v9.pos = v7.pos;
    v9.normal = v7.normal;
    v9.texCoord = v7.texCoord;

    v10.pos = glm::vec3(3.0f, 3.0f, -6.0f);
    v10.normal = triNormal;
    v10.texCoord = glm::vec2(1.0f, 1.0f);

    v11.pos = v8.pos;
    v11.normal = v8.normal;
    v11.texCoord = v8.texCoord;

    std::vector<VertexData> modelData = {v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11};

    int numBytes = modelData.size() * sizeof(VertexData);
    glBufferData(GL_ARRAY_BUFFER, numBytes, modelData.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    int mdSize = modelData.size();
    modelData.clear();    //can clear host data now

    /**************************************  
        CREATE A VERTEX ARRAY OBJECT
            (VAOs are mappings between VBO
            data and attribute locations
            that can be used in a shader)
    ***************************************/
    
    //create VAO mapping attributes in vertex buffer to different location attributes for shaders
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    //VAO details
    //glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

    //attribute 0: position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), 0); //change to 8 offset when texture included

    //attribute 1: normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (const GLvoid *)12);

    //attribute 2: texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (const GLvoid *)24);

    glBindVertexArray(0);

    /**************************************  
        LOAD TEXTURE INTO DEVICE MEMORY
    ***************************************/
    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pngWidth, pngHeight, 0, GL_RGB, GL_FLOAT, texData.data());
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glActiveTexture(GL_TEXTURE0);

    /**************************************  
        CREATE SHADERS
    ***************************************/
 
    //create shader using Dr. Pete's GLSLObject class
    sivelab::GLSLObject shader;
    shader.addShader("vertexShader_PrepForPerFragment.glsl", sivelab::GLSLObject::VERTEX_SHADER);
    shader.addShader("fragmentShader_flatTexture.glsl", sivelab::GLSLObject::FRAGMENT_SHADER);
    shader.createProgram();

    GLuint projMatrixID, viewMatrixID, modelMatrixID, normalMatrixID;
    projMatrixID = shader.createUniform("projMatrix");
    viewMatrixID = shader.createUniform("viewMatrix");
    modelMatrixID = shader.createUniform("modelMatrix");
    normalMatrixID = shader.createUniform("normalMatrix");

    // Create lights
    GLuint lightPosWorldID = shader.createUniform("lightPosWorld");
    GLuint diffuseComponentID = shader.createUniform("diffuseComponent");
    GLuint specularComponentID = shader.createUniform("specularComponent");
    GLuint shininessID = shader.createUniform("shininess");

    // Create Camera
    Camera cam;
    glm::mat4 M_proj = cam.getPerspectiveMatrix();

    //create texture
    GLuint texUnitID = shader.createUniform("myTexture");

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;

    /*********************************************************  
            RENDER LOOP!!! Until user closes window
    *********************************************************/
    while (!glfwWindowShouldClose(window))
    {
        endFrameTime = glfwGetTime();
        timeDiff = endFrameTime - startFrameTime;
        startFrameTime = glfwGetTime();

        // Clear the window's buffer (or clear the screen to our
        // background color)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        glm::vec3 m_W = -glm::normalize(front);
        glm::vec3 m_U = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), m_W));
        glm::vec3 m_V = glm::normalize(glm::cross(m_W, m_U));

        cam.setUVW(m_U, m_V, m_W);

        //create view matrix from camera data
        glm::mat4 M_view = cam.getViewMatrix();

        /* Render your objects here */
        shader.activate();

        glm::vec4 lightPosition(1.0f, 0.9f, 2.0f, 1.0f);
        glm::vec3 diffuseComponent(1.0f, 0.0f, 1.0f);
        glm::vec3 specularComponent(1.0f, 1.0f, 1.0f);
        
        glUniform4fv(lightPosWorldID, 1, glm::value_ptr(lightPosition));
        glUniform3fv(diffuseComponentID, 1, glm::value_ptr(diffuseComponent));
        glUniform3fv(specularComponentID, 1, glm::value_ptr(specularComponent));
        glUniform1f(shininessID, 32.0f);

        glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelMatrix));

        //copy view and proj matrices from host to device
        glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr(M_proj));
        glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr(M_view));
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(normalMatrixID, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        //Create textures

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texID);
        glUniform1f(texUnitID, 0);

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, mdSize);
        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, 0);
        
        shader.deactivate();

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        
            // ************** Moving camera support!
        float moveRatePerFrame = 0.05;
        if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS) {
            cam.setPosition(cam.getPosition() + -cam.getW() * moveRatePerFrame);
        }
        if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS) {
            cam.setPosition(cam.getPosition() - cam.getU() * moveRatePerFrame);

        }
        if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS) {
            cam.setPosition(cam.getPosition() + cam.getW() * moveRatePerFrame);
        }
        if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS) {
            cam.setPosition(cam.getPosition() + cam.getU() * moveRatePerFrame);
        }
        if (glfwGetKey( window, GLFW_KEY_T ) == GLFW_PRESS) {
            std::cout << "fps: " << 1.0/timeDiff << std::endl;
        }
        if (glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
            cam.setPosition(cam.getPosition() + cam.getV() * moveRatePerFrame);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
            cam.setPosition(cam.getPosition() - cam.getV() * moveRatePerFrame);
        }

        // Rotating triangle
        //rot = rot + glm::radians(.001f);
        //modelMatrix = glm::rotate(modelMatrix, rot, glm::vec3(0,1,0)); 
        
    }
  
    glfwTerminate();
    return 0;
}