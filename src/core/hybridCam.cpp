// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "hybridCam.h"
#include <GL/glew.h>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/rotate_vector.hpp>

static const double two_pi = 2.0 * glm::pi<double>();
static const double half_pi = glm::half_pi<double>();
static const float gimLockBuffer = std::numeric_limits<float>::epsilon() * 100.0f;

HybridCam::HybridCam()
{

}

void HybridCam::Init(){
    Reset(false);
}

glm::vec3 HybridCam::GetRight() const
{
    return glm::normalize(glm::cross(rLookAt, up));
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
}

void HybridCam::ZoomR(const float& zoom){
    if(orbit){
        orbitDist -= zoom;
        orbitDist = glm::max(orbitDist, 1.0f);
        eye = lookAt - rLookAt * orbitDist;
    }
}
