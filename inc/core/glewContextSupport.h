#ifndef GLEW_CONTEXT_SUPPORT_H
#define GLEW_CONTEXT_SUPPORT_H

#include "GL/glew.h"

GLEWContext* glewGetContext();

class GlewContextSupport
{
public:
    GlewContextSupport();
    virtual ~GlewContextSupport();
protected:
    void initGlewContext();
    void activateGlewContext();
    void deactivateGlewContext();
private:
    GLEWContext* _glewContext;
};

#endif
