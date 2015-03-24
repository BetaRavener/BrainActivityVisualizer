/*
* UniShader-Demo - Showcase programs for UniShader Interface
* Copyright (c) 2011-2013 Ivan Sevcik - ivan-sevcik@hotmail.com
*
* This software is provided 'as-is', without any express or
* implied warranty. In no event will the authors be held
* liable for any damages arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute
* it freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented;
*    you must not claim that you wrote the original software.
*    If you use this software in a product, an acknowledgment
*    in the product documentation would be appreciated but
*    is not required.
*
* 2. Altered source versions must be plainly marked as such,
*    and must not be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any
*    source distribution.
*/

#pragma once
#ifndef HYBRID_CAM_H
#define HYBRID_CAM_H

#include <limits>
#include <glm/vec3.hpp>

class HybridCam{
public:
	HybridCam();
	void Init();
	void Clear();
	void DrawCrosshair();
    const glm::vec3 &GetEye() const {return eye;}
    const glm::vec3 &GetLookAt() const {return lookAt;}
    const glm::vec3 &GetUp() const {return up;}
    float getZoom() const {return orbitDist;}
	bool IsOrbiting() const { return orbit; }
    void MoveA(const glm::vec3 &vec);
    void MoveR(const glm::vec3 &vec);
    void RotateA(const glm::vec3 &vec);
    void RotateR(const glm::vec3 &vec);
	void InvertY(){invertedY = !invertedY;}
	void SwitchCamMode(bool orbit);
	void ZoomR(const float& zoom);
    void Reset(bool orb);
protected:
    glm::vec3 eye, lookAt, up;
    bool invertedY, orbit;
	float orbitDist;
    glm::vec3 rLookAt;
    glm::vec3 rotations;

	//croshair variables
	bool remakeAxis;
	float *axisColors;
	float *axisEnds;
    unsigned int colorVBO, vertexVBO;
    unsigned int crosshairEndVAO, crosshairLineVAO;
};

#endif
