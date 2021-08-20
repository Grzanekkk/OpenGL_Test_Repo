#include "Renderer.h"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

void GLCheckError()
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL ERROR] (" << error << ")" << std::endl;
    }
}