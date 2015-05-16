// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef ELECTRODE_H
#define ELECTRODE_H

#include <glm/common.hpp>
#include <string>
#include <memory>
#include "safePtr.h"

/**
 * @brief The Electrode class represents a signel renderable electrode.
 */
class Electrode
{
public:
    typedef std::shared_ptr<Electrode> Ptr;
    typedef std::shared_ptr<const Electrode> PtrConst;
    typedef SafePtr<Electrode> WeakPtr;
    typedef SafePtr<const Electrode> WeakPtrConst;

    /**
     * @brief create Creates a new instance of Electrode.
     * @param name Name of the electrode.
     * @return Shared pointer to the new instance.
     */
    static Ptr create(std::string name);

    /**
     * @brief name Getter.
     * @return The name of the electrode.
     */
    const std::string& name();

    /**
     * @brief position2D Getter.
     * @return Position of the electrode in 2D space.
     */
    glm::vec2 position2D();

    /**
     * @brief position3D Getter.
     * @return Position of the electrode in 3D space.
     */
    glm::vec3 position3D();

    /**
     * @brief has2D Getter.
     * @return True if the electrode has position in 2D space.
     */
    bool has2D();

    /**
     * @brief has3D Getter.
     * @return True if the electrode has position in 3D space.
     */
    bool has3D();

    /**
     * @brief position2D Setter.
     * @param pos Position of the electrode in 2D space.
     */
    void position2D(glm::vec2 pos);

    /**
     * @brief position3D Setter.
     * @param pos Position of the electrode in 3D space.
     */
    void position3D(glm::vec3 pos);

    /**
     * @brief color Getter.
     * @return Color of the electrode.
     */
    glm::vec3 color();

    /**
     * @brief intensity Sets the color of the electrode depending
     * on the intensity, which must be in range <-1,1>. The color
     * is linearly mixed between blue, green, and red.
     * @param intensity Intensity of the signal assigned to the electrode.
     */
    void intensity(double intensity);

    /**
     * @brief setInactive Sets the electrode as inactive, which means
     * no signal is assigned to it. Also sets the color accordingly.
     */
    void setInactive();

    /**
     * @brief setUnavailable Sets the color as unavailable, which means
     * there were not enough samples in the signal to perform an operation.
     * Also sets the color accordingly.
     */
    void setUnavailable();

private:
    Electrode();

    std::string _name;

    bool _has2D;
    bool _has3D;

    glm::vec2 _position2D;
    glm::vec3 _position3D;

    glm::vec3 _color;
    bool _active;
};

#endif
