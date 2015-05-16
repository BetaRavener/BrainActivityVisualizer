// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#pragma once
#ifndef HYBRID_CAM_H
#define HYBRID_CAM_H

#include <limits>
#include <glm/vec3.hpp>

/**
 * @brief The HybridCam class represents a camera for a scene and allows basic operations
 * such as translation and rotation. These operations may be done relative to the camera
 * position (freeform) or relative to the camera focus point (orbital), therefore hybrid.
 */
class HybridCam{
public:
	HybridCam();

    /**
     * @brief Initializes the class before usage.
     */
    void Init();

    /**
     * @brief Getter.
     * @return The position of the camera.
     */
    glm::vec3 GetEye() const {return eye;}

    /**
     * @brief Getter.
     * @return The camera focus point.
     */
    glm::vec3 GetLookAt() const {return lookAt;}

    /**
     * @brief Gettter.
     * @return The vector pointing up from the camera.
     */
    glm::vec3 GetUp() const {return up;}

    /**
     * @brief Getter.
     * @return The vector pointing right from the camera.
     */
    glm::vec3 GetRight() const;

    /**
     * @brief Getter.
     * @return Ammount of zoom (orbital distance in orbiting mode).
     */
    float getZoom() const {return orbitDist;}

    /**
     * @brief Getter.
     * @return True if the camera is orbiting.
     */
	bool IsOrbiting() const { return orbit; }

    /**
     * @brief Moves camera into position (absolute vector).
     * @param vec Position where the camera will be moved.
     */
    void MoveA(const glm::vec3 &vec);

    /**
     * @brief Moves camera by a relative vector.
     * @param vec Vector by which the camera position will change.
     */
    void MoveR(const glm::vec3 &vec);

    /**
     * @brief Rotates camera to a specified angle (x,y,z absolute rotation).
     * @param vec The triple of angles.
     */
    void RotateA(const glm::vec3 &vec);

    /**
     * @brief Rotates camera by a specified angle (x,y,z relative rotation).
     * @param vec The triple of angles.
     */
    void RotateR(const glm::vec3 &vec);

    /**
     * @brief Inverts the operations for the y axis (up-down is inverted).
     */
	void InvertY(){invertedY = !invertedY;}

    /**
     * @brief Switch between camera modes.
     * @param orbit If true, the camera will orbit the focus point, otherwise
     * the focus point will be moved and the camera will remain static.
     */
	void SwitchCamMode(bool orbit);

    /**
     * @brief Adds zoom to current value.
     * @param zoom Relative zoom value.
     */
	void ZoomR(const float& zoom);

    /**
     * @brief Resets the camera into initial state.
     * @param orb If true, the camera will be orbiting.
     */
    void Reset(bool orb);
protected:
    glm::vec3 eye, lookAt, up;
    bool invertedY, orbit;
    float orbitDist;
    glm::vec3 rLookAt;
    glm::vec3 rotations;
};

#endif
