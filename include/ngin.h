#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "types.h"
#include "log.h"
#include "shader.h"
#include "model.h"


/// Initializes the state of the engine: OpenGL context, window, events, etc...
/// Uses OpenGL 4.6 by default.
/// 
/// Returns NULL on initialization failure
GLFWwindow *ngin_init(i32 window_width, i32 window_height);

void ngin_destroy(void);
