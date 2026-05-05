#define TINYOBJLOADER_IMPLEMENTATION

#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "tiny_obj_loader.h"

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

class Vertex {
public:
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

int CheckGLErrors(const char *s)
{
    int errCount = 0;
    return errCount;
}

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
        LOAD OBJ FILE
    ***************************************/
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warnings;
    std::string errors;
    std::string filename = "cat.obj";
    std::string dir = "models";

    bool success = tinyobj::LoadObj(&attributes, &shapes, &materials, &warnings, &errors, filename.c_str(), dir.c_str());
    std::vector<Vertex> vertices;

    if (!success) std::cout << "FAILED TO LOAD MODEL \n";
    if (success) std::cout << "Loaded model I think \n";

    //Decompression
    for (int i = 0; i < shapes.size(); i++) {
        tinyobj::shape_t &shape = shapes.at(i);
        tinyobj::mesh_t &mesh = shape.mesh;
        for (int j = 0; j < mesh.indices.size(); j++) {
            tinyobj::index_t i = mesh.indices.at(j);
            glm::vec3 position = {
                attributes.vertices[i.vertex_index * 3],
                attributes.vertices[i.vertex_index * 3 + 1],
                attributes.vertices[i.vertex_index * 3 + 2]
            };
            glm::vec3 normal = {
                attributes.normals[i.normal_index * 3],
                attributes.normals[i.normal_index * 3 + 1],
                attributes.normals[i.normal_index * 3 + 2]
            };
            glm::vec2 texCoord = {
                attributes.texcoords[i.texcoord_index * 2],
                attributes.texcoords[i.texcoord_index * 2 + 1],
            };
        // Not gonna care about texCoord right now.
            Vertex vert = { position, normal, texCoord };
            vertices.push_back(vert);
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
        CREATE A VERTEX BUFFER OBJECT (OBJ Scene)
    ***************************************/
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *) (sizeof(float) * 3));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *) (sizeof(float) * 6));

    /**************************************  
        CREATE A VERTEX BUFFER OBJECT (TRIANGLE)
    ***************************************/
   
    /* create vertex array buffer to hold triangle data
    GLuint m_triangleVBO[1], m_VAO;
    glGenBuffers(1, m_triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

    //triangle data that will be copied to GPU mem
    std::vector<float> host_VertexBuffer { -3.0f, -3.0f, 0.0f, 0.0f, 0.0f, 1.0f, //v0 
                                            3.0f, -3.0f, 0.0f, 0.0f, 0.0f, 1.0f, //v1 
                                            0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 1.0f }; //v2 
    int numBytes = host_VertexBuffer.size() * sizeof(float);

    //copy numBytes from host_VertexBuffer to the GPU and store in currently bound VBO
    glBufferData(GL_ARRAY_BUFFER, numBytes, host_VertexBuffer.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    host_VertexBuffer.clear();    //once copied we can clear host data

    /**************************************  
        CREATE A VERTEX ARRAY OBJECT
            (VAOs are mappings between VBO
            data and attribute locations
            that can be used in a shader)
    **************************************
    
    //create VAO mapping attributes in vertex buffer to different location attributes for shaders
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    //VAO details
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

    //attribute 0: position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1); 

    glBindVertexArray(0); */ 

    /**************************************  
        CREATE SHADERS
    ***************************************/
 
    //create shader using Dr. Pete's GLSLObject class
    sivelab::GLSLObject shader;
    shader.addShader("vertexShader_PrepForPerFragment.glsl", sivelab::GLSLObject::VERTEX_SHADER);
    shader.addShader("fragmentShader_blinnPhong.glsl", sivelab::GLSLObject::FRAGMENT_SHADER);
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;

    /* Loop until the user closes the window */
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

        //glBindVertexArray(m_VAO);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glBindVertexArray(0);
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

        /* Rotating triangle
        rot = rot + glm::radians(.001f);
        modelMatrix = glm::rotate(modelMatrix, rot, glm::vec3(0,1,0)); */
        
    }
  
    glfwTerminate();
    return 0;
}