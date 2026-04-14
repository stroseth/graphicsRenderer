#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"

/**

    Point of this class: 
        Retrieve projection matrix data + view matrix data
        Construct necessary matrices

    Support different projection and view matrices

*/
class Camera{
    public:
        Camera();
        //Camera(glm::vec3 pos, glm::vec3 origin);

        //View Matrix
        glm::mat4 getViewMatrix();
        //Projection matrices: ortho and perspective
        glm::mat4 getPerspectiveMatrix();
        glm::mat4 getOrthographicMatrix();

        void setPosition(glm::vec3 pos);

        glm::vec3 getPosition() { return m_pos; }
        glm::vec3 getViewDir() { return m_viewDir; }
        glm::vec3 getU() { return m_U; }
        glm::vec3 getW() { return m_W; }

    private:
        glm::vec3 m_pos, m_viewDir;
        glm::vec3 m_U, m_V, m_W;

        float aspectRatio;
        //float left, right, bottom, top, near, far;
};