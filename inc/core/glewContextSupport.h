// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef GLEW_CONTEXT_SUPPORT_H
#define GLEW_CONTEXT_SUPPORT_H

#include "GL/glew.h"

GLEWContext* glewGetContext();

/**
 * @brief The GlewContextSupport class is a wrapper arround GLEW context for its easier managment.
 */
class GlewContextSupport
{
public:
    GlewContextSupport();
    virtual ~GlewContextSupport();
protected:
    /**
     * @brief Initializes the GLEW context.
     */
    void initGlewContext();

    /**
     * @brief Activates the GLEW context.
     */
    void activateGlewContext();

    /**
     * @brief Dectivates the GLEW context.
     */
    void deactivateGlewContext();
private:
    GLEWContext* _glewContext;
};

#endif
