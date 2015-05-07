#include "hybridCam.h"
#include <GL/glew.h>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/rotate_vector.hpp>

static const double two_pi = 2.0 * glm::pi<double>();
static const double half_pi = glm::half_pi<double>();
static const float gimLockBuffer = std::numeric_limits<float>::epsilon() * 100.0f;

HybridCam::HybridCam():
remakeAxis(true),
axisEnds(0),
axisColors(0){}

void HybridCam::Init(){
    Reset(false);
    /*if(axisColors == 0)
    axisColors = new float[18];

    axisColors[0] = 1.0f; axisColors[1] = 0;     axisColors[2] = 0;
    axisColors[3] = 1.0f; axisColors[4] = 0;     axisColors[5] = 0;
    axisColors[6] = 0;    axisColors[7] = 1.0f;  axisColors[8] = 0;
    axisColors[9] = 0;    axisColors[10] = 1.0f; axisColors[11] = 0;
    axisColors[12] = 0;   axisColors[13] = 0;    axisColors[14] = 1.0f;
    axisColors[15] = 0;   axisColors[16] = 0;    axisColors[17] = 1.0f;

    glGenVertexArrays(1, &crosshairLineVAO);
    glGenVertexArrays(1, &crosshairEndVAO);

    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, 18*sizeof(float), 0, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, 18*sizeof(float), axisColors, GL_DYNAMIC_DRAW);

    glBindVertexArray(crosshairLineVAO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glBindVertexArray(crosshairEndVAO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glVertexPointer(3, GL_FLOAT, 6*sizeof(float), (void*)(3*sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glColorPointer(3, GL_FLOAT, 6*sizeof(float), 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    delete  axisColors; axisColors = nullptr;*/
}

void HybridCam::DrawCrosshair(){
    /*if(remakeAxis){
        if(axisEnds == 0)
        axisEnds = new float[18];
        float a = 1.5f;
        //create corners - indices
        axisEnds[0] = lookAt.x-a;	axisEnds[1] = lookAt.y;		axisEnds[2] = lookAt.z;
        axisEnds[3] = lookAt.x+a;	axisEnds[4] = lookAt.y;		axisEnds[5] = lookAt.z;
        axisEnds[6] = lookAt.x;		axisEnds[7] = lookAt.y-a;	axisEnds[8] = lookAt.z;
        axisEnds[9] = lookAt.x;		axisEnds[10] = lookAt.y+a;	axisEnds[11] = lookAt.z;
        axisEnds[12] = lookAt.x;	axisEnds[13] = lookAt.y;	axisEnds[14] = lookAt.z-a;
        axisEnds[15] = lookAt.x;	axisEnds[16] = lookAt.y;	axisEnds[17] = lookAt.z+a;
        remakeAxis = false;
        glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
        glBufferData(GL_ARRAY_BUFFER, 18*sizeof(float), axisEnds, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        delete(axisEnds); axisEnds = 0;
    }

    //enable states
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(crosshairLineVAO);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.0f);
    glDrawArrays(GL_LINES, 0, 6);
    glDisable(GL_LINE_SMOOTH);
    glBindVertexArray(crosshairEndVAO);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(10.0f);
    glDrawArrays(GL_POINTS, 0, 3);
    glDisable(GL_POINT_SMOOTH);
    glBindVertexArray(0);
    ///use this to correct error
    glPointSize(0.01f);
    glBegin(GL_POINTS);
    glColor4f(0,0,0,0);
    glVertex3f(0,0,0);
    glEnd();
    ///

    //disable states
    glDisable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);*/
}

const glm::vec3 &HybridCam::GetRight() const
{
    return glm::normalize(glm::cross(rLookAt, up));
}

void HybridCam::Clear(){
    /*glDeleteBuffers(1,&colorVBO);
    glDeleteBuffers(1,&vertexVBO);
    glDeleteVertexArrays(1,&crosshairEndVAO);
    glDeleteVertexArrays(1,&crosshairLineVAO);*/
}

void HybridCam::Reset(bool orb){
    orbit = orb;
    if (orb)
    {
        orbitDist = 1;
        lookAt = glm::vec3(0,0,0);
        rLookAt = glm::vec3(0,0,-1);
        rotations = glm::vec3(0,0,0);
        eye = lookAt - rLookAt * orbitDist;
        up = glm::vec3(0,1,0);
    }
    else
    {
        eye = glm::vec3(0,0,0);
        rotations = glm::vec3(0,0,0);
        rLookAt = glm::vec3(0,0,-1);
        lookAt = eye + rLookAt;
        up = glm::vec3(0,1,0);
        orbitDist = 0;
    }

    invertedY = true;
}

void HybridCam::MoveA(const glm::vec3 &vec){
    if(orbit){
        lookAt = vec;
        eye = lookAt - rLookAt * orbitDist;
    }
    else{
        eye = vec;
        lookAt = eye + rLookAt;
    }
    remakeAxis = true;
}

void HybridCam::MoveR(const glm::vec3 &vec){
    glm::vec3 right = GetRight();

    if(orbit){
        lookAt += up * (invertedY ? vec.y : -vec.y);
        lookAt += right * vec.x;
        lookAt += rLookAt * vec.z;

        eye = lookAt - rLookAt * orbitDist;
    }
    else{
        eye += up * (invertedY ? vec.y : -vec.y);
        eye += right * vec.x;
        eye += rLookAt * vec.z;

        lookAt = eye + rLookAt;
    }
    remakeAxis = true;
}

void HybridCam::RotateA(const glm::vec3 &vec){
    rotations = glm::vec3(.0,.0,.0);
    RotateR(vec);
}

void HybridCam::RotateR(const glm::vec3 &vec){
    if(orbit){
        if(invertedY)
            rotations += glm::vec3(-vec.x, vec.y, .0);
        else
            rotations += glm::vec3(-vec.x, -vec.y, .0);
    }
    else{
        if(invertedY)
            rotations += glm::vec3(vec.x, -vec.y, .0);
        else
            rotations += glm::vec3(vec.x, vec.y, .0);
    }

    //check overruns
    while (rotations.y > two_pi)
        rotations.y -= two_pi;
    while (rotations.y < 0.0f)
        rotations.y += two_pi;
    if(rotations.x > half_pi - gimLockBuffer)
        rotations.x = (float)(half_pi - gimLockBuffer);
    else if (rotations.x < -half_pi + gimLockBuffer)
        rotations.x = -(float)(half_pi + gimLockBuffer);

    rLookAt = glm::vec3(0,0,-1);
    rLookAt = glm::rotateX(rLookAt, rotations.x);
    rLookAt = glm::rotateY(rLookAt, rotations.y);

    up = glm::vec3(0,1,0);
    up = glm::rotateX(up, rotations.x);
    up = glm::rotateY(up, rotations.y);

    if(orbit)
        eye = lookAt - rLookAt * orbitDist;
    else
        lookAt = eye + rLookAt;
    remakeAxis = true;
}

void HybridCam::SwitchCamMode(bool orbit){
    if(orbit){
        orbitDist = 1;
        lookAt = eye + rLookAt * orbitDist;
    }
    else{
        lookAt = eye + rLookAt;
    }

    this->orbit = orbit;
    remakeAxis = true;
}

void HybridCam::ZoomR(const float& zoom){
    if(orbit){
        orbitDist -= zoom;
        orbitDist = glm::max(orbitDist, 1.0f);
        eye = lookAt - rLookAt * orbitDist;
    }
    remakeAxis = true;
}
