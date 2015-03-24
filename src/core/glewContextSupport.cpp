#include "glewContextSupport.h"
#include "UniShader/UniShader.h"

static GLEWContext* currentGlewContext = nullptr;

GLEWContext* glewGetContext()
{
    return currentGlewContext;
}

GlewContextSupport::GlewContextSupport() :
    _glewContext(nullptr)
{
}

GlewContextSupport::~GlewContextSupport()
{
    if (_glewContext != nullptr)
    {
        delete _glewContext;
        _glewContext = nullptr;
    }
}

void GlewContextSupport::initGlewContext()
{
    if (_glewContext != nullptr)
    {
        delete _glewContext;
    }
    _glewContext = new GLEWContext;

    activateGlewContext();
    glewExperimental = true;
    glewInit();
    deactivateGlewContext();
}

void GlewContextSupport::activateGlewContext()
{
    currentGlewContext = _glewContext;
    us::UniShader::setGLEWContext(currentGlewContext);
}

void GlewContextSupport::deactivateGlewContext()
{
    if (currentGlewContext == _glewContext)
    {
        currentGlewContext = nullptr;
        us::UniShader::setGLEWContext(currentGlewContext);
    }
}
